clc; clear; close all;

% Serial port settings
port = "COM2";  % Specify COM port
baud = 115200;  % Set baud rate
s = serialport(port, baud);

% Clear any data in the input and output buffers of the serial port
flush(s);

% Buffer to accumulate Base64 data
base64Buffer = "";

% function to process Base64 encoded image data
function processBase64Image(base64data)
    try
        % Decode Base64 data to binary
        binarydata = matlab.net.base64decode(base64data);
        
        % Define file name for saving image
        timestamp = datetime('now');
        disp(timestamp);
        imgFileName = str(timestamp);
        
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

% Continuous processing loop
while true
    % Read data from the serial port
    data = readline(s);
    
    % Append incoming data to buffer
    base64Buffer = strcat(base64Buffer, data);
    
    % Check if data contains end-of-image marker (e.g., "END_OF_IMAGE")
    if contains(base64Buffer, "\n")
        % extract Base64 image data up to marker
        imageData = extractBefore(base64Buffer, "\n");
        
        % Process Base64 image data
        processBase64Image(imageData);
        
        % Clear buffer
        base64Buffer = extractAfter(base64Buffer, "\n");
    end
end
