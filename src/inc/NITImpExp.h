#ifndef IMP_EXP_H_INCLUDED
#define IMP_EXP_H_INCLUDED

#ifndef STATIC_LIB
    #if defined(_MSC_VER)
    	#ifdef BUILD_DLL
        	#define NITDLL_API __declspec(dllexport)
    	#else
        	#define NITDLL_API __declspec(dllimport)
    	#endif
    #elif defined(__GNUC__)
        #ifdef BUILD_DLL
            #define NITDLL_API __attribute__((visibility("default")))
        #else
            #define NITDLL_API
        #endif
    #else
    	#define NITDLL_API
    #endif // defined
#endif

namespace NITLibrary {
enum ConnectorType
{
    NO_CONNECTOR,
    USB_2,								/*!< USB 2.0 connector. */
    USB_3,                               /*!< USB 3.0 connector. */
    GIGE = 4,
    #ifdef _WIN32
    CL_DALSA = 8,
    CL_IMPERX = 16
    #endif
};

}

#endif // IMP_EXP_H_INCLUDED
