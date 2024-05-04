#ifndef DEMOSAICING_H_INCLUDED
#define DEMOSAICING_H_INCLUDED

#include "NITImpExp.h"
#include "NITDevice.h"

namespace NITLibrary
{
     /** \brief namespace of the functions relative to demosaicing, only applicable to color cameras.
     *
     * USB:\n
     * NIT visible USB color cameras output RAW bayer data.\n
     * By default, this data is passed to the pipeline filters as float gray pixels.\n
     * If demosaicing filter is activated, the RAW bayer data is demosaiced. As a result, data is
     * passed to the pipeline filters as RGBA pixels (32bits).\n
     * GIGE:
     * NIT visible GIGE color cameras can output data as correction_Color data. In this case, an internal debayering is applied.\n
     * One can also set the output format of the camera to Bayer_GR16. In this case the output is RAW data( internal debayering is not active).\n
     * In this case, the SDK debayering can be applied by activationg it.\n
     * \image html demosaic.png "Demosaicing process"
     */
    namespace Demosaicing
    {
        /** \brief activate or deactivate the demosaicing filter
         *
         * GIGE: Activating SDK debayering disable automatically internal debayering
         *
         * \param dev The device for which demosaicing must be activated. This device must be color capable.
         * \param b_activate If true the demosaicing is activated, else the demosaicing is deactivated
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         */
        NITDLL_API void activate( NITDevice* dev, bool b_activate = true );
        /** \brief return the demosaicing state
         *
         * \return true if demosaicing active, else false.
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         */
        NITDLL_API bool active( NITDevice* );

        /** \brief Set the value of the luminosity gain involved in the crosstalk compensation process.
         *
         * \param dev The device for which demosaicing must be activated. This device must be color capable.
         * \param value to be set. range: [1.0,15.0], default value: 5.0
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         * \throw NITException if value is out of range.
         */
        NITDLL_API void setLuminosityGain( NITDevice* dev, double value );
        /** \brief return the current luminosity gain value.
         *
         * \param dev The device for which getLuminosityGain must return a value. This device must be color capable.
         *
         * \return return the current luminosity gain value.
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         */
        NITDLL_API double getLuminosityGain( NITDevice* dev );

        /** \brief Set the value of the color saturation involved in the last stage of the demosaicing process.
         *
         * \param dev The device for which demosaicing must be activated. This device must be color capable.
         * \param value to be set. range: [0.1,5.0], default value: 1.0
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         * \throw NITException if value is out of range.
         */
        NITDLL_API void setColorSaturation( NITDevice* dev, double value );
        /** \brief return the current color saturation value.
         *
         * \param dev The device for which getColorSaturation must return a value. This device must be color capable.
         *
         * \return return the current color saturation value.
         *
         * \throw NITException if dev is not a device supporting Demosaicing( currently only MC1003 can be demosaiced ).
         */
        NITDLL_API double getColorSaturation( NITDevice* dev );
    }
}

#endif // DEMOSAICING_H_INCLUDED
