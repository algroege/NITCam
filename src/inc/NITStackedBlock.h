#ifndef NITSTACKEDBLOCK_H_INCLUDED
#define NITSTACKEDBLOCK_H_INCLUDED

#include <sstream>

#include "NITException.h"

namespace NITLibrary
{
/** \brief Helper class used to manage the 'Stacked Block_x' parameter available on some NIT cameras.
 *
 * This union permit to fill the offsetY and height parameter of a stacked block and to get an unsigned int or string formatted to pass
 * to NITLibrary::NItDevice::setParamValueOf().
 * The result of NITLibrary::NItDevice::paramValueOf() and NITLibrary::NItDevice::paramStrValueOf() can also be passed to this union to get the
 * encoded offsetY and height.
 * */
    union NITStackedBlock
    {
        private:
            unsigned int raw;
        public:
            struct
            {
                unsigned int offsetY : 16; /// High part of 'raw'
                unsigned int height  : 16; /// Low part of 'raw'
            };

            /** \brief Construct a NITStackedBlock object
             *
             * Use this constructor to get an unsigned int to pass to setParamValueOf
             *
             * \param offset_y offset of the stacked block relative to the preceding enabled stacked block( for the first enabled stacked block, the offset
             *           is relative to the first line of the sensor.
             * \param height height height of the block.
             */
            NITStackedBlock( unsigned int offset_y, unsigned int height ) : offsetY(offset_y), height(height) {}

            /** \brief Construct a NITStackedBlock object
             *
             * Use this constructor to get offset and height from the unsigned int returned by paramValueOf
             *
             * \param raw concatenated values of offsetY(high part) and height(low part)
             */
            NITStackedBlock( unsigned int raw ) : raw(raw) {}

            /** \brief cast operator
             *
             * \return raw
             */
            operator unsigned int() const { return raw; }


            /** \brief return a string representing this stacked block
             *
             * The format is <offsetY>;<height> eg: 120;344
             *
             * \return return a string representation of this stacked block
             */
            std::string to_string() const
            {
                std::stringstream ss;
                ss << offsetY << ';' << height;
                return ss.str();
            }
            /** \brief return a NITStackedBlock object inited from a well formed string
             *
             * The format of the string must be <offsetY>;<height> eg: 120;344
             *
             * \param The string representation of the stacked block.
             *
             * \throw NITException if the string contains something else than numbers and comma.
             * \return return a NITStackedBlock object
             */
            static NITStackedBlock from_string( const std::string& str )
            {
                if( str.find_first_not_of( "0123456789;") != str.npos )
                    NITException::throwException( "StackedBlock: bad string format" );

                unsigned int y,h;
                char dummy;
                std::stringstream ss(str);
                ss >> y >> dummy >> h;
                return NITStackedBlock(y,h);
            }
    };
} //namespace NITLibrary

#endif // NITSTACKEDBLOCK_H_INCLUDED
