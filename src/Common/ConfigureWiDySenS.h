#ifndef CONFIGUREWIDYSENS_H_INCLUDED
#define CONFIGUREWIDYSENS_H_INCLUDED

#include <iostream>

#include <NITManager.h>
#include <NITDevice.h>
#include <NITFilter.h>
#include <NITAutomaticGainControl.h>
#include <NITPlayer.h>
#include <string>
#include <NITSnapshot.h>

/** This sample configuration is specific to WiDySenS 640-VST cameras                **/
/*                                                                                   */
/* SWIR cameras need to have a Non Uniformity Correction( NUC ) to show best results */
/* NUC files can be found in the USB key provided with your camera in a folder named */
/*      SNxxxx with xxxx the serial number of your camera                            */
/* Copy this SNxxx folder in the working directory of this application               */
/* When the NITDevice object is constructed, he looks for the presence of this folder*/
/*      enable automatically the Nuc processing                                      */
void ConfigureDevice(NITLibrary::NITDevice* dev);

#define USE_USB
#define NEED_AGC

#endif // CONFIGUREWIDYSENS_H_INCLUDED
