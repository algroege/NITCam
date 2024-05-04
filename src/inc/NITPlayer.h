#ifndef NITPLAYER_H
#define NITPLAYER_H

#include <NITObserver.h>
#include <string>

namespace NITLibrary {
    namespace NITToolBox {
        /** \brief Class to display frames
         *
         * This observer display the frames in a window.
         */
        class NITPlayer : public NITObserver
        {
            public:
                /** \brief Construct a NITPlayer object
                 *
                 * \param title Title of the window
                 */
                NITPlayer( const std::string& title ) { Init( title.c_str() ); }

                /** \brief Destructor */
                NITDLL_API ~NITPlayer();

                NITDLL_API void* nativeHandle();

            private:
                class Impl;
                Impl* impl;

                NITDLL_API void Init( const char* );
                NITDLL_API void onNewFrame( const NITFrame& frame );
        };
    }
}
#endif // NITPLAYER_H
