#ifndef NITGIGE_H_INCLUDED
#define NITGIGE_H_INCLUDED

#include "NITImpExp.h"
#include <string>
#include <vector>

#include <iostream>

namespace NITLibrary {

    class NITDevice;

    /** \brief namespace of helpers for Gige cameras. */
  namespace Gige {

    /** \brief base class for Gige cameras parameter definition.
     *
     * Derived classes are used by NITConfigObserverGige to inform for the parameters of a device.
     */
    class Param
    {
        protected:
            void* node;

            Param( void* node );
            NITDLL_API bool GetName( char*, size_t&) const;
        public:
            /** \brief Visibility of the parameters */
            enum eVisibility {  Beginner,                    /**< Visible by all users */
                                Expert,                      /**< Visible by experts and Gurus */
                                Guru                         /**< Visible by Gurus only */
                             };

            /** \brief return the name of the parameter
             *
             * \return return the name of the parameter
             */
            std::string name() const
            {
                std::vector< char > tmp(512);
                size_t data_size( tmp.size());
                if( !GetName( tmp.data(), data_size ) )
                {
                    tmp.resize(data_size);
                    GetName( tmp.data(), data_size );
                }
                return std::string( tmp.data() );
            }

            /** \brief return if the parameter can be modified
             *
             * A parameter is not mutable if it is not writeable or if it can have only one possible value.
             *
             * \return true if parameter is writable, false otherwise
             */
            NITDLL_API bool isMutable() const;
            /** \brief return if the parameter can be read
             *
             * \return true if parameter is readable, false otherwise
             */
            NITDLL_API bool isReadable() const;
            /** \brief return by which kind of user the parameter can be visible
             *
             * \return one of the eVisibility entries
             */
            NITDLL_API eVisibility Visibility() const;
    };

    /** \brief class who define integer parameters for Gige cameras.     */
    class IntParam : public Param
    {
        public:
            enum eRepresentation
                {   Linear,                         //!< Slider with linear behavior
                    Logarithmic,                    //!< Slider with logarithmic behaviour
                    Boolean,                        //!< Check box
                    PureNumber,                     //!< Decimal number in an edit control
                    HexNumber,                      //!< Hex number in an edit control
                    IPV4Address,                    //!< IP-Address
                    MACAddress,                     //!< MAC-Address
                } ;
            IntParam( void* node );

            NITDLL_API int minValue() const;        //!< Minimum possible value of the parameter
            NITDLL_API int maxValue() const;        //!< Maximum possible value of the parameter
            NITDLL_API int step() const;            //!< Increment step of the parameter
            NITDLL_API bool isContinuous() const;   //!< true if the parameter can take any integer value between minValue and maxValue
            NITDLL_API int Representation() const;  //!< Representation of the parameter
    };
    /** \brief class who define floating point parameters for Gige cameras.     */
    class FloatParam : public Param
    {
        public:
            FloatParam( void* node );

            NITDLL_API float minValue() const;      //!< Minimum possible value of the parameter
            NITDLL_API float maxValue() const;      //!< Maximum possible value of the parameter
            NITDLL_API float step() const;          //!< Increment step of the parameter
            NITDLL_API bool isContinuous() const;   //!< true if the parameter can take any floating point value between minValue and maxValue
    };
    /** \brief class who define boolean parameters for Gige cameras.     */
    class BoolParam : public Param
    {
        public:
            BoolParam( void* node );
    };
    /** \brief class who define enum parameters for Gige cameras.     */
    class EnumParam : public Param
    {
            NITDLL_API unsigned int GetNumberEntries() const;
            NITDLL_API bool GetEntry( unsigned int , char*, size_t& ) const;
        public:
            EnumParam( void* node );

            std::vector< std::string > GetEntries() //!< Return a string representation of each entry in the enumeration
            {
                std::vector< std::string > entries;
                unsigned int nbre = GetNumberEntries();
                std::vector< char > tmp(512);
                for( int i = 0; i!= nbre; ++i )
                {
                    size_t data_size( tmp.size());
                    if( !GetEntry( i,  tmp.data(), data_size ) )
                    {
                        tmp.resize(data_size);
                        GetEntry( i, tmp.data(), data_size );
                    }
                    entries.push_back( &tmp[0] );
                }
                return entries;
            }
    };

    /** \brief class who define string parameters for Gige cameras.     */
    class StringParam : public Param
    {
        public:
            StringParam( void* node );
    };
    /** \brief class who define command parameters for Gige cameras.
     *
     * Command parameters can only have the value 1.
     */
    class CommandParam : public Param
    {
        public:
            CommandParam( void* node );
    };

    /** \brief Function who permit to be informed of the reception of the first packet of a frame.
     *
     * This is the shortest event we can receive after exposure time.\n
     * This function is coupled with NITDevice::captureNFrames() and have only a meaning when the number of frames to capture is one.\n
     * The timer starts when NITDevice::captureNFrames() is called.
     *
     * \code dev->captureNFrame( 1 ); //Capture 1 frame
     *  dev->waitBeginOfFrame(20); \endcode
     *
     * \param dev The gige device on which function will be applied.
     * \param timeout The maximum number of milliseconds to wait for the reception of the first packet.\n
     * \return false if the function timed out, else true if the first packet was received.
     * \throw NITException if the device is not Gige
     */
    NITDLL_API bool waitBeginOfFrame(NITDevice& dev, int timemout );
    NITDLL_API bool GetXml( NITDevice&, char*, size_t );

    /** \brief Return a string containing the xml of the Gige camera.
     * \param dev The gige device on which function will be applied.
     * \return the xml content.
     * \throw NITException if the device is not Gige
     */
    inline std::string getXml( NITDevice& dev )
    {
        std::vector< char > tmp(100*1024);
        size_t data_size( tmp.size());
        if( !GetXml( dev, tmp.data(), data_size ) )
        {
            tmp.resize(data_size);
            GetXml( dev, tmp.data(), data_size );
        }
        return std::string( tmp.data() );
    }
} }

#endif // NITGIGE_H_INCLUDED
