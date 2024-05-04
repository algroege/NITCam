#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include "NITImpExp.h"

namespace NITLibrary {

class NITFrame;
}

    /** \brief Internal helper class used by the SDK only.     */
class Connectable
{
    public:
        virtual void onNewImage( NITLibrary::NITFrame& ) = 0;
        void SetPrevious( Connectable* );
        virtual void Disconnect( Connectable* ) = 0;

    protected:

        Connectable();
        virtual ~Connectable();

        Connectable* previous;

};

#endif // CONNECTABLE_H
