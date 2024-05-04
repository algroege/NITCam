#ifndef NITFILTER_H
#define NITFILTER_H

#include "NITConnectable.h"
#include <list>


class ThreadedConnectable;

namespace NITLibrary {

class NITObserver;

/** \brief Base class of all the filters.
 *
 * A filter receive a frame through the function NITFilter::onNewFrame() and modify it in-place.
 *
 * Filters can be chained together and to NITObserver objects.\n
 * If more than one processing object is connected to a NITFilter, each added processing object imply the creation of a new branch of the pipeline running in his own thread.
 *
 * Finally a NITFilter can be active(default at construction), in this case the transformation of the frame is done\n
 * or it can be inactive in which case the frame is simply passed to the next stage.
 *
 * All the filters of the NITToolBox derives from NITFilter.
 *
 * To apply your own processing to the frames; you have to derive a class from NITFilter and overload the onNewFrame() function.
 */
class NITFilter : public Connectable
{
    public:
        /** \brief operator to connect a NITFilter to this NITFilter
         *
         * \param next_filter: NITFilter to connect just after this NITFilter
         *
         * \return next_filter to permit chaining
         *
         */
        NITDLL_API NITFilter&      operator<<( NITFilter& next_filter );

        /** \brief operator to connect a NITObserver to this NITFilter
         *
         * \param next_observer: NITObserver to connect just after this NITFilter
         *
         */
		NITDLL_API void            operator<<( NITObserver& next_observer );

        /** \brief disconnect this NITFilter from the pipeline */
        NITDLL_API void            disconnect();

        /** \brief change the state of the NITFilter
         *
         * \param state: if true the NITFilter is active, else the frames are directly passed to the next layer without processing.
         *
         */
		NITDLL_API void            activate( bool state );

        /** \brief return the current state of the NITFilter
         *
         * \return return the current state of the NITFilter
         *
         */
		NITDLL_API bool            active() const;

	protected:
        NITDLL_API NITFilter();
        NITDLL_API ~NITFilter();

    private:
        /** \brief Called each time a new frame is captured
         *
         * \param frame: frame to process
         *
         * \threading This function can be called from different threads.
         *
         */
        virtual void onNewFrame( NITFrame& frame ) = 0;
        typedef void (NITFilter::*NewFramePtr)( NITFrame& );
        NewFramePtr curOnNewFrame;
        NITDLL_API void onNewImage( NITFrame& );
        void noNewFrame( NITFrame& );

        void Connect( Connectable& );
        NITDLL_API void Disconnect( Connectable* );

        Connectable* connectedObject;
        std::list< ThreadedConnectable* > threadedConnectedObjects;
};

}
#endif // NITFILTER_H
