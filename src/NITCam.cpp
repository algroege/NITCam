#include "NITCam.h"
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;
using namespace NITLibrary::NITToolBox;  //For the filters and observer

NITCam::NITCam() : mgc(2000, 5000) {
	pPlayer = NULL;

	//NITManualGainControl mgc(min, max);
	try {
		cout << "Connecting to device ..." << endl;
		//Open a connection to the camera and create a NITDevice instance
		dev = CreateDevice();    										
		
		if (dev) {
			//Connect a NITConfigObserver derived class to the NITDevice
			(*dev) << config_observer;          						
			cout << "configuring device ..." << endl;
			//Set camera parameters:
			ConfigureDevice(dev);										
			// configure snap counter
			snap.setCounter(1, 5);

		} else {
			cout << "No Camera on USB, so ... I'm out!!!" << std::endl;
		}
	}
	catch( NITException& exc ) {
			cout << "NITException: " << exc.what() << std::endl;
	}
	
}

NITCam::~NITCam() {
	if (dev != NULL) {
		// make sure to stop cam and delete player if still running
		stopLiveImage();
	}
}

void NITCam::activateTriggerMode(bool state) {
	try {
		if (state) {
			dev->setParamValueOf("Trigger Mode", "Input");
		}
		else {
			dev->setParamValueOf("Trigger Mode", "Disabled");
		}
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

bool NITCam::captureFrames(const string saveDirectory, const string fileName, const string fileType, bool gatedMode, int bitMode, double inputTriggerDelay, double exposureTime, int numOfFramesToCapture) {
	switch (bitMode) {
		case 0:
			// build pipelie without gc
			*dev << snap;
			break;
		case 1:
			// build pipeline with mgc
			*dev << mgc << snap;
			break;
		default:
			// build pipelie with agc
			*dev << agc << snap;
	}
		

	try {
		// change mode to 'global shutter'
		if (gatedMode) {
			dev->setParamValueOf("Mode", "Gated");
		} else {
			dev->setParamValueOf("Mode", "Global Shutter");
			dev->setParamValueOf("AnalogGain", "Low");
		}
		// needto update mode config first
		dev->updateConfig();
		dev->setParamValueOf("Exposure Time", exposureTime);
		dev->setParamValueOf("Trigger Delay Input", inputTriggerDelay);
		dev->updateConfig();

		//cout << "setting filetype to *.bmp and directory to: " << directory << endl;
		snap.reset(saveDirectory, fileName, fileType);
		snap.setCounter(snap.getCounterValue(), 5);

		// set snap count
		snap.snap(numOfFramesToCapture);
		// get current counter value
		unsigned int currentCounterValue = snap.getCounterValue();
		//cout << "Current counnter value: " << currentCounterValue << std::endl;
		// start capturing
		dev->start();

		// wait until frame is captured
		time_t tstart;
		tstart = time(0);
		while ((currentCounterValue + numOfFramesToCapture) > snap.getCounterValue()) {
			// break if time limit reached
			if (difftime(time(0), tstart) > 2) {
				cout << "No frame within 3 seconds.." << endl;
				return false;
			}
		}
		dev->stop();

		cout << "Last File Name: " << snap.getLastFileName() << std::endl;
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
		return false;
	}
	// disconnect all
	snap.disconnect();
	agc.disconnect();
	mgc.disconnect();
	return true;
}

void NITCam::setMgcMinMax(unsigned short min, unsigned short max) {
	mgc.setMinMaxValue(min, max);
	//*dev << mgc << snap;
}

void NITCam::startLiveImage() {
	// Make sure no player is running
	stopLiveImage();
	// allocate new instance of none existing
	if (pPlayer == NULL) {
		pPlayer = new NITPlayer("Camera view");
	}

	try {
		snap.disconnect();
		*dev << agc << *pPlayer;
		dev->start();
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}

	// for several seconds
	//chrono::milliseconds timespan(15000); // or whatever
	//this_thread::sleep_for(timespan);
	//dev->stop();
}

void NITCam::startMgcLiveImage() {
	// Make sure no player is running
	stopLiveImage();
	// reset pipeline
	if (pPlayer == NULL) {
		pPlayer = new NITPlayer("Camera view");
	}
	try {
		snap.disconnect();
		*dev << mgc << *pPlayer;
		dev->start();
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::stopLiveImage() {
	try {
		dev->stop();
		snap.disconnect();
		agc.disconnect();
		mgc.disconnect();
		if (pPlayer != NULL) {
			delete pPlayer;
			pPlayer = NULL;
		}
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::setNucDirectory(const string nucFileDirectory) {
	try {
		dev->setNucDirectory(nucFileDirectory);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::setNucFile(const string nucFileDirectory) {
	try {
		dev->setNucFile(nucFileDirectory);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::setBprDirectory(const string bprFileDirectory) {
	try {
		dev->setBprFile(bprFileDirectory);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::setBprFile(const string bprFileDirectory) {
	try {
		dev->setBprFile(bprFileDirectory);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::activateNuc(bool activate) {
	try {
		dev->activateNuc(activate);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::activateBpr(bool activate) {
	try {
		dev->activateBpr(activate);
	}
	catch (NITException& exc) {
		cout << "NITException: " << exc.what() << std::endl;
	}
}

void NITCam::nucActive() {
	if (dev->nucActive()) {
		cout << "NUC Processing is active" << endl;
	} else {
		cout << "NUC Processing is inactive" << endl;
	}
}
void NITCam::bprActive() {
	if (dev->bprActive()) {
		cout << "BPR Processing is active" << endl;
	}
	else {
		cout << "BPR Processing is inactive" << endl;
	}
}

