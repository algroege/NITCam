#ifndef CREATEUSBDEVICE_H_INCLUDED
#define CREATEUSBDEVICE_H_INCLUDED

#include <NITManager.h>

#include <iostream>

#include <NITDevice.h>
#include <NITFilter.h>
#include <NITAutomaticGainControl.h>
#include <NITPlayer.h>
#include <string>
#include <NITSnapshot.h>

NITLibrary::NITDevice* CreateDevice();

#endif // CREATEUSBDEVICE_H_INCLUDED
