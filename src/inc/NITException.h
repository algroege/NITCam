#ifndef NITEXCEPTION_H_INCLUDED
#define NITEXCEPTION_H_INCLUDED

#include "NITImpExp.h"
#include <stdexcept>

namespace NITLibrary {

/** \brief Used to transmit exceptions to the calling process.
 *
 * As this class derives from std::runtime_error, the only usable function is what() who return a string describing the error.\n
 * This exception is intended to only be thrown by NITLibrary.\n
 *
 * This mecanism permit to pass exceptions from NITLibrary dll to the executable.\n
 * When an exception happen, the SDK call throwException, who internally call a callback function defined at the process side.\n
 * If you don't set a callback function by calling setThrowFunction, the default function DefaultThrowFunc is called.\n
 * This function throw a NITException on the process side, passing the message(msg) thrwon.
 */
class NITException : public std::runtime_error
{
    public:
        typedef void (*THROWFUNC)(const char*);

        /** \brief The throw function used if known as been set. **/
        static void DefaultThrowFunc( const char* msg ) { throw NITException( msg ); }
        /** \brief The function to call to set a callback function. **/
        static void setThrowFunction( THROWFUNC func ){ throwFunc = func; }
        /** \brief The function called when the SDK must throw an exception. **/
        #ifdef _WIN32
        static  __declspec(noreturn) void throwException(const char* msg){ throwFunc(msg); }
        #else
        static  __attribute__((noreturn)) void throwException(const char* msg){ throwFunc(msg); }
        #endif // _WIN32
//        static THROWFUNC throwFunc;

    private:
        static THROWFUNC throwFunc;
        NITException( const char* msg ) : std::runtime_error( msg ) {}
};
}

extern "C" { NITDLL_API void setThrowFunction(NITLibrary::NITException::THROWFUNC); }

#endif // NITEXCEPTION_H_INCLUDED
