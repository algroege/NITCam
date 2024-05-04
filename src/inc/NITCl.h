#ifndef NITCL_H_INCLUDED
#define NITCL_H_INCLUDED

#include "NITImpExp.h"
#include <string>
#include <cstring>

namespace NITLibrary {

    class NITDevice;

    namespace ClControl {
        typedef bool (*CL_WCBACK)(const char* buffer, unsigned int buffer_size, void* user_param );
        typedef bool (*CL_RCBACK)(char* buffer, unsigned int buffer_size, unsigned int timeout, void* user_param );

        struct ClConfig
        {
            enum { USE_SERIAL_PORT, USE_CALLBACK } type;
            union
            {
                struct //Callback
                {
                    CL_WCBACK write;
                    CL_RCBACK read;
                    void* writeUserParam;
                    void* readUserParam;
                } cb;
                char serialPortName[64];
            };

            unsigned int modelId;
            unsigned int sensorWidth;
            unsigned int sensorHeight;
            char serialNumber[7];
            char firmwareVersion[6];
            char capacities[17];

            ClConfig() { std::memset( capacities, 0, 17 ); }
            ClConfig( const std::string& serial_port, const std::string& config_file = std::string() ) : type( USE_SERIAL_PORT )
            {
                strncpy_s( serialPortName, serial_port.c_str(), 64 );
                if( !config_file.empty() )
                    InitFromFile( config_file.c_str() );
            }
            ClConfig( CL_WCBACK wcb, CL_RCBACK rcb, void* write_user_param, void* read_user_param, const std::string& config_file = std::string() ) : type( USE_CALLBACK )
            {
                cb.write = wcb;
                cb.read = rcb;
                cb.writeUserParam = write_user_param;
                cb.readUserParam = read_user_param;
                if( !config_file.empty() )
                    InitFromFile( config_file.c_str() );
            }

            private:
                NITDLL_API void InitFromFile( const char* config_file );
        };
        static int Error;
        static std::string ErrorString;
        NITDLL_API void newFrame( NITDevice* dev, unsigned char* buffer, unsigned int bytes );
        NITDLL_API bool hasPluginDalsa();
        NITDLL_API int getLastError();
        NITDLL_API const char* getLastErrorString();

    }
}

#endif // NITCL_H_INCLUDED
