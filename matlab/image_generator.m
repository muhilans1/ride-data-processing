% Create a 10x10x3 matrix for an RGB image
img = rand(10, 10, 3); 

% Display the image
imshow(img);

% Save the image as a PNG file
imwrite(img, 'random_rgb_image.png');