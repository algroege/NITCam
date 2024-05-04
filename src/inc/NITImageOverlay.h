#ifndef NITIMAGEOVERLAY_H
#define NITIMAGEOVERLAY_H

#include <NITFilter.h>
#include <vector>
#include <string>

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Permit to overlay an image on part of the frame
 *
 */
class NITImageOverlay : public NITFilter
{
    public:
        /** \brief Construct a NITImageOverlay object
         *
         * Currently, the supported image formats are "png", "jpeg", "tiff" and "bmp".\n
         * The supported pixel formats in the file are gray(0,255), gray(0.0,1.0), rgb and rgba.\n
         * The overlay-ed image is converted to the same format as the frame format.\n
         * A transparent color can be applied. In this case, all the pixels in the overlay-ed image with this color are not copied to the frame.\n
         * The image is clipped to the boundaries of the frame.
         *
         * \param image_file The full path to the image to overlay.
         * \param x_pos, y_pos The upper left corner of the position of the overlay-ed image in the frame.
         * \param opacity The opacity level range [0.0,1.0].
         *
         * \throw NITException if the file doesn't exist.
         * \throw NITException if the file format is not supported.
         * \throw NITException if the opacity is out of range.
         */
        NITImageOverlay( const std::string& image_file, unsigned int x_pos, unsigned int y_pos, float opacity = 1.0f )
        {
            Init( image_file.c_str(), x_pos, y_pos, opacity );
        }

        /** \brief Destructor */
        NITDLL_API ~NITImageOverlay();

        /** \brief Change the overlay-ed image, position and opacity
         *
         * \param new_image_file The full path to the image to overlay.
         * \param x_pos, y_pos The upper left corner of the position of the overlay-ed image in the frame.
         * \param opacity The opacity level range [0.0,1.0].
         *
         * \throw NITException if the file doesn't exist.
         * \throw NITException if the file format is not supported.
         * \throw NITException if the opacity is out of range.
         */
        void setImageFile( const std::string& new_image_file, unsigned int x_pos, unsigned int y_pos, float opacity = 1.0f )
        {
            SetImageFile( new_image_file.c_str(), x_pos, y_pos, opacity );
        }

        /** \brief Change the overlay-ed image
         *
         * \param new_image_file The full path to the image to overlay.
         *
         * \throw NITException if the file doesn't exist.
         * \throw NITException if the file format is not supported.
         */
        void setImageFile( const std::string& new_image_file )
        {
            SetImageFile( new_image_file.c_str() );
        }

        /** \brief return the overlay-ed image full path
         *
         * \throw return the overlay-ed image full path.
         */
        std::string getImageFile() const
        {
            std::vector< char > tmp(512);
            unsigned int data_size( (unsigned int)tmp.size());
            if( !GetImageFile( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                GetImageFile( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }

        /** \brief Change the overlay-ed image position
         *
         * \param x_pos, y_pos The upper left corner of the position of the overlay-ed image in the frame.
         *
         * \throw NITException if the file format is not supported.
         * \throw NITException if the opacity is out of range.
         */
        NITDLL_API void setPosition( unsigned int x_pos, unsigned int y_pos );

        /** \brief Change the overlay-ed image X position
         *
         * \param x_pos The left side of the position of the overlay-ed image in the frame.
         */
        NITDLL_API void setPosX( unsigned int x_pos );

        /** \brief Change the overlayed image Y position
         *
         * \param y_pos The upper side of the position of the overlay-ed image in the frame.
         */
        NITDLL_API void setPosY( unsigned int y_pos );

        /** \brief Change the overlay-ed image opacity
         *
         * \param new_opacity The opacity level range [0.0,1.0].
         *
         * \throw NITException if the opacity is out of range.
         */
        NITDLL_API void setOpacity( float new_opacity );

        /** \brief Set the color to use as transparency color (color version)
         *
         * All the pixels in the overlay-ed image with this color are not copied to the frame.\n
         * If the frame is gray, the transparent color is converted to the range [0.0, 1.0] with this formula:\n
         *  <em>transparent_gray = ( ((float)(r + g + b ))/3 ) / 255</em>
         *
         * \param r,g,b red, green, and blue value of the transparency color in the range [0,255]
         */
        NITDLL_API void setTransparentColor( unsigned char r, unsigned char g, unsigned char b );

        /** \brief Set the color to use as transparency color
         *
         * All the pixels in the overlay-ed image with this color are not copied to the frame.\n
         * If the frame is rgba, the transparent color is converted to color in the range [0, 255] with this formula:\n
         *     <em>transparent_color = [gray*255, gray*255, gray*255, 0]</em>
         *
         * \param gray value of the transparency color in the range [0.0,1.0]
         */
        NITDLL_API void setTransparentColor( float gray );

        /** \brief Enable/Disable the use of the transparency color
         *
         * \param enable If true the transparency color is applied, else not
         */
        NITDLL_API void enableTransparentColor( bool enable );

        /** \brief Fill the passed variables with the position.
         *
         * \param x_pos, y_pos variables to be filled
         */
        NITDLL_API void getPosition( unsigned int& x_pos, unsigned int& y_pos );

        /** \brief return the X position of the overlay-ed image.
         *
         * \return return the X position of the overlay-ed image.
         */
        NITDLL_API unsigned int getPosX() const;

        /** \brief return the Y position of the overlay-ed image.
         *
         * \return return the Y position of the overlay-ed image.
         */
        NITDLL_API unsigned int getPosY() const;

        /** \brief return the current opacity value.
         *
         * \return return the current opacity value.
         */
        NITDLL_API float getOpacity() const;

        /** \brief return if the transparent color is enabled.
         *
         * \return true if enabled, else false.
         */
        NITDLL_API bool isTransparentColorEnabled() const;

    private:
        class Impl;
        Impl* impl;

        NITDLL_API void Init( const char*, unsigned int, unsigned int, float );
        NITDLL_API void SetImageFile( const char*, unsigned int, unsigned int, float );
        NITDLL_API void SetImageFile( const char* );
        NITDLL_API bool GetImageFile( char*, unsigned int& ) const;
        NITDLL_API void onNewFrame( NITFrame& );
};
    }
}
#endif // NITIMAGEOVERLAY_H
