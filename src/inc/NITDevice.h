#ifndef NITDEVICE_H
#define NITDEVICE_H

#include "NITImpExp.h"
#include <string>
#include <vector>


namespace NITLibrary {

class NITFilter;
class NITObserver;
class NITConfigObserver;


	enum FxType
	{
		FX2,								/*!< FX2 chip */
		FX3                                 /*!< FX3 chip */
	};

/** \brief Main class which describe the active camera
 *
 * Thrue this class, you can set and get the camera parameters and initiate the capture of frames.\n
 * You can't instantiate directly this class. Instead, NITManager will return an instance of this class when you call one of the open functions.
 * \see NITManager::openOneDevice(), NITManager::openDevice(), NITManager::openBySerialNumber()
 *
 */
class NITDevice
{
    public:
		NITDLL_API  virtual unsigned int    sensorWidth() const = 0;     //!< Return the sensor width
		NITDLL_API  virtual unsigned int    sensorHeight() const = 0;    //!< Return the sensor height
        /** \brief Return the type of the connector on which the camera is connected.
         *
         *   Can return one of USB_2, USB_3 or GIGE
         *   This is the connector on the host side, notably for USB cameras if an USB3 camera is connected to an USB2 connector on the host side,
         *   this function will return USB_2.
         */
		NITDLL_API  virtual ConnectorType   connectorType() const = 0;
		NITDLL_API  virtual unsigned int    connectorNumber() const = 0; //!< Return the index of the camera in the NITManager list.
        /** \brief Return the commercial name of the camera. */
                            std::string	    commercialName() const
		{
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !CommercialName( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                CommercialName( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
		}
        /** \brief Return the sensor model of the camera. like NSC1003 */
            std::string		modelId() const
		{
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !ModelId( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                ModelId( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
		}
        /** \brief Return the FGPA firmware version of the camera. */
                            std::string		firmwareVersion() const
        {
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !FirmwareVersion( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                FirmwareVersion( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }
        /** \brief Return the serial number of the camera. */
            std::string		serialNumber() const
        {
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !SerialNumber( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                SerialNumber( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }
        /** \brief Set the directory containing the NUC files
         *
         *  The path(if not empty) must point to a writeable directory containing a directory named 'NUC'.\n
         *  If directory path is valid, the automatic nuc interpolation is activated.\n
         *  If directory path is empty, the nuc filtering is deactivated.\n
         *  If is_bpr_path is true, the bad pixel recovery is also activated with the files contained in this path.
         *
         * \param dir_path path to the directory
         * \param is_bpr_path true if the directory contain also the bpr files
         *
         * \throw NITException if the directory doesn't exist
         * \throw NITException if the directory doesn't contain a directory named 'NUC'
         * \throw NITException if the directory isn't writeable
         */
        void    setNucDirectory( const std::string& dir_path, bool is_bpr_path = true ) { SetNuc( dir_path.c_str(), is_bpr_path ); }
        /** \brief Set a NUC file
         *
         *  The path(if not empty) must point to a valid NUC file.\n
         *  The nuc interpolation is deactivated and the NUC in this file is applied regardless the parameter changes.\n
         *  If file_path is empty, the nuc filtering is deactivated.
         *
         * \param file_path path to the NUC file
         *
         * \throw NITException if the file doesn't exist
         * \throw NITException has not an 'yml' extension
         */
        void    setNucFile( const std::string& file_path )                              { SetNuc( file_path.c_str(), false ); }
        /** \brief Set the directory containing the BPR files
         *
         *  The path(if not empty) must point to a directory containing a directory named 'NUC'.\n
         *  If directory path is valid, the automatic bad pixel correction is activated.\n
         *  If directory path is empty, the bad pixel correction filtering is deactivated.
         *
         * \param dir_path path to the directory
         *
         * \throw NITException if the directory doesn't exist
         * \throw NITException if the directory doesn't contain a directory named 'NUC'
         */
        void    setBprDirectory( const std::string& dir_path )                          { SetBpr( dir_path.c_str() ); }
        /** \brief Set a BPR file
         *
         *  The path(if not empty) must point to a valid BPR file.\n
         *  The bad pixel correction in this file is applied regardless the parameter changes.\n
         *  If file_path is empty, the bad pixel correction is deactivated.
         *
         * \param file_path path to the BPR file
         *
         * \throw NITException if the file doesn't exist
         * \throw NITException has not an 'yml' extension
         */
        void    setBprFile( const std::string& file_path )                              { SetBpr( file_path.c_str() ); }

        /** \brief Activate/Deactivate the nuc processing
         *
         *  \attention The nuc processing is only activated if a valid nuc path or nuc file exists.
         *
         * \param activate if true try to activate the nuc processing, else deactivate the nuc processing
         */
        NITDLL_API virtual void    activateNuc( bool activate = true ) = 0;
        /** \brief Activate/Deactivate the bpr processing
         *
         *  \attention The bpr processing is only activated if a valid bpr path or bpr file exists.
         *
         * \param activate if true try to activate the bpr processing, else deactivate the bpr processing
         */
        NITDLL_API virtual void    activateBpr( bool activate = true ) = 0;

        /** \brief return the state of the nuc processing
         *
         * \return true if nuc processing active, else return false.
         */
        NITDLL_API virtual bool    nucActive() const = 0;

        /** \brief return the state of the bpr processing
         *
         * \return true if bpr processing active, else return false.
         */
        NITDLL_API virtual bool    bprActive() const = 0;

        /** \brief Set the frame rate
         *
         *  Set the nearest frame rate possible in the range delimited by NITDevice::minFps() and NITDevice::maxFps()
         *
         * \param new_fps
         *
         * \emit NITConfigObserver::onFpsChanged
         */
		NITDLL_API virtual void             setFps( double new_fps) = 0;
		NITDLL_API virtual double			fps() const = 0;                //!<  Return the current frame rate
		NITDLL_API virtual double			minFps() const = 0;             //!<  Return the currently minimum frame rate
		NITDLL_API virtual double			maxFps() const = 0;             //!<  Return the currently maximum frame rate

        /** \brief Set the position and dimensions of the returned frames
         *
         *  This function permit to set the region of interest atomically.
         *  When you call setParamValueOf with 'Number of lines', the SDK sum this new value with the current value of 'First line'.\n
         *  If this sum is above the sensor height, an exception is thrown. This can lead to tricky situations.
         *  Let say sensor height is 512 and the current 'First line' is 10 and the current 'Number of lines' is 502.\n
         *  If you want to set 'Number of Lines to 507, you first have to set 'First line' below 6 and then set 'Number of lines' to 507.\n
         *  If you do it the other side, the SDK will throw.
         *
         *  setRoi permit to avoid this situation. The sum is made with the parameters passed to the function.
         *
         * \param offset_x, offset_y, width, height roi elements.
         *
         * \emit NITConfigObserver::onParamChanged for each parameter who as effectively changed.
         *
         * \throw NITException if the offset_x + width or offset_y + height is above the sensor dimensions
         */
		NITDLL_API virtual void setRoi( unsigned int offset_x, unsigned int offset_y, unsigned int width, unsigned int height) = 0;

        /** \brief Return the current value of the parameter paramName in numeric format
         *
         *  The current value is the value in the camera.
         *  \code double clock = dev->paramValueOf( "PixelClock" ); //Return the value in the camera let say 25.0
         *   dev->setParamValueOf( "PixelClock", 50.0 );       //The new value is not yet sent to the camera
         *   clock =  dev->paramValueOf( "PixelClock" );       //Return the value in the camera which is allways 25.0
         *   dev->updateConfig();                              //The new value is sent to the camera
         *   clock =  dev->paramValueOf( "PixelClock" );       //Return the value in the camera which now 50.0 \endcode
         *  For parameters where the numeric format have a meaning, the returned value is the current value.
         *  \code double expo = dev->paramValueOf( "ExposureTime" ); //can return 200.0 for example \endcode
         *  For parameters who are enumerations, the return value is the index of the enumeration.
         *  \code unsigned int current_mode = dev->paramValueOf( "Mode" ); //can return 0 if capture mode is 'Global Shutter' \endcode
         *
         * \param paramName For a list of available parameters see the page corresponding to your camera.
         *
         * \throw NITException if paramName is not supported by the current camera.
         */
		double paramValueOf(const std::string& paramName ) const
		{
		    return ParamValueOf( paramName.c_str() );
		}
        /** \brief Return the current value of the parameter paramName in string format
         *
         *  The current value is the value in the camera.
         *  \code std::string clock = dev->paramStrValueOf( "PixelClock" ); //Return the value in the camera let say "25MHz"
         *   dev->setParamValueOf( "PixelClock", "50MHz" );            //The new value is not yet sent to the camera
         *   clock =  dev->paramStrValueOf( "PixelClock" );            //Return the value in the camera which is allways "25MHz"
         *   dev->updateConfig();                                      //The new value is sent to the camera
         *   clock =  dev->paramStrValueOf( "PixelClock" );            //Return the value in the camera which now "50MHz" \endcode
         *
         * \param paramName For a list of available parameters see the page corresponding to your camera.
         *
         * \throw NITException if paramName is not supported by the current camera.
         */
		std::string paramStrValueOf(const std::string& paramName) const
		{
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !ParamStrValueOf( paramName.c_str(), tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                ParamStrValueOf( paramName.c_str(), tmp.data(), data_size );
            }
            return std::string( tmp.data() );
		}

        /** \brief Prepare to change the current value of the parameter paramName in unsigned int numeric format
         *
         * This form of the function apply to parameters where unsigned int values have a meaning like 'Number of Column'.\n
         * The change is sent to the camera on the next call to NITDevice::updateConfig().\n
         * For some parameters the change may induce modifications of other parameters.\n
         * The return value permit to chain calls.\n
         * USB: The parameter is sent to the camera on the next call to updateConfig().\n
         * GIGE: The parameter is sent to the camera immediatly.\n
         * \code dev->setParamValueOf( "OneParameter", OneValue ).setParamValueOf( "AnotherParameter", "anotherValue" ).updateConfig(); \endcode
         * Numeric value as to be desambiguated.\n
         * \code dev->setParamValueOf( "OneParameter", 1 ) //ambiguous
         * dev->setParamValueOf( "OneParameter", 1u ).dev->setParamValueOf( "OneParameter", (unsigned int)1 ) //unambiguous \endcode
         * \param paramName For a list of available parameters see the page corresponding to your camera.
         * \param value The new value to apply.
         *
         * \return *this
         *
         * \throw NITException if paramName is not supported by the current camera.
         * \throw NITException if value is out of range or not applicable to the current camera.
         */
        NITDevice& setParamValueOf(const std::string& paramName, unsigned int value)        { return SetParamValueOf( paramName.c_str(), value ); }

        /** \brief Prepare to change the current value of the parameter paramName in double format
         *
         * This form of the function apply to parameters where double values have a meaning like 'Pixel Clock'.\n
         * The change is sent to the camera on the next call to NITDevice::updateConfig().\n
         * For some parameters the change may induce modifications of other parameters.\n
         * The return value permit to chain calls
         * USB: The parameter is sent to the camera on the next call to updateConfig().\n
         * GIGE: The parameter is sent to the camera immediatly.\n
         * \code dev->setParamValueOf( "OneParameter", OneValue ).setParamValueOf( "AnotherParameter", "anotherValue" ).updateConfig(); \endcode
         * Numeric value as to be desambiguated.\n
         * \code dev->setParamValueOf( "OneParameter", 1 ) //ambiguous
         * dev->setParamValueOf( "OneParameter", 1.0 ).dev->setParamValueOf( "OneParameter", (double)1 ) //unambiguous \endcode
         * \param paramName For a list of available parameters see the page corresponding to your camera.
         * \param value The new value to apply.
         *
         * \return *this
         *
         * \throw NITException if paramName is not supported by the current camera.
         * \throw NITException if value is out of range or not applicable to the current camera.
         */
        NITDevice& setParamValueOf(const std::string& paramName, double value)              { return SetParamValueOf( paramName.c_str(), value ); }

        /** \brief Prepare to change the current value of the parameter paramName in string format
         *
         * This form of the function apply to all parameters.\n
         * The change is sent to the camera on the next call to NITDevice::updateConfig().\n
         * For some parameters the change may induce modifications of other parameters.\n
         * The return value permit to chain calls.
         * \code dev->setParamValueOf( "OneParameter", OneValue ).setParamValueOf( "AnotherParameter", "anotherValue" ).updateConfig(); \endcode
         * \param paramName For a list of available parameters see the page corresponding to your camera.
         * \param value The new value to apply.
         *
         * \return *this
         *
         * \throw NITException if paramName is not supported by the current camera.
         * \throw NITException if value is ill-formed.
         * \throw NITException if value is out of range or not applicable to the current camera.
         */
		NITDevice& setParamValueOf(const std::string& paramName, const std::string& value)  { return SetParamValueOf( paramName.c_str(), value.c_str() ); }

        /** \brief Call the NITConfigObserver functions to notify the parameter changes
         *
         * USB: Send the changed parameters to the camera.
         * \emit NITConfigObserver::onParamChanged for all changed parameters\n
         * NITConfigObserver::onParamRangeChanged if needed\n
         * NITConfigObserver::onFpsChanged if needed\n
         * NITConfigObserver::onFpsRangeChanged if needed\n
         *
         */
		NITDLL_API virtual void         updateConfig() = 0;

        /** \brief Start the capture
        *
        *   The streaming run until NITDevice::stop() is called.
        *
        * \emit NITConfigObserver::onNewFrame() For each received frame
        * \threading The capture don't run in the current thread
        * \throw NITException if the streaming is currently running
        */
		NITDLL_API virtual void			start() = 0;
        /** \brief Start the capture until n frames are captured
        *
        * The streaming stop automatically when the number of frames has been captured.
        * This function must be coupled with NITDevice::waitEndCapture()
        * \code dev->captureNFrames( 10 );
        *  dev->waitEndCapture(); \endcode
        * \param n The number of frames to capture
        * \param error_increment_count If false a dropped frame don't increment the counter
        * \emit NITConfigObserver::onNewFrame() For each received frame
        * \threading The capture don't run in the current thread
        *
        * \throw NITException if the streaming is currently running
        */
		NITDLL_API virtual void			captureNFrames(size_t n, bool error_increment_count = false ) = 0;
        /** \brief Start the capture for a duration
        *
        * The streaming stop automatically when the time has elapsed.
        * This function must be coupled with NITDevice::waitEndCapture()
        * \code dev->captureForDuration( 1000 ); //Capture for 1 second
        *  dev->waitEndCapture(); \endcode
        * \param milliseconds The number of milliseconds to capture
        * \emit NITConfigObserver::onNewFrame() For each received frame
        * \threading The capture don't run in the current thread
        * \throw NITException if the streaming is currently running
        */
		NITDLL_API virtual void			captureForDuration(unsigned long milliseconds) = 0;

        /** \brief Stop the capture
        */
		NITDLL_API virtual void			stop() = 0;
        /** \brief Block the current thread until the capture is done
        *
        * This function is coupled with NITDevice::captureNFrames() or NITDevice::captureForDuration()
        * \code dev->captureForDuration( 1000 ); //Capture for 1 second
        *  dev->waitEndCapture(); \endcode
        *
        * \param timeout The maximum number of milliseconds to wait for the end of capture.\n
        *        If -1, the function wait until the job is done.\n
        *        If a timeout occurs, the streaming is stopped.
        * \return false if the function timed out, else true if the job was honored
        */
		NITDLL_API virtual bool			waitEndCapture( int timeout = -1 ) = 0;

        /** \brief Permit to connect a NITFilter derived object
        * \return The a reference to the NITFilter object for chaining \code (dev) << filter << filter2 << observer1; \endcode
        */
		NITDLL_API virtual NITFilter&   operator<<( NITFilter& ) = 0;
        /** \brief Permit to connect a NITObserver derived object
        *
        */
		NITDLL_API virtual void         operator<<( NITObserver& ) = 0;
        /** \brief Permit to connect a NITConfigObserver derived object
        *
        */
		NITDLL_API virtual void         operator<<( NITConfigObserver& ) = 0;


		NITDLL_API virtual void         computeLowPoint( bool preserve_gain ) = 0;
		NITDLL_API virtual void         computeHighPoint() = 0;
		                   void         generateNuc( const std::string& filename ) { GenerateNuc( filename.c_str() ); }
        /** \brief Return the current path of the NUC
        * \return Return the current path of the NUC
        */
        std::string getCurrentNucPath() const
        {
            std::vector< char > tmp(512);
            size_t data_size( tmp.size());
            if( !GetCurrentNucPath( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                GetCurrentNucPath( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }
        virtual ~NITDevice();
    protected:
         NITDevice();

   private:

        NITDLL_API virtual bool         CommercialName( char*, size_t& ) const = 0;
        NITDLL_API virtual bool         ModelId( char*, size_t& ) const = 0;
        NITDLL_API virtual bool         FirmwareVersion( char*, size_t& ) const = 0;
        NITDLL_API virtual bool         SerialNumber( char*, size_t& ) const = 0;

		NITDLL_API  virtual void        SetNuc( const char* dir_path, bool is_bpr_path ) = 0;
		NITDLL_API  virtual void        SetBpr( const char* file_path ) = 0;

        NITDLL_API virtual double		ParamValueOf(const char* ) const = 0;
        NITDLL_API virtual bool         ParamStrValueOf( const char*, char*, size_t& ) const = 0;
        NITDLL_API virtual NITDevice&   SetParamValueOf(const char*, unsigned int ) = 0;
        NITDLL_API virtual NITDevice&   SetParamValueOf(const char*, double ) = 0;
        NITDLL_API virtual NITDevice&   SetParamValueOf(const char*, const char* ) = 0;

        NITDLL_API virtual void         GenerateNuc( const char* ) = 0;
        NITDLL_API virtual bool         GetCurrentNucPath( char*, size_t& ) const = 0;
};

}
#endif // NITDEVICE_H
