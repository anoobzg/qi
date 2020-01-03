#include <iostream>

extern "C"
{
	#include <f2c.h>
	#include <clapack.h>
}

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>

#include <assert.h>
using namespace cv;
void clapack_svd(const Mat& src, Mat& uo, Mat& so, Mat& vo)
{
	Mat* A = (Mat*)&src;
	Mat* W = &so;
	Mat* U = &uo;
	Mat* V = &vo;
	//获取待分解矩阵A的大小;
	int ROW = A->rows;
	int COLUMN = A->cols;

	//转换A为数组Aa，以调用CLAPACK库中SVD分解函数;
	double* Aa = new double[ROW * COLUMN];

	int tempc(0);
	for (int j = 0; j < COLUMN; ++j)
	{
		for (int i = 0; i < ROW; ++i)
		{
			Aa[tempc] = A->at<double>(i, j);//cvmGet(A, i, j);
			tempc++;
		}
	}

	//定义相关参数并初始化及分配内存;
	char JOBU;
	char JOBVT;

	//数据类型integer是fortran里的。这里在C++下可以使用的原因是f2c.h文件中已经作了定义;
	integer M = ROW;
	integer N = COLUMN;
	integer LDA = M;
	integer LDU = M;
	integer LDVT = N;
	integer LWORK;
	integer INFO;

	int mm = (ROW >= COLUMN) ? COLUMN : ROW;
	int mn = (ROW >= COLUMN) ? ROW : COLUMN;


	//LWORK >= max( 1, 3 * min( M, N ) + max( M, N ), 5 * min( M, N ) );
	int tem1 = 3 * mm + mn;
	int tem2 = 5 * mm;
	LWORK = (tem1 >= tem2) ? tem1 : (tem2 >= 1) ? tem2 : 1;

	double* s = new double[mm];     //只返回特征值，数组大小为min( M, N );
	double* wk = new double[LWORK];
	double* uu = new double[ROW * COLUMN];
	double* vt = new double[COLUMN * COLUMN];

	JOBU = 'S';
	JOBVT = 'A';

	//调用CLAPACK库中SVD分解函数对矩阵A进行SVD分解
	/* Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer  *n,
	doublereal *a, integer *lda, doublereal *s, doublereal *u,  integer *ldu,
	doublereal *vt, integer *ldvt, doublereal *work, integer  *lwork, integer *info)
	*/
	dgesvd_(&JOBU, &JOBVT, &M, &N, Aa, &LDA, s, uu, &LDU, vt, &LDVT, wk, &LWORK, &INFO);

	//根据分解成功标志位的值将分解后的数组转换成CvMat矩阵形式;
	if (INFO == 0)
	{
		tempc = 0;
		for (int iw = 0; iw < COLUMN; ++iw)
		{
			for (int jw = 0; jw < COLUMN; ++jw)
			{
				if (iw == jw)
				{
					W->at<double>(iw, jw) =  s[tempc];
					tempc++;
				}else
					W->at<double>(iw, jw) = 0.0;
			}
		}

		tempc = 0;
		for (int iu = 0; iu < COLUMN; ++iu)
		{
			for (int ju = 0; ju < ROW; ++ju)
			{
				U->at<double>(ju, iu) = uu[tempc];
				tempc++;
			}
		}

		tempc = 0;
		for (int iv = 0; iv < COLUMN; ++iv)
		{
			for (int jv = 0; jv < COLUMN; ++jv)
			{
				V->at<double>(iv, jv) =  vt[tempc];
				tempc++;
			}
		}
	}

	//内存释放;
	delete[] Aa;
	delete[] s;
	delete[] wk;
	delete[] uu;
	delete[] vt;
}

void opencv_svd(const Mat& src, Mat& u, Mat& s, Mat& v)
{
	cv::SVDecomp(src, s, u, v, SVD::FULL_UV);
}

void Check(const Mat& src, const Mat& dst)
{
	int row = src.rows;
	int column = src.cols;

	int d_row = dst.rows;
	int d_column = dst.cols;

	assert(row == d_row);
	assert(column == d_column);

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			assert(src.at<double>(i, j) == dst.at<double>(i, j));
		}
	}
}

int main(int argc, char* argv[])
{
	Mat src = (Mat_<double>(3, 3) << 8, 1, 6, 3, 5, 7, 4, 9, 2);

	Mat clapack_u(3, 3, CV_64FC1);
	Mat clapack_s(3, 3, CV_64FC1);
	Mat clapack_v(3, 3, CV_64FC1);
	clapack_svd(src, clapack_u, clapack_s, clapack_v);

	Mat opencv_u;
	Mat opencv_s;
	Mat opencv_v;
	opencv_svd(src, opencv_u, opencv_s, opencv_v);

	std::cout << "clapack svd: " << std::endl;
	std::cout << clapack_s << std::endl;
	std::cout << "opencv svd: " << std::endl;
	std::cout << opencv_s << std::endl;
	return EXIT_SUCCESS;
}