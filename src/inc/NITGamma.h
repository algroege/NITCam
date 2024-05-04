#ifndef NITGAMMA_H
#define NITGAMMA_H

#include <NITFilter.h>

namespace NITLibrary {
    namespace NITToolBox {
/** \brief Permit to adjust the gamma of the image
 *
 * \see https://en.wikipedia.org/wiki/Gamma_correction
 *
 * Gamma correction is only supproted on gray scale frames.
 *
 * The gamma curve is described as an "S-Curve" as below:
 * You can modify 2 parameters: the gamma factor and the center of the curve. If the value is less than the center the LUT curve red is applied and if it is greater than the center value, the LUT curve in blue is applied.
 * \image html gamma.png
 */
class NITGamma : public NITFilter
{
    public:
        /** \brief Construct a NITGamma object
         *
         * \param new_center center value in the range [0.0, 1.0]
         * \param new_gamma gamma value in the range [0.1,3.0]
         *
         * \throw NITException if new_center or new_gamma are out of range
         */
        NITDLL_API NITGamma( float new_center = 0.5, float new_gamma = 0.5 ); //center compris entre 0.0 et 1.0
                                                                              //gamma compris entre  0.0 et 3.0

        /** \brief Destructor */
        NITDLL_API virtual ~NITGamma();

        /** \brief set a new center value
         *
         * \param new_center center value in the range [0.0, 1.0]
         *
         * \throw NITException if new_center is out of range
         */
        NITDLL_API void setCenter( float new_center );

        /** \brief return the current center value
         *
         * \return current center value
         */
        NITDLL_API float getCenter() const;

        /** \brief set a new gamma value
         *
         * \param new_gamma gamma value in the range [0.0, 3.0]
         *
         * \throw NITException if new_gamma is out of range
         */
        NITDLL_API void setGamma( float new_gamma );

        /** \brief return the current gamma value
         *
         * \return current gamma value
         */
        NITDLL_API float getGamma() const;

    private:
        float center, gamma;

        class Impl;
        Impl* impl;

        void onNewFrame( NITFrame& );
};
    }
}
#endif // NITGAMMA_H
