function [Z] = load_z_from_file(file)
    fid = fopen(file, 'rb');
    if(fid > 0)
        w = fread(fid, 1, 'int32');
        h = fread(fid, 1, 'int32');
        Z = fread(fid, [h w], 'float32');
    end
    fclose(fid);
end