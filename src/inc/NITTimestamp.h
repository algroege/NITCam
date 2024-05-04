#ifndef NITTIMESTAMP_H
#define NITTIMESTAMP_H

#include "NITAddText.h"

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Overlay a date time string on the current frame.
 *
 * The date time is format is: <em>YYYYMMDDTHHMMSS,fffffffff </em>.\n
 * Example: 20200220T125030,562123
 * and: <em>dd-mm-yyyy HH::MM::SS:mks</em> with mks milliseconds on three digits on Windows.\n
 * Example: 20_02-2020 12:50:30:562
 *
 * The overlay is done at the position specified and with the font specified.\n
 * If due to the size and position of the overlay, the overlay is to big to be rendered in the current frame, the overlay is cropped.
 */
class NITTimestamp : public NITAddText
{
    public:
        /** \brief Construct a NITTimestamp object.
         *
         * \param x_pos: x position of the text.
         * \param y_pos: y position of the text.
         * \param font_name: name of the TrueType font to use( as displayed in any text editor).
         *        If the name is not recognized by the system or is not a TrueType font, the default system TrueType font is used.
         *        Default font is Arial on Windows.
         *        Default font is LiberationMono on Linux (if LiberationMono is missing the best fitting font is chosen)
         * \param font_size: size of the font in points.
         */
        NITDLL_API NITTimestamp( unsigned int x_pos, unsigned int  y_pos, const std::string& font_name, unsigned int font_size );
        /** Destructor */
        NITDLL_API ~NITTimestamp();

    private:
        void onNewFrame( NITFrame& frame );
};

    }
}
#endif // NITTIMESTAMP_H
