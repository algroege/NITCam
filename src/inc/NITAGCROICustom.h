#ifndef NITAGCROICUSTOM_H
#define NITAGCROICUSTOM_H

#include "NITAutomaticGainControl.h"

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Filter who apply an histogram stretching based on a region of interest.
 * This filter is not applied on color input frames.
 *
 * This filter calculate an histogram on the defined region of interest.\n
 * \snippet{doc} snippets AgcDetail
 */
class NITAGCROICustom : public NITAutomaticGainControl
{
    public:
        /** \brief Construct a NITAGCROI object.
         *
         * \param roi: region of interest to use to calculate the histogram.
         * \param ignored_below, ignored_above: number of pixels to ignore on each side of the histogram to decide the min and max value of the histogram.
         */
        NITDLL_API NITAGCROICustom( const Roi& roi, unsigned int ignored_below = 200, unsigned int ignored_above = 200 );
        /** \brief Destructor */
        NITDLL_API ~NITAGCROICustom();
        /** \brief Set a new region of interest.
         *
         * \param roi: region of interest to use to calculate the histogram.
         */
        NITDLL_API void setRoi( const Roi& roi );
        /** \brief return the current region of interest.
         *
         * \return return the current region of interest.
         */
        NITDLL_API Roi getRoi() const;
};
    }
}
#endif // NITAGCROICUSTOM_H
