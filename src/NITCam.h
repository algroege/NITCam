#ifndef NITINTERFACE_H
#define NITINTERFACE_H

#include <Windows.h>                     //For ::Sleep
#include <iostream>

#include <NITManager.h>
#include <NITDevice.h>
#include <NITFilter.h>
#include <NITAutomaticGainControl.h>
#include <NITManualGainControl.h>
#include <NITPlayer.h>
#include <string>
#include <NITSnapshot.h>

#include "Common\CameraSelector.h"

#ifndef CAMERA_MODEL
    #error you must define CAMERA_MODEL in CameraSelector.h.
#endif // CAMERA_MODEL


using namespace std;
using namespace NITLibrary;
using namespace NITLibrary::NITToolBox;  //For the filters and observer

#ifdef USE_GIGE
    #include "Common/CreateGigeDevice.h"
    #include "Common/GigeConfigObserver.h"
    #define CONFIG_OBSERVER GigeConfigObserver
    #include "Common/SimplePipeline.h"

#elif defined(USE_USB)
    #include "Common/CreateUsbDevice.h"
    #include "Common/UsbConfigObserver.h"
    #define CONFIG_OBSERVER UsbConfigObserver
    #ifdef NEED_AGC   //Some cameras need an adaptation of the RAW data outputted by the camera to be displayed
        //#include "Common/AgcPipeline.h"
    #else
        #include "Common/ColorPipeline.h"
    #endif // NEED_AGC
#endif

/** \brief This is the main Interface Class to handle the shitty NIT Camera
 *
 * All the interfaces you desire!
 *
 */
class NITCam {
	NITSnapshot snap;
	NITAutomaticGainControl agc;
	NITManualGainControl mgc;
	
	
	//double numOfFramesToCapture;
	
	protected:
		NITPlayer* pPlayer;
	
	public:
		NITCam();
		~NITCam();		
		CONFIG_OBSERVER config_observer;
		NITDevice* dev;
		// NITPlayer player;
		
		string directory;

		void activateTriggerMode(bool);
		/** \brief Main function to capture frames
		 *
		 * int bitMode: 0 = 14-bit, 1 = 8-bit manual gain control, 2 = 8-bit automatic gain control
		 *
		 */
		bool captureFrames(const string saveDirectory, const string fileName, const string fileType, bool gatedMode, int bitMode, double triggerDelayInput, double exposureTime, int numOfFramesToCapture);						// Expo Min: 100 - Expo Max: 2500 - step: 100;
		
		void setMgcMinMax(unsigned short min, unsigned short max);
		
		//void setAutomaticgainControl(bool);

		void startLiveImage();
		void startMgcLiveImage();
		void stopLiveImage();

		// ToDo: NUC and BPR, 

		void setNucDirectory(const string nucFileDirectory);
		void setNucFile(const string nucFileDirectory);

		void setBprDirectory(const string bprFileDirectory);
		void setBprFile(const string bprFileDirectory);		

		void activateNuc(bool);
		void activateBpr(bool);

		void nucActive();
		void bprActive();

};

#endif
