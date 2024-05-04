#ifndef NITUSB_H_INCLUDED
#define NITUSB_H_INCLUDED

#include "NITImpExp.h"
#include <string>
#include <vector>

namespace NITLibrary {

    class NITDevice;

    /** \brief namespace of helpers for Usb cameras. */
  namespace Usb {
    NITDLL_API bool GetUsbDevicePath(NITDevice& dev, char*, size_t );

    /** \brief Return a string containing the usb path to the camera.
     * The usb path is a string who can have two forms:\n
     *    If only one NIT camera is coonected: \?usb#vid_vvvv&pid_pppp#ssss#{gggggggg-gggg-gggg-gggg-gggggggggggg}
     *    If more than one camera is connected:\?usb#vid_vvvv&pid_pppp&mi_ii#aaaaaaaaaaaaaaaa#{gggggggg-gggg-gggg-gggg-gggggggggggg}
     * \param dev The usb device on which function will be applied.
     * \return the usb path content.
     * \throw NITException if the device is not Usb
     */
    inline std::string getUsbDevicePath( NITDevice& dev )
    {
        std::vector< char > tmp(1024);
        size_t data_size( tmp.size());
        if( !GetUsbDevicePath( dev, tmp.data(), data_size ) )
        {
            tmp.resize(data_size);
            GetUsbDevicePath( dev, tmp.data(), data_size );
        }
        return std::string( tmp.data() );
    }
} }

#endif // NITUSB_H_INCLUDED
