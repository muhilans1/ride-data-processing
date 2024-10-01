clc; clear; close all;

% Serial port settings
port = "COM3";  % Specify COM port
baud = 115200;  % Set baud rate
s = serialport(port, baud);
fprintf('Serial Port %s opened with baud %d', port, baud)
% Clear any data in the input and output buffers of the serial port
flush(s);

% Buffer to accumulate Base64 data
base64Buffer = "";

% function to process Base64 encoded image data
function processBase64Image(base64data)
    try
        disp("I'm processing data")
        % Decode Base64 data to binary
        binarydata = matlab.net.base64decode(base64data);
        
        % Define file name for saving image
        timestamp = datetime('now');
        format='yyyy-MM-dd HHmmss';
        
        imgFileName = string(timestamp, format)
        
        % Open file for writing binary data        
        tempID = fopen(imgFileName, 'wb');        
        
        % Write binary image data to temporary file
        fwrite(tempID, binarydata, 'uint8');
        
        % Close the temporary file
        fclose(tempID);
        
        % Read image from temporary file
        outputimg = imread(imgFileName);
        
        % Display image in figure window
        imshow(outputimg);
        
        % Force MATLAB to update figure window immediately
        drawnow;
    catch ME
        disp('Error processing image:');
        disp(ME.message);
    end
end

% Set the number of images to receive for testing
maxImages = 5;  % Stop after receiving 5 images
imageCount = 0;  % Initialize counter

% Continuous processing loop
while true
    % Read data from the serial port
    data = readline(s);
    disp(base64Buffer)
    disp("I'm reading data")
    
    % Append incoming data to buffer
    base64Buffer = strcat(base64Buffer, data);
    
    % Check if data contains end-of-image marker (e.g., "END_OF_IMAGE")
    if contains(base64Buffer, "END_OF_IMAGE")
        % extract Base64 image data up to marker
        imageData = extractBefore(base64Buffer, "END_OF_IMAGE");
        
        % Process Base64 image data
        processBase64Image(imageData);

        %Image Limit for Testing:
        % Increment the image counter
        imageCount = imageCount + 1;
        fprintf('Image %d processed.\n', imageCount);
        
        % Break if the number of images reaches the maximum for testing
        if imageCount >= maxImages
            disp('Max number of images reached. Exiting...');
            
            break;
        end
        
        % Clear buffer
        base64Buffer = extractAfter(base64Buffer, "END_OF_IMAGE");
    end

end
