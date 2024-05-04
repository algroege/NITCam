#ifndef NITCOLORMAP_H
#define NITCOLORMAP_H

#include <NITFilter.h>

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Apply a color Lut on grayscale frames. */
class NITColorMap : public NITFilter
{
    public:
        /** \brief color map enumeration */
        enum { NONE,        /**< no colormap applied */
                AUTUMN,     /**< autumn colormap */
                BONE,      /**<  bone colormap */
                JET,      /**<  jet colormap */
                WINTER,      /**<  winter colormap */
                RAINBOW,      /**<  rainbow colormap */
                OCEAN,      /**<  ocean colormap */
                SUMMER,      /**<  summer colormap */
                SPRING,      /**<  spring colormap */
                COOL,      /**<  cool colormap */
                HSV,      /**<  hsv colormap */
                PINK,      /**<  pink colormap */
                HOT,      /**<  hot colormap */
                NIGHT_VISION      /**<  night vision  colormap*/
            };
        /** \brief Construct a NITColorMap object
         *
         * \param color_map: index of the color Lut to apply
         *
         * \throw NITException if the color_map index is out of range
         */
        NITDLL_API NITColorMap( unsigned int color_map = NONE );
        /** \brief Destructor */
        NITDLL_API ~NITColorMap();
        /** \brief Change the color Lut
         *
         * \param new_color_map: index of the color Lut to apply
         *
         * \throw NITException if the color_map index is out of range
         */
        NITDLL_API void setColorMap( unsigned int new_color_map );
        /** \brief  return the current color map index
         *
         * \return return the current color map index
         */
        NITDLL_API unsigned int getColorMap() const;

    private:
        class Impl;
        Impl* impl;
        unsigned int curIndex;

        void onNewFrame( NITFrame& );
};
    }
}
#endif // NITCOLORMAP_H
