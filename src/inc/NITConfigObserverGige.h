#ifndef NITCONFIGOBSERVERGIGE_H
#define NITCONFIGOBSERVERGIGE_H

#include "NITConfigObserver.h"
#include "NITGige.h"
//#include "NITGigeDeviceBase.h"

class NITGigeDeviceBase;

namespace NITLibrary {

    class NITException;

    /** \brief Permits to the user of the SDK to be informed of changes in a Gige camera
     *
     * This class is pure virtual.\n
     * To receive informations about the camera changes, you have to derive from this class and overload the functions.\n
     * The derived class object must then be connected to a NITDevice.
     *
     * As soon a the object is connected to a NITDevice, onNewGroup is called for each Gige group of parameters and \n
     * onNewParam is called for each parameter of the camera.\n
     * This permit to obtain the name of all supported parameter, there current range and current value.\n
     */
	class NITConfigObserverGige : public NITConfigObserver
	{
	protected:
        /** \brief Construct a NITConfigObserverGige object  */
		NITDLL_API NITConfigObserverGige() {}
        /** \brief Destructor  */
		NITDLL_API virtual ~NITConfigObserverGige() {}

        /**\brief Called when the NITConfigObserverGige is connected to the camera.
         *
         * \param group_name: name of the gige group of parameters.
         *
         * \threading This function is called in the thread where the object was connected to the NITDevice.
         */
		NITDLL_API virtual void     onNewGroup( const char* group_name ) = 0;
        /// @{
        /** \brief Called when the NITConfigObserverGige is connected to the camera.
         *
         * \param group_name: name of the gige group of this parameters.
         * \param param: a structure giving informations about the parameter.
         *
         * \threading This functions are called in the thread where the object was connected to the NITDevice.
         */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::BoolParam& param) = 0;
		/** \overload void     onNewParam( const char* group_name, const Gige::IntParam& param) = 0 */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::IntParam& param) = 0;
		/** \overload void     onNewParam( const char* group_name, const Gige::FloatParam& param) = 0 */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::FloatParam& param) = 0;
		/** \overload void     onNewParam( const char* group_name, const Gige::EnumParam& param) = 0 */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::EnumParam& param) = 0;
		/** \overload void     onNewParam( const char* group_name, const Gige::StringParam& param) = 0 */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::StringParam& param) = 0;
		/** \overload void     onNewParam( const char* group_name, const Gige::CommandParam& param) = 0 */
		NITDLL_API virtual void     onNewParam( const char* group_name, const Gige::CommandParam& param) = 0;
        ///@}
        /** \brief Called when a parameter is changed.
         *
         * A parameter can change because a call was made to NITDevice::setParamValueOf() or NITDevice::setFps() or because the parameter is a dependant parameter( it depend from the state of another parameter).
         *
         * \param param_name: name of the parameter who was changed.
         * \param str_value: new value of the parameter in string format.
         * \param num_value: new value of the parameter in numeric format.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() function was called.
         */
		NITDLL_API virtual void		onParamChanged( const char* param_name, const char* str_value, float num_value )
		{
		    //std::cout << "NITConfigObserverGige::onParamChanged " << param_name << std::endl;
		}

        /** \brief Called when a parameter range is changed.
         *
         * A parameter range can change because the parameter is a dependant parameter( it depend from the state of another parameter ).
         *
         * \param param_name: name of the parameter who was changed.
         * \param str_values: pointer to an array of new values of the parameter in string format.
         * \param num_values: pointer to an array of new values of the parameter in numeric format.
         * \param array_size: size of the arrays.
         * \param cur_str_val: new current value of the parameter in string format.
         * \param cur_num_val: new current value of the parameter in numeric format.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() function was called.
         */
		NITDLL_API virtual void	    onParamRangeChanged( const char* param_name, const char* str_values[], const float* num_values, unsigned int array_size,
                                                  const char* cur_str_val, float cur_num_val )
		{
		    //std::cout << "NITConfigObserverGige::onParamRangeChanged " << param_name << std::endl;
		}

        /** \brief Called when the frame rate is changed.
         *
         * The frame rate can change because a call was made to NITDevice::setParamValueOf() or NITDevice::setFps().
         *
         * \param new_fps: new value of the frame rate.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         */
        NITDLL_API virtual void     onFpsChanged( double new_fps )
		{
		    //std::cout << "NITConfigObserverGige::onFpsChanged " << new_fps << std::endl;
		}

        /** \brief Called when the current frame rate range is changed.
         *
         * The frame rate range can change because a call was made to NITDevice::setParamValueOf() or NITDevice::setFps().
         *
         * \param new_fpsMin, new_fpsMax: new value of the frame rate range.
         * \param new_fps: new value of the frame rate.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         */
        NITDLL_API virtual void     onFpsRangeChanged( double new_fpsMin, double new_fpsMax, double new_fps )
		{
		    //std::cout << "NITConfigObserverGige::onFpsRangeChanged " <<new_fps << std::endl;
		}
        /** \brief Called when external NUC is active and changed.
         *
         * Gige cameras embeds Nucs(this are internal Nucs).\n
         * This internal Nucs can be deactivated and external Nucs can be activated in the NITDevice object.\n
         * This function applies only to external Nucs.\n
         * Each time some parameters like exposure are changed, the current nuc if enabled is changed.\n
         * This function notify the application of the changes.\n
         * A status number indicates which kind of nuc is applied:\n
         * If status is -1: The selected exposure time is below or above the exposure times for which a Nuc file exists.\n
         * If status is 0: The Nuc is an exact Nuc coming from one of the Nuc files for the current exposure.\n
         * If status is 1: The Nuc is interpolated with the nearest Nuc files corresponding to the current exposure.\n
         *
         * \param nuc_str: a string representing the current NUC.
         * \param status: status of the applied nuc
         *
         *  \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         *
         */
		NITDLL_API virtual void	    onNucChanged( const char* nuc_str, int status )
		{
		    //std::cout << "NITConfigObserverGige::onNucChanged " << nuc_str << std::endl;
		}

		// Friend
		friend /*class*/ NITGigeDeviceBase;
	};
}

#endif // NITCONFIGOBSERVERGIGE_H_INCLUDED
