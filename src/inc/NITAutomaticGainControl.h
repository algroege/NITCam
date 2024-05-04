#ifndef NITAUTOMATICGAINCONTROL_H
#define NITAUTOMATICGAINCONTROL_H

#include <NITGainControl.h>

namespace NITLibrary {
    namespace NITToolBox {

#pragma pack( push, 1 )
/** \brief A simple structure to pass rectangular region of interest to the NITAGCROI filter. */
struct NITDLL_API Roi
{
    unsigned short xLeft,    /**< left coordinate */
                    xRight,  /**< right coordinate */
                    yTop,   /**< top coordinate */
                    yBottom; /**< bottom coordinate */
    /** \brief default constructor. All coordinates are set to 0 */
    Roi() : xLeft(0), xRight(0), yTop(0), yBottom(0) {}
    /** \brief constructor.
     * \param xLeft Left coordinate
     * \param xRight Right coordinate
     * \param yTop Top coordinate
     * \param yBottom Bottom coordinate
     */
    Roi( unsigned short xLeft, unsigned short xRight, unsigned short yTop, unsigned short yBottom ) : xLeft(xLeft), xRight(xRight), yTop(yTop), yBottom(yBottom) {}
    /** \brief return the emptiness of the ROI
     * An empty ROI has his width and/or height set to 0
     *
     * \return true if empty or false otherwise
     */
    bool empty() const { return (xLeft == xRight) || (yTop == yBottom); }
    /** \brief return if the ROI is valid
     * An valid ROI has at minimum one of his coordinates not 0
     *
     * \return true if valid or false otherwise
     */
    bool valid() const { return ((*(unsigned long long*)this) != 0LL); }
};
#pragma pack( pop )

/** \brief Filter who apply an histogram stretching based on the full frame.
 * This filter is not applied on color input frames.
 *
 * This filter calculate an histogram on the full frame.\n
 * \snippet{doc} snippets AgcDetail
 */
class NITAutomaticGainControl : public NITGainControl
{
    public:
        /** \brief Construct a NITAutomaticGainControl object.
         *
         * \param ignored_below, ignored_above: number of pixels to ignore on each side of the histogram to decide the min and max value of the histogram.
         */
        NITDLL_API NITAutomaticGainControl( unsigned int ignored_below = 200, unsigned int ignored_above = 200 );
        /** \brief Destructor */
        NITDLL_API ~NITAutomaticGainControl();
};

    }
}
#endif // NITAUTOMATICGAINCONTROL_H
