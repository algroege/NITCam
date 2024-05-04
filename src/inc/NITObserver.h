#ifndef NITOBSERVER_H
#define NITOBSERVER_H

#include <NITConnectable.h>

namespace NITLibrary {

/** \brief Base class of all the observers.
 *
 * An observer receive a const frame through the function NITFilter::onNewFrame().
 *
 * This instances of this class are used at the end of a pipeline branch.\n
 * The frame data must be copied for further use. The copied data is not managed by the SDK.
 *
 * Observers can be connected to NITFilter objects or directly to a NITDevice.\n
 *
 * All the observers of the NITToolBox derives from NITFilter.
 *
 * You have to derive a class from NITObserver and overload the onNewFrame() function to apply your own processing.
 */
class NITObserver : public Connectable
{
    public:
        /** \brief disconnect this observer from the pipeline */
        NITDLL_API void disconnect();

    protected:
        NITDLL_API NITObserver();
        NITDLL_API ~NITObserver();

    private:
        void Disconnect( Connectable* ) {}
        NITDLL_API void onNewImage( NITFrame& );
        /** \brief Called each time a new frame is captured
         *
         * \param frame: frame to copy or to collect information from
         *
         * \threading This function can be called from different threads.
         */
        virtual void onNewFrame( const NITFrame& frame ) = 0;
};
}

#endif // NITOBSERVER_H
