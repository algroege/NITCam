#ifndef NITMANAGER_H
#define NITMANAGER_H

#include "NITImpExp.h"
#include "NITException.h"
#include "NITCl.h"

#include <memory>
#include <string>
#include <vector>
#include <functional>


template< class Func >
std::string stringWrap( Func f )
{
        std::vector< char > tmp(512);
        size_t data_size( tmp.size());
        if( !f( tmp.data(), data_size ) )
        {
            tmp.resize(data_size);
            f( tmp.data(), data_size );
        }
        return std::string( tmp.data() );
}

template< class Func >
std::string stringWrap0( Func f )
{
        std::vector< char > tmp(512);
        size_t data_size( tmp.size());
        if( !f( tmp.data(), data_size ) )
        {
            tmp.resize(data_size);
            f( tmp.data(), data_size );
        }
        return std::string( tmp.data() );
}

template< class Func >
std::string stringWrap1( Func f )
{
        std::vector< char > tmp(512);
        size_t data_size( tmp.size());
        if( !f( tmp.data(), data_size ) )
        {
            tmp.resize(data_size);
            f( tmp.data(), data_size );
        }
        return std::string( tmp.data() );
}

class DeviceInfo;

/*! @brief main namespace of the library */
namespace NITLibrary {

class NITDevice;

    namespace Gige {
        NITDevice* openByMacAddress( const std::string& mac_address );
        NITDevice* openByIpAddress( const std::string& ip_address );
        NITDevice* openByUserDefinedName( const std::string& user_name );
        bool       forceIp( const std::string& mac, const std::string& ip, const std::string& msk, const std::string& gw );
    }

    namespace ClControl {
        NITDevice* openBySerialPort( const std::string& );
        NITDevice* openWithCallback( const ClConfig& );
    }

/** \brief Manages all the connected devices and allow the instantiation of a NITDevice object to control the camera.
 *
 * This class is a singleton. A unique instance of this class is automatically created on the first call to NITManager::getInstance().
 * NITManager maintain a list of connected cameras.
 * At the call of one of the functions dealing with cameras, if the list is empty, it is populated.
 * The list of connected cameras is populated in the order the cameras are discovered.
 */
class NITManager
{
    public:
        /** \brief Instantiate the only NITManager object.
         *
         * \return a reference to the unique NITManager object.
         */
         #ifdef _WIN32
        __declspec(noinline) static NITManager& getInstance()
         #else
            __attribute__((noinline)) static NITManager& getInstance()
         #endif // _WIN32
        {
            setThrowFunction( &NITException::DefaultThrowFunc );
            return GetInstance();
        }

        /** \brief Return the current SDK version.
         *
         * Can be called without instantiating an object: \code NITManager::getSDKVersion() \endcode .
         *
         * \return string representing the SDK version in the form 3.0.0.
         */
        static std::string getSDKVersion()
        {
            return stringWrap( GetSDKVersion );
        }

        /** \brief Set on which connector type NITManager will try to discover cameras.
         *
         * Can be called without instantiating an object: \code NITManager::use( NITLibrary::USB_3|NITLibrary::GIGE ) \endcode .
         * If connector_types contains one of USB_2 or USB_3, NITManager try to find USB cameras.
         * If connector_types contains GIGE, NITManager try to find Gige cameras.
         *   The discovery process for Gige cameras is guided by the values of min_number_of_gige_cameras and max_gige_discovery_time.
         *   If min_number_of_gige_cameras == 0, NITManager try to find gige cameras until max_gige_discovery_time seconds as elapsed.
         *   If max_gige_discovery_time == 0, NITManager try to find min_number_of_gige_cameras.
         *   If both parameters are not 0, NITManager try to find min_number_of_gige_cameras. If max_gige_discovery_time as elapsed,\n
         *   NITManager returns with the number of found cameras.
         *
         * \param[in] connector_types ORed ConnectorType.
         * \param[in] connector_types min_number_of_cameras The minimum number of Gige cameras to discover.
         * \param[in] connector_types ORed ConnectorType The maximum time to search for Gige cameras( seconds ).
         * \throw NITException if GIGE connector type is set and min_number_of_gige_cameras and max_gige_discovery_time are both 0.
         */
        NITDLL_API static void use( NITLibrary::ConnectorType connector_types, unsigned int min_number_of_gige_cameras = 1, unsigned int max_gige_discovery_time = 15 );

        /** \brief Reset the NITManager object.
         *
         * After this operation, all cameras are destroyed.
         *
         */
        NITDLL_API void reset();
        /** \brief Return the number of device discovered.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \return The number of connected cameras the last time the list was populated.
         */
        NITDLL_API unsigned int deviceCount() const;

        /** \brief Return a string describing the device at index.
         *
         * \param[in] index of the device.
         * \return A string describing the camera
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the index is out of the maintened list bounds.
         */
        std::string stringDescriptor( unsigned int index) const
        {
            using namespace std::placeholders;
            return stringWrap1( std::bind( &NITManager::StringDescriptor, this, index, std::placeholders::_1, std::placeholders::_2 ) );
        }
        /** \brief Return a string describing all the devices discovered.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \return A string describing the cameras
         * \throw NITException if the maintained list is empty after discovery.
         */
        std::string listDevices() const
        {
            using namespace std::placeholders;
            return stringWrap1( std::bind( &NITManager::ListDevices, this, std::placeholders::_1, std::placeholders::_2 ) );
        }
        /** \brief Open the device at the given index.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \param[in] index The index of the device in the maintained list.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the index is out of the maintained list bounds.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if the camera at index is not a NIT camera( Gige only ).
         */
        NITDLL_API NITDevice* openDevice( unsigned int index ) const;

        /** \brief Open the first discovered device
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if the camera at index is not a NIT camera( Gige only ).
         */
        NITDLL_API NITDevice* openOneDevice() const;

        /** \brief Open a discovered device by serial number.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \param[in] sn The serial number of the queried device.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given serial number exists.
         */
        NITDevice* openBySerialNumber( const std::string& sn ) const
        {
            return OpenBySerialNumber( sn.c_str() );
        }
        std::vector< DeviceInfo* > getCurrentDeviceInfoList() const
        {
            std::vector< DeviceInfo* > tmp(10);
            size_t data_size( tmp.size());
            if( !GetCurrentDeviceInfoList( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                GetCurrentDeviceInfoList( tmp.data(), data_size );
            }
            if( data_size )
                tmp.resize( data_size );
            else
                tmp.clear();
            return tmp;
        }
        std::string stringDescriptorFromDeviceInfo( DeviceInfo* info) const
        {
            using namespace std::placeholders;
            return stringWrap1( std::bind( &NITManager::StringDescriptor2, this, info, std::placeholders::_1, std::placeholders::_2 ) );
        }
        std::string serialNumber( DeviceInfo* info ) const
        {
            using namespace std::placeholders;
            return stringWrap1( std::bind( &NITManager::SerialNumber, this, info, std::placeholders::_1, std::placeholders::_2 ) );
        }
        void updateDeviceList( const std::vector<DeviceInfo*>& dev_infos, NITDevice* dev = nullptr )
        {
            UpdateDeviceList( dev_infos.data(), dev_infos.size(), dev );
        }
        /*
        void updateDeviceList( const std::vector<DeviceInfo*>& dev_infos, const char* dev_to_keep )
        {
            UpdateDeviceList( dev_infos.data(), dev_infos.size(), dev_to_keep );
        }
        */
        NITDLL_API void releaseDevice( NITDevice* dev );

    private:
        NITManager();
        ~NITManager();

        NITDLL_API  static  NITManager& GetInstance();
        NITDLL_API  static  bool        GetSDKVersion( char* , size_t& );
        NITDLL_API          NITDevice*  OpenBySerialNumber( const char* ) const;
        NITDLL_API          NITDevice*  OpenByMacAddress( const char* ) const;
        NITDLL_API          NITDevice*  OpenByIpAddress( const char* ) const;
        NITDLL_API          NITDevice*  OpenByUserDefinedName( const char* ) const;
        NITDLL_API          bool        StringDescriptor( unsigned int index, char* , size_t& ) const;
        NITDLL_API          bool        StringDescriptor2( DeviceInfo*, char* , size_t& ) const;
        NITDLL_API          bool        ListDevices( char*, size_t& ) const;
        NITDLL_API  static  bool        ForceIp( const char*, const char*, const char*, const char* );
        NITDLL_API          bool        GetCurrentDeviceInfoList( DeviceInfo**, size_t& ) const;
        NITDLL_API          bool        SerialNumber( DeviceInfo*, char*, size_t& ) const;
        NITDLL_API          void        UpdateDeviceList( DeviceInfo* const* ptr, size_t nbre, NITDevice* dev_to_delete );
//        NITDLL_API          void        UpdateDeviceList( DeviceInfo* const* ptr, size_t nbre, const char* dev_to_keep );
        NITDLL_API          NITDevice*  OpenBySerialPort( const char* ) const;
        NITDLL_API          NITDevice*  OpenWithCallback( const ClControl::ClConfig& ) const;

        class Impl;
        std::unique_ptr< Impl > impl;

        friend NITDevice* Gige::openByMacAddress( const std::string& );
        friend NITDevice* Gige::openByIpAddress( const std::string& );
        friend NITDevice* Gige::openByUserDefinedName( const std::string& );
        friend bool Gige::forceIp( const std::string&, const std::string&, const std::string&, const std::string& );

        friend NITDevice* ClControl::openBySerialPort( const std::string& );
        friend NITDevice* ClControl::openWithCallback( const ClControl::ClConfig& );

};
    namespace Gige {
        /** \brief Open a discovered Gige device by mac address.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         * Mac address of the camera can be foud on the rear of the camera.
         * Mac address string must be in the form 70:b3:d5:2a:c0:00 (columns are mandatory).
         *
         * \param[in] mac_address The mac address of the queried device.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given mac address exists.
         */
        inline NITDevice* openByMacAddress( const std::string& mac_address )    { return NITManager::getInstance().OpenByMacAddress( mac_address.c_str() ); }
        /** \brief Open a discovered Gige device by ip address.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \param[in] ip_address The ip address of the queried device.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given ip address exists.
         */
        inline NITDevice* openByIpAddress( const std::string& ip_address )      { return NITManager::getInstance().OpenByIpAddress( ip_address.c_str() ); }
        /** \brief Open a discovered Gige device by user defined name.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \param[in] user_name The user defined name of the queried device.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given mac address exists.
         */
        inline NITDevice* openByUserDefinedName( const std::string& user_name ) { return NITManager::getInstance().OpenByUserDefinedName( user_name.c_str() ); }

        /** \brief Change the ip configuration of the device with the given mac address.
         *
         * Mac address of the camera can be foud on the rear of the camera.
         * Mac address string must be in the form 70:b3:d5:2a:c0:00 (columns are mandatory).
         * This function tries to connect to the camera with given mac_address regardless of the discovery of this device.
         * The setted IP configuration is active until the camera is powered off.
         *
         * \param[in] mac_address The mac address of the device to update.
         * \param[in] ip_address The new IP address.
         * \param[in] mask The new subnetwork mask.
         * \param[in] gateway The new gateway.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given mac address exists.
         */
        inline bool forceIp( const std::string& mac_address, const std::string& ip_address, const std::string& mask, const std::string& gateway )
                {
                    return NITManager::ForceIp( mac_address.c_str(), ip_address.c_str(), mask.c_str(), gateway.c_str() );
                }
    }

    namespace ClControl {
        //typedef void (*CL_CBACK)(const char*, uint32_t);
        /** \brief Open a Camera Link device by serial port.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         * Mac address of the camera can be foud on the rear of the camera.
         * Mac address string must be in the form 70:b3:d5:2a:c0:00 (columns are mandatory).
         *
         * \param[in] name of the serial port.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given serial port exists.
         */
        inline NITDevice* openBySerialPort( const std::string& port_name )    { return NITManager::getInstance().OpenBySerialPort( port_name.c_str() ); }
        /** \brief Open a discovered Gige device by ip address.
         *
         * When the maintained list is empty, calling this function, will try to discover the connected cameras.
         *
         * \param[in] ip_address The ip address of the queried device.
         * \return A pointer to the open device.
         * \throw NITException if the maintained list is empty.
         * \throw NITException if the model of the camera cannot be detected.
         * \throw NITException if no camera with the given ip address exists.
         */
        inline NITDevice* openWithCallback( const ClControl::ClConfig& config )
        {
            return NITManager::getInstance().OpenWithCallback( config );
        }
    }
}

extern "C" NITDLL_API NITLibrary::NITManager& CreateNITManager();

#endif // NITMANAGER_H
