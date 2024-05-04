#ifndef MANUALGAINCONTROL_H
#define MANUALGAINCONTROL_H

#include "NITGainControl.h"

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Filter who apply a stretching we a preset min and max value.
 * This filter is not applied on color input frames.
 *
 * Contrary to NITAutomaticGainControl and derived, the stretching is done with fixed values.
 * No histogram calculation is done.
 */
class NITManualGainControl : public NITGainControl
{
    public:
        /** \brief Construct a NITManualGainControl object.
         *
         * \param low_limit, high_limit: min value and max value used to produce the stretching.
         */
        NITDLL_API NITManualGainControl( unsigned short low_limit, unsigned short high_limit );
        /** \brief Destructor */
        NITDLL_API ~NITManualGainControl();
        /** \brief Set new values to compute the stretching.
         *
         * \param low_limit, high_limit: min value and max value used to produce the stretching.
         */
        NITDLL_API void setMinMaxValue( unsigned short low_limit, unsigned short high_limit );
};
    }
}
#endif // MANUALGAINCONTROL_H
