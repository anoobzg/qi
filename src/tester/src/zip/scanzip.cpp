#include "scanzip.h"
#include <opencv2/core.hpp>
#include <zip.h>
#include <unzip.h>

#ifdef _WIN32
#define USEWIN32IOAPI
#include <iowin32.h>
#endif

#include <iostream>
typedef int (*zipdata_processor_func)(void* data, zipFile& zfile);
typedef int (*unzipdata_processor_func)(void* data, unzFile& uzfile);
typedef int (*unzipbuffer_processor_func)(void* data, char* buffer, int len);

#include <string>
struct zipdata_processor
{
    zipdata_processor_func func;
    void* data;
};

struct unzipdata_processor
{
    unzipdata_processor_func func;
    void* data;
};

struct unzipbuffer_processor
{
    unzipbuffer_processor_func func;
    void* data;
};

// 保存时在zip文档中创建独立文件的函数
int save_zipfile(zipFile& zip_file, const char* file, zipdata_processor& processor)
{
    int error = ZIP_OK;
    const char* password = NULL;
    zip_fileinfo zi_file;
    int opt_compress_level = 1;  //压缩等级
    unsigned long crc_file = 0;
    int zip64 = 0;

    zi_file.tmz_date.tm_sec = zi_file.tmz_date.tm_min = zi_file.tmz_date.tm_hour =
        zi_file.tmz_date.tm_mday = zi_file.tmz_date.tm_mon = zi_file.tmz_date.tm_year = 0;
    zi_file.dosDate = 0;
    zi_file.internal_fa = 0;
    zi_file.external_fa = 0;

    //if (password != NULL) 
    //    error = getFileCrc(filenameinzip, buf, size_buf, &crcFile);
    //
    //zip64 = isLargeFile(filenameinzip);
    //

    error = zipOpenNewFileInZip3_64(zip_file, file, &zi_file, NULL, 0, NULL, 0, NULL /* comment*/,
        (opt_compress_level != 0) ? Z_DEFLATED : 0, opt_compress_level, 0,
        /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
        -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
        password, crc_file, zip64);

    if (error != ZIP_OK)
        printf("error in opening %s in zipfile\n", file);

    if (error == ZIP_OK)
    {
        error = (*processor.func)(processor.data, zip_file);
    }
    if (error < 0)
        error = ZIP_ERRNO;
    else
    {
        error = zipCloseFileInZip(zip_file);
        if (error != ZIP_OK)
            printf("error in closing %s in the zipfile\n", file);
    }
    return error;
}

// 保存时内部创建zip文档的函数
bool save_zip_inner(const char* zip_file, zipdata_processor& processor)
{
    zipFile zipout_file;
    int overwrite = 0;  //2表示附加在文件后 , 其它表示重写
    int error = ZIP_OK;
    //    int errclose;
#ifdef USEWIN32IOAPI
    zlib_filefunc64_def ffunc;
    fill_win32_filefunc64A(&ffunc);
    zipout_file = zipOpen2_64(zip_file, overwrite, NULL, &ffunc);
#else
    zf = zipOpen64(zip_file, overwrite);
#endif

    if (zipout_file == NULL)
    {
        printf("error opening %s\n", zip_file);
        error = ZIP_ERRNO;
    }

    if (error == ZIP_OK)
    {
        error = (*processor.func)(processor.data, zipout_file);
    }
    int close_error = zipClose(zipout_file, NULL);
    if (close_error != ZIP_OK)
        printf("error in closing %s\n", zip_file);
    return error == ZIP_OK;
}

// 加载时内部打开zip文档的函数
bool load_zip_inner(const char* unzip_file, unzipdata_processor& processor)
{
    unzFile unz_file;
    char filename_try[256 + 16] = "";
    strncpy_s(filename_try, unzip_file, 256 - 1);
    /* strncpy doesnt append the trailing NULL, of the string is too long. */
    filename_try[256] = '\0';

    int error = UNZ_OK;
#ifdef USEWIN32IOAPI
    zlib_filefunc64_def ffunc;
#endif

#ifdef USEWIN32IOAPI
    fill_win32_filefunc64A(&ffunc);
    unz_file = unzOpen2_64(unzip_file, &ffunc);
#else
    uf = unzOpen64(unzip_file);
#endif
    if (unz_file == NULL)
    {
        strcat_s(filename_try, ".zip");
#ifdef USEWIN32IOAPI
        unz_file = unzOpen2_64(filename_try, &ffunc);
#else
        unz_file = unzOpen64(filename_try);
#endif
    }

    if (unz_file == NULL)
    {
        printf("Cannot open %s or %s.zip\n", unzip_file, unzip_file);
        return false;
    }

    error = (*processor.func)(processor.data, unz_file);

    unzClose(unz_file);
    return error == ZIP_OK;
}

int load_unzipfile(unzFile& unzip_file, const char* file, unzipbuffer_processor& processor)
{
    char name[256];
    unz_file_info64 file_info;
    int error = unzGetCurrentFileInfo64(unzip_file, &file_info, name, sizeof(name), NULL, 0, NULL, 0);

    if ((error != UNZ_OK))
    {
        printf("error %d with zipfile in unzGetCurrentFileInfo\n", error);
        return error;
    }

    if (!strcmp(file, name) && file_info.uncompressed_size > 0)
    {
        error = unzOpenCurrentFilePassword(unzip_file, NULL);
        if (error != UNZ_OK)
        {
            printf("error %d with zipfile in unzOpenCurrentFilePassword\n", error);
        }

        if (error == UNZ_OK)
        {
            char* buffer = new char[file_info.uncompressed_size];
            int read_len = unzReadCurrentFile(unzip_file, buffer, (unsigned int)file_info.uncompressed_size);
            if(read_len > 0) error = (*processor.func)(processor.data, buffer, (int)file_info.uncompressed_size);
            assert(unzReadCurrentFile(unzip_file, buffer, 1) == 0);
            delete[]buffer;
        }

        if (error == UNZ_OK)
        {
            error = unzCloseCurrentFile(unzip_file);
            if (error != UNZ_OK)
            {
                printf("error %d with zipfile in unzCloseCurrentFile\n", error);
            }
        }
        else
            unzCloseCurrentFile(unzip_file); /* don't lose the error */
    }
    else
    {
        printf("error filename in zipfile\n");
        error = UNZ_ERRNO;
    }

    return error;
}
/////////////////////////////////
//zip文档内 不同格式独立文件的加载保存实现

// .bmp
struct zip_bmp_data
{
    cv::Mat* mat;
};

int save_bmp_data(void* data, zipFile& zfile)
{
    zip_bmp_data* bmp_data = (zip_bmp_data*)data;
    cv::Mat& mat = *bmp_data->mat;

    int width = mat.cols, height = mat.rows, channels = mat.channels();
    int fileStep = (width * channels + 3) & -4;
    uchar zeropad[] = "\0\0\0\0";
    static const char* fmtSignBmp = "BM";

    int  bitmapHeaderSize = 40;
    int  paletteSize = channels > 1 ? 0 : 1024;
    int  headerSize = 14 /* fileheader */ + bitmapHeaderSize + paletteSize;
    size_t fileSize = (size_t)fileStep * height + headerSize;

    char* buffer = new char[fileSize];
    char* tmp = buffer;

    // write signature 'BM'
    int sign_size = (int)strlen(fmtSignBmp);
    memcpy(tmp, fmtSignBmp, sign_size);
    tmp += sign_size;

    // write file header
    *(int*)(tmp) = (int)fileSize; tmp += 4; // file size 
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = headerSize; tmp += 4;

    // write bitmap header
    *(int*)(tmp) = bitmapHeaderSize; tmp += 4;
    *(int*)(tmp) = width; tmp += 4;
    *(int*)(tmp) = height; tmp += 4;

    *tmp++ = (uchar)(1);
    *tmp++ = (uchar)(1 >> 8);
    int c = (channels << 3);
    *tmp++ = (uchar)(c);
    *tmp++ = (uchar)(c >> 8);
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = 0; tmp += 4;
    *(int*)(tmp) = 0; tmp += 4;

    //write palette
    if (channels == 1)
    {
        int i, length = 256;
        for (i = 0; i < length; i++)
        {
            int val = (i * 255 / (length - 1));
            *tmp++ = (uchar)val; *tmp++ = (uchar)val; *tmp++ = (uchar)val;
            *tmp++ = 0;
        }
    }

    width *= channels;
    for (int y = height - 1; y >= 0; y--)
    {
        memcpy(tmp, mat.ptr(y), width);
        tmp += width;
        if (fileStep > width)
        {
            memcpy(tmp, zeropad, fileStep - width);
            tmp += fileStep - width;
        }
    }

    int error = zipWriteInFileInZip(zfile, buffer, (unsigned)fileSize);

    int offset = (int)(tmp - buffer);
    assert(fileSize == (int)fileSize);

    delete[] buffer;
    return error;
}
int load_bmp_data(void* data, char* buffer, int len)
{
    zip_bmp_data* bmp_data = (zip_bmp_data*)data;
    cv::Mat& mat = *bmp_data->mat;

    int width = *(int*)(buffer + 18);
    int height = *(int*)(buffer + 22);
    int channels = 1;
    char* d = buffer + 1078;

    mat.create(height, width, CV_8UC1);
    int fileStep = (width * channels + 3) & -4;
    for (int y = height - 1; y >= 0; y--)
    {
        memcpy(mat.ptr(y), d, width);
        d += width;
        if (fileStep > width)
        {
            d += fileStep - width;
        }
    }
    return UNZ_OK;
}
// .ply
struct zip_ply_data
{
    cv::Mat* position;
    cv::Mat* flags;
    cv::Mat* color;
};

int save_ply_data(void* data, zipFile& zfile)
{
    zip_ply_data* ply_data = (zip_ply_data*)data;
    cv::Mat& pmat = *ply_data->position;
    cv::Mat& fmat = *ply_data->flags;
    cv::Mat& cmat = *ply_data->color;

    int width = fmat.cols, height = fmat.rows;
    unsigned long vertex_size = 0;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (*fmat.ptr(j, i) > 0)
                ++vertex_size;
        }
    }
    //write header
    char ply_header[1024];
    sprintf_s(ply_header, 1024, "ply\nformat binary_little_endian 1.0\n"
        "obj_info num_cols %d\n"
        "obj_info num_rows %d\n"
        "element vertex %lu\n"
        "property float x\n"
        "property float y\n"
        "property float z\n"
        "property uchar diffuse_red\n"
        "property uchar diffuse_green\n"
        "property uchar diffuse_blue\n"
        "end_header\n", width, height, vertex_size);

    int len = (int)strlen(ply_header);
    int error = ZIP_OK;

    error = zipWriteInFileInZip(zfile, ply_header, (unsigned)len);

    //write vertex
    int vertex_buffer_size = vertex_size * (3 * sizeof(float) + 3 * sizeof(unsigned char));
    char* tmp = 0;
    char* vertex_buffer = new char[vertex_buffer_size];
    tmp = vertex_buffer;

    int stride = 3 * sizeof(float);
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (*fmat.ptr(j, i) > 0)
            {
                const uchar* p = pmat.ptr(j, i);
                const uchar* c = cmat.ptr(j, i);

                memcpy(tmp, p, stride);
                tmp += stride;
                *tmp++ = *c; *tmp++ = *c; *tmp++ = *c;
            }
        }
    }

    int offset = (int)(tmp - vertex_buffer);
    assert(offset == vertex_buffer_size);
    error = zipWriteInFileInZip(zfile, vertex_buffer, (unsigned)vertex_buffer_size);
    delete[] vertex_buffer;
    return error;
}

int load_ply_data(void* data, char* buffer, int len)
{
    zip_ply_data* ply_data = (zip_ply_data*)data;
    cv::Mat& pmat = *ply_data->position;
    cv::Mat& fmat = *ply_data->flags;

    int width = fmat.cols;
    int height = fmat.rows;
    pmat.create(height, width, CV_32FC3);

    int fvertex_size = 0;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (*fmat.ptr(j, i) > 0)
                ++fvertex_size;
        }
    }

    char* t = buffer;

    int nn = 0;
    int n = 0;

    int t1 = -1;
    int t2 = -1;
    do {
        if (*t == '\n')
        {
            ++nn;
            if (nn == 4) t1 = n;
            if (nn == 5) t2 = n;
        }
        ++t;
        ++n;
    } while ((n < 1000) && (nn < 12));

    if ((t1 > 0) && (t2 > 0))
    {
        std::string header(buffer + t1 + 1, buffer + t2);
        int vertex_number = -1;
        size_t pos = header.find_last_of(' ');
        if (pos != std::string::npos)
        {
            std::string str_num(buffer + t1 + 1 + pos, buffer + t2);
            vertex_number = atoi(str_num.c_str());
        }

        //assert(fvertex_size == vertex_number);
        if (vertex_number > 0)
        {
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (*fmat.ptr(j, i) > 0)
                    {
                        uchar* p = pmat.ptr(j, i);
                        memcpy(p, t, 3 * sizeof(float));
                        t += 15;
                    }
                }
            }

            return UNZ_OK;
        }
        return UNZ_ERRNO;
    }

    return UNZ_ERRNO;
}
// 扫描数据zip文档的组织
struct zip_scan_data
{
    cv::Mat* position;
    cv::Mat* depth;
    cv::Mat* color;
    cv::Mat* flags;
};

int save_scan_data(void* data, zipFile& zipout_file)
{
    zip_scan_data* scan_data = (zip_scan_data*)data;

    cv::Mat& color = *scan_data->color;
    cv::Mat& depth = *scan_data->depth;
    cv::Mat& position = *scan_data->position;
    cv::Mat& flags = *scan_data->flags;

    int error = ZIP_OK;
    do
    {
        zipdata_processor zip_processor;

        zip_bmp_data bmp_data;
        zip_processor.func = save_bmp_data;
        zip_processor.data = (void*)&bmp_data;

        bmp_data.mat = (cv::Mat*)(&color);
        if (error = save_zipfile(zipout_file, "color.bmp", zip_processor) != ZIP_OK) break;

        bmp_data.mat = (cv::Mat*)(&depth);
        if (error = save_zipfile(zipout_file, "depth.bmp", zip_processor) != ZIP_OK) break;

        bmp_data.mat = (cv::Mat*)(&flags);
        if (error = save_zipfile(zipout_file, "flags.bmp", zip_processor) != ZIP_OK) break;

        zip_ply_data ply_data;
        ply_data.position = (cv::Mat*)(&position);
        ply_data.flags = (cv::Mat*)(&flags);
        ply_data.color = (cv::Mat*)(&color);
        zip_processor.func = save_ply_data;
        zip_processor.data = (void*)&ply_data;
        if (error = save_zipfile(zipout_file, "position.ply", zip_processor) != ZIP_OK) break;
    } while (0);

    return error;
}

int load_scan_data(void* data, unzFile& unzip_file)
{
    zip_scan_data* scan_data = (zip_scan_data*)data;

    cv::Mat& color = *scan_data->color;
    cv::Mat& depth = *scan_data->depth;
    cv::Mat& position = *scan_data->position;
    cv::Mat& flags = *scan_data->flags;

    unz_global_info64 info;
    int error = unzGetGlobalInfo64(unzip_file, &info);
    if (error != UNZ_OK)
        printf("error %d with zipfile in unzGetGlobalInfo \n", error);
    if (info.number_entry != 4)
    {
        printf("zipfile is not scan data zip\n");
        error = UNZ_ERRNO;
    }

    const char* names[4] = { "color.bmp", "depth.bmp", "flags.bmp", "position.ply" };
    unzipbuffer_processor processors[4];
    zip_bmp_data depth_bmp;
    depth_bmp.mat = scan_data->depth;
    zip_bmp_data color_bmp;
    color_bmp.mat = scan_data->color;
    zip_bmp_data flags_bmp;
    flags_bmp.mat = scan_data->flags;
    zip_ply_data position_data;
    position_data.color = scan_data->color;
    position_data.flags = scan_data->flags;
    position_data.position = scan_data->position;

    processors[0].func = load_bmp_data;
    processors[0].data = &color_bmp;
    processors[1].func = load_bmp_data;
    processors[1].data = &depth_bmp;
    processors[2].func = load_bmp_data;
    processors[2].data = &flags_bmp;
    processors[3].func = load_ply_data;
    processors[3].data = &position_data;

    if (error == UNZ_OK)
    {
        for (uLong i = 0; i < info.number_entry; i++)
        {
            if (load_unzipfile(unzip_file, names[i], processors[i]) != UNZ_OK)
                break;
            
            if ((i + 1) < info.number_entry)
            {
                error = unzGoToNextFile(unzip_file);
                if (error != UNZ_OK)
                {
                    printf("error %d with zipfile in unzGoToNextFile\n", error);
                    break;
                }
            }
        }
    }

    return error;
}
/////////////////////////////////

// scan 数据保存加载接口
bool save_scanzip(const cv::Mat& position, const cv::Mat& color, const cv::Mat& flags, const cv::Mat& depth, const char* zip_file)
{
    int error = ZIP_OK;
    zipdata_processor processor;
    zip_scan_data scan_data;
    scan_data.position = (cv::Mat*)&position;
    scan_data.color = (cv::Mat*)& color;
    scan_data.flags = (cv::Mat*)& flags;
    scan_data.depth = (cv::Mat*)& depth;
    processor.func = save_scan_data;
    processor.data = (void*)&scan_data;
    error = save_zip_inner(zip_file, processor) ? ZIP_OK : ZIP_ERRNO;
	return error == ZIP_OK;
}

bool load_scanzip(cv::Mat& position, cv::Mat& color, cv::Mat& flags, cv::Mat& depth, const char* zip_file)
{
    int error = UNZ_OK;
    unzipdata_processor processor;
    zip_scan_data scan_data;
    scan_data.position = (cv::Mat*) & position;
    scan_data.color = (cv::Mat*) & color;
    scan_data.flags = (cv::Mat*) & flags;
    scan_data.depth = (cv::Mat*) & depth;
    processor.func = load_scan_data;
    processor.data = (void*)&scan_data;
    error = load_zip_inner(zip_file, processor) ? UNZ_OK : UNZ_ERRNO;
    return error == UNZ_OK;
}
