fid = fopen('img.txt', 'r');
base64data = fscanf(fid, '%s');
fclose(fid);

binarydata = matlab.net.base64decode(base64data);

tempImgFileName = 'tempimg.png';
tempID = fopen(tempImgFileName,'wb');
fwrite(tempID, binarydata, 'uint8');
fclose(tempID);

outputimg = imread(tempImgFileName);
imshow(outputimg);


