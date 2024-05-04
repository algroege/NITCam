#ifndef NITSNAPSHOT_H_INCLUDED
#define NITSNAPSHOT_H_INCLUDED

#include "NITObserver.h"
#include <string>
#include <vector>

namespace NITLibrary
{
	namespace NITToolBox
	{
        /** \brief This class record frames in image files.
         *
         * The supported formats are bmp, jpg, png, tif, with pixel type rgb
         *
         * The file names have the following form: \<directory\>/\<prefix\>_\<counter\>.\<extension\>\n
         * With \<directory\>,\<prefix\>,\<counter\>,\<extension\> parameters who can be set.\n
         * The function setCounter() permits to set the number of digits of the counter. The default value is 0; in this case counter is written without trailing 0.\n
         * Example: if counter == 10 and number of digits is 0: The file name look like this: \<directory\>/\<prefix\>_10.\<extension\>\n
         * Example: if counter == 10 and number of digits is 4: The file name look like this: \<directory\>/\<prefix\>_0010.\<extension\>
         *
         * The number of frames recorded are set with the function snap().
         */
		class NITSnapshot : public NITObserver
		{
		public:
            /** \brief Construct an uninitialized NITSnapshot object.
             *
             * If this constructor is called, you must call reset and, if needed, setJpegQuality.\n
             * If not, the calls to the object functions will be no-ops.\n
             */
		    NITSnapshot() : impl(NULL) {}
            /** \brief Construct a NITSnapshot object.
             *
             * \param file_directory The existing writable directory where the files must be created.
             * \param prefix  Prefix of the file.\n
             * \param extension Extension of the file. The extension define the image format.\n
             * extension can be "bmp", "jpg", "jpeg", "png", "tif", "tiff". A dot can precede the name.
             * \param jpeg_quality quality of the jpeg file( uniquely used for jpeg ).
             *
             * \throw NITException if the directory don't exists.
             * \throw NITException if the extension is not supported.
             * \throw NITException if the jpeg_quality is above 100.
             */
			NITSnapshot(const std::string& file_directory, const std::string& prefix, const std::string& extension, unsigned int jpeg_quality = 95 ) : impl(NULL)
			{
			    reset( file_directory, prefix, extension );
			    setJpegQuality( jpeg_quality );
			}

			/** \brief Destructor. */
			NITDLL_API ~NITSnapshot();

            /** \brief Set new file components.
             *
             * \param file_directory The existing writable directory where the files must be created.
             * \param prefix  Prefix of the file.\n
             * \param extension Extension of the file. The extension define the image format.\n
             * extension can be "bmp", "jpg", "jpeg", "png", "tif", "tiff". A dot can precede the name.
             *
             * \throw NITException if the directory don't exists.
             * \throw NITException if the extension is not supported.
             */
			void reset( const std::string& file_directory, const std::string& prefix, const std::string& extension )
			{
			    SetFileName( file_directory.c_str(), prefix.c_str(), extension.c_str() );
			}
            /** \brief Set new jpeg quality.
             *
             * If the image to record is not jpeg, the parameter is ignored.
             *
             * \param jpeg_quality quality of the jpeg file( uniquely used for jpeg ).
             *
             * \throw NITException if the jpeg_quality is above 100.
             */
            NITDLL_API void setJpegQuality( unsigned int jpeg_quality );

            /** \brief Set new counter start value.
             *
             * The counter is the value used to construct the name of the file.\n
             * Each time a new file is created this value is incremented by one.\n
             * The default value at object creation is 1.
             *
             * \param new_counter The new value of the counter.
             * \param digits number of digits used to convert the counter to string in the file name creation process.
             */
            NITDLL_API void setCounter( unsigned int new_counter, unsigned int digits );

            /** \brief Return the full file name of the last recorded image.
             *
             * \return the full file name of the last recorded image
             */
            std::string getLastFileName() const
            {
                std::vector< char > tmp(512);
                unsigned int data_size( (unsigned int)tmp.size());
                if( !GetFileName( tmp.data(), data_size ) )
                {
                    tmp.resize(data_size);
                    GetFileName( tmp.data(), data_size );
                }
                return std::string( tmp.data() );
            }
            /** \brief Return the current counter value.
             *
             * \return the current counter value.
             */
            NITDLL_API unsigned int getCounterValue() const;

            /** \brief Set a number of images to record.
             *
             * At creation of the object the current snap count is 0, that is no frame is recorded.\n
             * Each time a frame is recorded the snap count is decremented. When the count reach 0, the recording is stopped.
             *
             * The parameter of this function is added to the current snap count.
             *
             * \param count Number of images to record.
             */
			NITDLL_API void snap( unsigned int count );

		protected:
			// Implementation
			NITDLL_API void	onNewFrame(const NITFrame& frame );

		private:
                NITDLL_API void SetFileName( const char* file_path, const char* prefix, const char* extension );
                NITDLL_API bool GetFileName( char*, unsigned int& ) const;

		    class Impl;
		    Impl* impl;
		};
	}
}

#endif // NITSNAPSHOT_H_INCLUDED
