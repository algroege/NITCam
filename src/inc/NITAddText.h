#ifndef NITADDTEXT_H
#define NITADDTEXT_H

#include <NITFilter.h>
#include <vector>
#include <string>

/*! @brief main namespace of the library */
namespace NITLibrary {
    /*! @brief namespace of the library filters */
    namespace NITToolBox {

/** \brief Overlay a text on the current frame.
 *
 * The overlay is done at the position and with the font specified.
 * If due to the size and position of the overlay, the overlay is to big to be rendered in the current frame, the overlay is cropped.
 */
class NITAddText : public NITFilter
{
    public:
        /** \brief Construct a NITAddText object.
         *
         * \param text: string to be overlayed. If empty, no string is displayed.
         * \param x_pos: x position of the text.
         * \param y_pos: y position of the text.
         * \param font_name: name of the TrueType font to use( as displayed in any text editor).
         *        If the name is not recognized by the system or is not a TrueType font, the default system TrueType font is used.
         *        Default font is Arial on Windows.
         *        Default font is LiberationMono on Linux (if LiberationMono is missing the best fitting font is chosen)
         * \param font_size: size of the font in points.
         */
        NITAddText(const std::string& text, unsigned int x_pos, unsigned int  y_pos, const std::string& font_name, unsigned int font_size )
        {
            Init( text.c_str(), x_pos, y_pos, font_name.c_str(), font_size );
        }
        /** \brief Destructor
         */
        NITDLL_API ~NITAddText();

        /** \brief Change the current text.
         *
         * \param text: string to be overlayed. If text is empty, no text is overlay-ed.
         */
        void setText( const std::string& text )                          { SetText( text.c_str() ); }

        /** \brief Change the current font.
         *
         * \param font_name: name of the TrueType font to use( as displayed in any text editor).
         *        If the name is not recognized by the system or is not a TrueType font, the default system TrueType font is used(Arial on Windows).
         */
        void setFontName( const std::string& font_name )                  { SetFontName( font_name.c_str() ); }

        /** \brief Change the current font and size.
         *
         * \param font_name: name of the TrueType font to use( as displayed in any text editor).
         *        If the name is not recognized by the system or is not a TrueType font, the default system TrueType font is used(Arial on Windows).
         * \param font_size: size of the font in points.
         */
        void setFont( const std::string& font_name, unsigned int font_size )  { SetFont( font_name.c_str(), font_size ); }

        /** \brief Change the current font size.
         *
         * \param font_size: size of the font in points.
         */
        NITDLL_API void setFontSize( unsigned int font_size );

        /** \brief return the current overlay-ed text.
         *
         * \return return the current overlay-ed text.
         */
        std::string getText() const
        {
            std::vector< char > tmp(512);
            unsigned int data_size( (unsigned int)tmp.size());
            if( !GetText( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                GetText( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }

        /** \brief return the current font name.
         *
         * \return return the current font name.
         */
        std::string getFontName() const
        {
            std::vector< char > tmp(512);
            unsigned int data_size( (unsigned int)tmp.size());
            if( !GetFontName( tmp.data(), data_size ) )
            {
                tmp.resize(data_size);
                GetFontName( tmp.data(), data_size );
            }
            return std::string( tmp.data() );
        }

        /** \brief return the current font size.
         *
         * \return return the current font size.
         */
        NITDLL_API unsigned int getFontSize() const;

        /** \brief set the position of the text.
         *
         * \param x_pos, y_pos: x,y position of the upper left corner of the text
         */
        NITDLL_API void setPosition( unsigned int x_pos, unsigned int y_pos );
        /** \brief set the x position.
         *
         * \param x_pos: position of the left side of the text
         */
        NITDLL_API void setPosX( unsigned int x_pos );
        /** \brief set the y position.
         *
         * \param y_pos: position of the upper side of the text
         */
        NITDLL_API void setPosY( unsigned int y_pos );
        /** \brief activate/deactivate background transparency.
         *
         * \param b_set: if true only the text is displayed. If false the text is displayed on a white background (default true).
         *
         */
        NITDLL_API void setTransparentBackground( bool b_set = true );

        /** \brief return the position of the text.
         *
         * \return return the position of the text.
         */
        NITDLL_API void getPosition( unsigned int& x_pos, unsigned int& y_pos );
        /** \brief return the x position of the text.
         *
         * \return return the x position of the text.
         */
        NITDLL_API unsigned int getPosX() const;
        /** \brief return the y position of the text.
         *
         * \return return the y position of the text.
         */
        NITDLL_API unsigned int getPosY() const;

    private:
        NITDLL_API void Init(const char*, unsigned int, unsigned int, const char*, unsigned int );
        NITDLL_API void SetText( const char* ) const;
        NITDLL_API void SetFontName( const char* );
        NITDLL_API void SetFont( const char*, unsigned int );
        NITDLL_API bool GetText( char*, unsigned int& ) const;
        NITDLL_API bool GetFontName( char*, unsigned int& ) const;

        class Impl;
        Impl* impl;

    protected:
        NITDLL_API void onNewFrame( NITFrame& );
};

    }
}
#endif // NITADDTEXT_H
