#ifndef NITFLIP_H
#define NITFLIP_H

#include <NITFilter.h>

namespace NITLibrary {
    namespace NITToolBox {

/** \brief Class to change the orientation of a frame. */
class NITFlip : public NITFilter
{
    public:
        enum eFlip {    NONE,
                        HORZ, /**< Flip the frame horizontally */
                        VERT, /**< Flip the frame vertically */
                        BOTH  /**< Flip the frame in both directions */
                   };
        /** \brief  Contruct a NITFlip object
         *
         * \param direction direction of the flip
         */
        NITDLL_API NITFlip( eFlip direction );
        /** \brief  Destructor */
        NITDLL_API ~NITFlip();

        /** \brief  Change the flip direction
         *
         * \param direction new direction of the flip
         */
        NITDLL_API void setFlip( eFlip direction );

        /** \brief  Return the flip direction
         *
         * \return the current flip direction
         */
        NITDLL_API eFlip getFlip() const;

    private:
        eFlip curFlip;

        class Impl;
        Impl* impl;

        void onNewFrame( NITFrame& );
};
    }
}
#endif // NITFLIP_H
