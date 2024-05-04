#ifndef NITFRAME_H
#define NITFRAME_H

#include "NITImpExp.h"

namespace NITLibrary {

/** \brief Class who embed the data of the captured frame.
 *
 * When a frame is captured by a NITdevice, a NITFrame is constructed and passed to the pipeline.
 *
 * The frame data is 16 bytes aligned.
 */
class NITDLL_API NITFrame
{
    public:
        enum ePixType { RGBA, /**< pixel format for color images */
                        FLOAT /**< pixel format for grayscale images */
                      };
        NITFrame();
        NITFrame( unsigned int, float*, unsigned int w, unsigned int h, unsigned long long id, float temperature = 0.0f, double ticks = 0.0 );
        ~NITFrame();
        /** \brief return the number of bits per pixel of the sensor
         *
         * This value correspond to the number of bits per pixel of the sensor regardless of the pixelType.\n
         *
         * \return return the number of bits per pixel
         */
        unsigned int bitsPerPixel() const   { return bitsPerPix; }
        /** \brief return a pointer to the pixel data
         *
         * \attention If the pixel type is RGBA the returned value has to be casted to unsigned int to traverse each pixel or unsigned char to traverse each pixel element.\n
         *
         * \return return a pointer to the pixel data
         */
        float* data() const                 { return datas; }
        /** \brief return a pointer to the pixel data
         *
         * \attention If the pixel type is RGBA the returned value has to be casted to unsigned int to traverse each pixel or unsigned char to traverse each pixel element.\n
         *
         * \return return a pointer to the pixel data
         */
        float* data()                       { return datas; }
        /** \brief return the number of rows of the frame
         *
         * \return return the number of rows of the frame
         */
        unsigned int rows() const           { return height; }
        /** \brief return the number of columns of the frame
         *
         * \return return the number of columns of the frame
         */
        unsigned int columns() const        { return width; }
        /** \brief return the temperature of the camera when the frame was captured
         *
         * Only for SWIR cameras. Always 0 for other cameras.
         * \return return the temperature of the camera in Celsius
         */
        float temperature() const          { return celsius; }
        /** \brief return the pixel format of the frame
         *
         * \return return the pixel format of the frame
         */
        ePixType pixelType() const          { return type; }
        /** \brief return the frame number of this frame
         *
         * - USB cameras:  This value is reset at NITDevice construction.
         *                 max value is MAX_UNSIGNED_LONG_LONG
         * - GIGE cameras: This value is reset when the streaming port is opened.
         *                 max value is MAX_UNSIGNED_SHORT
         *
         * \return return the frame number of this frame
         */
        unsigned long long Id() const    { return id; }
        /** \brief return the time in microseconds elapsed since the last reset of the Gige/Usb Timestamp
         *
         * For USB cameras, this value is the timestamp provided by the camera for SenS 1280V series.
         * For other USB cameras, value is 0.
         *
         * \return return the time in microseconds elapsed since the last reset of the Gige/Usb Timestamp
         */
        double gigeTimestamp() const    { return ticks; }
        /** \brief set the pixel format of the frame
         *
         * This function is used by NITFilters who transform gray images to color images or the inverse.
         *
         * \param pix_type The new pixel format
         * \return return the pixel format of the frame
         */
        void setPixelType( ePixType pix_type );

    private:
        float* datas;
        unsigned int width, height, bitsPerPix;
        float celsius;
        ePixType type;
        unsigned long long id;
        double ticks;
};
}
#endif // NITFRAME_H
