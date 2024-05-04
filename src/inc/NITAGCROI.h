#ifndef NITAGCROI_H
#define NITAGCROI_H

#include "NITAGCROICustom.h"

namespace NITLibrary {
    namespace NITToolBox {
/** \brief Filter who apply an histogram stretching based on predefined regions of interest.
 *
 * This filter calculate an histogram on the center half or quarter of a frame.\n
 * This filter is not applied on color input frames.
 * \snippet{doc} snippets AgcDetail
 */
class NITAGCROI : public NITAGCROICustom
{
    public:
        enum eRoiType { half,      /*!< The histogram is calculated on the center half of the frame */
                         quarter    /*!< The histogram is calculated on the center quarter of the frame */
                       };
        /** \brief Construct a NITAGCROICustom object.
         *
         * \param roi_type: predefined region of interest to use to calculate the histogram.
         * \param ignored_below, ignored_above: number of pixels to ignore on each side of the histogram to decide the min and max value of the histogram.
         */
        NITDLL_API NITAGCROI( eRoiType roi_type, unsigned int ignored_below = 200, unsigned int ignored_above = 200 );

        /** \brief Destructor */
        NITDLL_API ~NITAGCROI();

        /** \brief Set a new predefined region of interest.
         *
         * \param roi_type: predefined region of interest to use to calculate the histogram.
         */
        NITDLL_API void setRoiType( eRoiType roi_type );

        /** \brief return the current predefined region of interest.
         *
         * \return return the current predefined region of interest.
         */
        NITDLL_API eRoiType getRoiType() const;

    private:
        eRoiType roiType;

        void onNewFrame( NITFrame& frame );
};

    }
}
#endif // NITAGCROI_H
