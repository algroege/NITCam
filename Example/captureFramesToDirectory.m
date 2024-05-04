% Connect to NITCam
cam = clib.NITCam.NITCam();

% Set and activate NUC File
nucFile_200ns = 'D:\NITsnap\NUC\NUCFactory_0.2us.yml';
cam.setNucFile(nucFile_200ns);
cam.activateNuc(true);

% Set manual gain control
cam.setMgcMinMax(1, 5000);

% Configer trigger mode
cam.activateTriggerMode(true);

% Capture number of images and save into directory
saveDir = '';
fileName = '';
fileType = 'tif';
gatedMode = true;
bitMode = 0; % 0=14-bit;
triggerDelayInput = 0.45; % in µs
exposureTime = 0.1; % in µs
numTofImages = 1; 
cam.captureFrames(tofDirectory, tofFileName, fileType, gatedMode, bitMode, triggerDelayInput, exposureTime, numTofImages);