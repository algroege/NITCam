#ifndef NITCONFIGOBSERVER_H
#define NITCONFIGOBSERVER_H

#include "NITImpExp.h"
#include <string>
#include <vector>

class NITDeviceBase;
namespace NITLibrary {

    class NITException;

    /** \brief Permits to the user of the SDK to be informed of changes in an USB camera
     *
     * This class is pure virtual.\n
     * To receive informations about the camera changes, you have to derive from this class and overload the functions.\n
     * The derived class object must then be connected to a NITDevice.
     *
     * As soon a the object is connected to a NITDevice, onParamRangeChanged is called for each parameter of the camera.\n
     * This permit to obtain the name of all supported parameter, there current range and current value.\n
     */
	class NITConfigObserver
	{
	protected:
        /** \brief Construct a NITConfigObserver object  */
		NITDLL_API NITConfigObserver() {}
        /** \brief Destructor  */
		NITDLL_API virtual ~NITConfigObserver() {}

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
		NITDLL_API virtual void		onParamChanged( const char* param_name, const char* str_value, float num_value ) = 0;

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
                                                  const char* cur_str_val, float cur_num_val ) = 0;

        /** \brief Called when the frame rate is changed.
         *
         * The frame rate can change because a call was made to NITDevice::setParamValueOf() or NITDevice::setFps().
         *
         * \param new_fps: new value of the frame rate.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         */
        NITDLL_API virtual void     onFpsChanged( double new_fps ) = 0;

        /** \brief Called when the current frame rate range is changed.
         *
         * The frame rate range can change because a call was made to NITDevice::setParamValueOf() or NITDevice::setFps().
         *
         * \param new_fpsMin, new_fpsMax: new value of the frame rate range.
         * \param new_fps: new value of the frame rate.
         *
         * \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         */
        NITDLL_API virtual void     onFpsRangeChanged( double new_fpsMin, double new_fpsMax, double new_fps ) = 0;

        /** \brief Called each time a new frame is captured.
         *
         * If the status parameter is not 0, it mean the frame was not complete or corrupted.\n
         * In this case the frame is dropped. The connected filters have no knowledge of this frame.
         *
         * \param status: status of the incoming frame. 0 if frame Ok, else not 0.
         *
         * \threading This function is called from one of the streaming threads
         *
         */
		NITDLL_API virtual void		onNewFrame( int status ) = 0;

        /** \brief Called if an error occurs in the streaming threads.
         *
         * This function permit to know if an exception was thrown in the streaming process or in one of the filters.\n
         * Generally this kind of error terminate the thread where the error occured.
         *
         * \param exc: a copy of the catched exception.
         *
         * \threading This function is called from one of the streaming threads
         *
         */
		NITDLL_API virtual void	    onInternalError( const NITException& exc ) = 0;
        /** \brief Called when NUC is changed.
         *
         * Each time some parameters like exposure are changed, the current nuc if enabled is changed.\n
         * This function notify the application of the changes.\n
         * A status number indicates which kind of nuc is applied:\n
         * If status is -1: The selected exposure time is below or above the exposure times for which a Nuc file exists. In this case\n
         * the nearest possible Nuc is applied.\n
         * If status is 0: The Nuc is an exact Nuc coming from one of the Nuc files for the current exposure.\n
         * If status is 1: The Nuc is interpolated with the nearest Nuc files corresponding to the current exposure.\n
         * If status is 2: There is no nuc in this path.\n
         * If status is 3: The Nuc is a fixed Nuc the one selected by a call to setNucFile().\n
         *
         * \param nuc_str: a string representing the current NUC.
         * \param status: status of the applied nuc
         *
         *  \threading This function is called in the thread where the NITDevice::setParamValueOf() or NITDevice::setFps() function were called.
         *
         */
		NITDLL_API virtual void	    onNucChanged( const char* nuc_str, int status ) = 0;
		NITDLL_API virtual void     onNucProcessed( int type ) {}

		// Friend
		friend /*class*/ NITDeviceBase;
	private:
		// Forbid copy of NITConfigObserver instance.
		NITConfigObserver(const NITConfigObserver& other);
		NITConfigObserver&	operator= (const NITConfigObserver& other);

	};
}

#endif // NITCONFIGOBSERVER_H
