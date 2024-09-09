% read file
text = fileread('/Users/nzubair/Desktop/test1');

% decode text into byte array
img_bytes = matlab.net.base64decode(text);

% create a file with the decoded array
fid = fopen('test.png', 'wb'); % write in binary
fwrite(fid, img_bytes,'uint8');
fclose(fid);

% read new file and show image
image = imread('test.png');
imshow(image);