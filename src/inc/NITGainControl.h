#ifndef NITGAINCONTROL_H
#define NITGAINCONTROL_H

#include <NITFilter.h>

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Base class for all the histogram stretching classes.
 *
 */
class NITGainControl : public NITFilter
{
    public:
        /** \brief set the ignored pixels in the calculation process of the min max of the histogram
         *
         * \param pixels_below, pixels_above: number of pixels to ignore on each side of the histogram to decide the min and max value of the histogram.
         *
         * \see NITAutomaticGainControl, NITAGCROI, NITAGCROICustom, NITManualGainControl
         */
        NITDLL_API void setIgnoredPixels( unsigned int pixels_below, unsigned int pixels_above );
        /** \brief return the current ignored pixels
         *
         * \param pixels_below, pixels_above: on return contain the number of pixels to ignore on each side of the histogram to decide the min and max value of the histogram.
         *
         * \see NITAutomaticGainControl, NITAGCROI, NITAGCROICustom, NITManualGainControl
         */
        NITDLL_API void getIgnoredPixels( unsigned int& pixels_below, unsigned int& pixels_above ) const;
        /** \brief return the last calculated min and max value of the histogram
         *
         * \param min_value, max_value: on return contain the last calculated min and max value of the histogram.
         *        When the input frame is a color frame, the filter is not applied and min_value and max_value are set to 0.
         *
         *
         * \see NITAutomaticGainControl, NITAGCROI, NITAGCROICustom, NITManualGainControl
         */
        NITDLL_API void getMinMaxValue( unsigned short& min_value, unsigned short& max_value ) const;

        void onNewFrame( NITFrame& frame );
    protected:
        NITGainControl( unsigned int ignored_below, unsigned int ignored_above, bool automatic );
        virtual ~NITGainControl();

        class Impl;
        Impl* impl;

};
    }
}
#endif // NITGAINCONTROL_H
