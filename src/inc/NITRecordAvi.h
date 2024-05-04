#ifndef NITRECORDAVI_H
#define NITRECORDAVI_H

#include "NITObserver.h"
#include <string>
#include <vector>

namespace NITLibrary {
    namespace NITToolBox {
/** \brief This class record the frame data in an AVI file.
 *
 * The data is recorded in MP4 format.
 *
 * The frames are recorded when startRecording() is called.
 * The recording continue until stopRecording(), reset() or close() is called or the object is destructed.
 *
 */
class NITRecordAvi : public NITObserver
{
    public:
        /** \brief Construct an uninitialized NITRecordAvi object.
         *
         * If this constructor is called, you must call reset.\n
         * If not, the calls to the object functions will be no-ops.\n
         */
        NITRecordAvi() : impl(NULL) {}

        /** \brief Construct a NITRecordAvi object.
         *
         * \param output_filename The full path to the avi file to create
         * \param avi_frame_width, avi_frame_height Resolution of the recorded frame.\n
         *          If the resolution is lower than the frame resolution, the frame is cropped.\n
         *          If the resolution his higher than the frame resolution, the frame is displayed in top-left side of the avi image.
         * \param fps frame rate at which the recording is done.
         *
         * \throw NITException if the file cannot be open. or the extension is not avi.
         */
        NITRecordAvi( const std::string& output_filename, unsigned int avi_frame_width, unsigned int avi_frame_height, unsigned int fps )
        {
            Init( output_filename.c_str(), avi_frame_width, avi_frame_height, fps );
        }
        /** \brief Destructor
         *
         * Call close(false).
         */
        NITDLL_API ~NITRecordAvi();


        /** \brief Reset the current recording.
         *
         * If this function is called while a recording is started; the recording is stopped immediatly, remaining frames to record are dropped\n
         * and the file is closed.
         * If output_filename is the same name as the current file name, the file is rewritten. That is the old data is lost.
         *
         * \param output_filename The full path to the avi file to create
         * \param avi_frame_width, avi_frame_height Resolution of the recorded frame.\n
         *          If the resolution is lower than the frame resolution, the frame is cropped.\n
         *          If the resolution his higher than the frame resolution, the frame is displayed in top-left side of the avi image.
         * \param fps frame rate at which the recording is done.
         *
         * \throw NITException if the file cannot be open. or the extension is not avi.
         */
        void reset( const std::string& output_filename, unsigned int avi_frame_width, unsigned int avi_frame_height, unsigned int fps )
        {
            Reset( output_filename.c_str(), avi_frame_width, avi_frame_height, fps );
        }

        /** \brief Start recording in the current file. */
        NITDLL_API void startRecording();

        /** \brief Stop recording in the current file.
         *
         * The file is not closed. A new call to startRecording() will continue the recording on the current file.
         *
         * \param record_last_frames if set to true no new frames are taken into account, but frames already enqueued are honored\n
         *                           if set to false enqueued frames are dropped
         *
         * \throw NITException if the file is currently closed.
         */
        NITDLL_API void stopRecording(bool record_last_frames = true );

        /** \brief Close the current file.
         *
         * If recording is in progress, recording is first stopped.
         *
         * \param record_last_frames if set to true no new frames are taken into account, but frames already enqueued are honored\n
         *                           if set to false enqueued frames are dropped
         *
         * To restart a new recording session you must call reset().
         */
        NITDLL_API void close( bool record_last_frames = true );

        /** \brief Return the current full file path.
         *
         * \return the current full file path.
         */
        std::string getFileName() const
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

        /** \brief Return the current recorded frame width.
         *
         * This parameter is the width of the recorded image, not the width of the NITFrames who can vary
         *
         * \return the current recorded frame width.
         */
        NITDLL_API int aviFrameWidth() const;

        /** \brief Return the current recorded frame height.
         *
         * This parameter is the height of the recorded image, not the height of the NITFrames who can vary
         *
         * \return the current recorded frame height.
         */
        NITDLL_API int aviFrameHeight() const;

        /** \brief Return the current recording state.
         *
         * \return true if recording is in progress or false otherwise.
         */
        NITDLL_API bool isRecording() const;

        /** \brief Return the current file state.
         *
         * \return true if the file is open or false otherwise.
         */
        NITDLL_API bool isOpen() const;

    private:
        class Impl;
        Impl* impl;

        NITDLL_API void Init( const char* output_filename, unsigned int avi_frame_width, unsigned int avi_frame_height, unsigned int fps );
        NITDLL_API void Reset( const char* output_filename, unsigned int avi_frame_width, unsigned int avi_frame_height, unsigned int fps );
        NITDLL_API bool GetFileName( char*, unsigned int& ) const;

        NITDLL_API void onNewFrame( const NITFrame& frame );
};
    }
}
#endif // NITRECORDAVI_H
