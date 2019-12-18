#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_27__ {scalar_t__ i_planes; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_28__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_29__ {scalar_t__ i_wrapper_output; scalar_t__ i_internal_chroma; TYPE_1__* p_proc_image; int /*<<< orphan*/  p_image; int /*<<< orphan*/ * p_cv_image; TYPE_4__* p_opencv; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_30__ {int /*<<< orphan*/  (* pf_video_filter ) (TYPE_4__*,TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ CINPUT ; 
 int /*<<< orphan*/  CopyInfoAndRelease (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ NONE ; 
 scalar_t__ PROCESSED ; 
 int /*<<< orphan*/  ReleaseImages (TYPE_2__*) ; 
 scalar_t__ VINPUT ; 
 int /*<<< orphan*/  VlcPictureToIplImage (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* filter_NewPicture (TYPE_2__*) ; 
 TYPE_1__* image_Convert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  picture_CopyPixels (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_1__*) ; 

__attribute__((used)) static picture_t* Filter( filter_t* p_filter, picture_t* p_pic )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    picture_t* p_outpic = filter_NewPicture( p_filter );
    if( p_outpic == NULL ) {
        msg_Err( p_filter, "couldn't get a p_outpic!" );
        picture_Release( p_pic );
        return NULL;
    }

    // Make a copy if we want to show the original input
    if (p_sys->i_wrapper_output == VINPUT)
        picture_Copy( p_outpic, p_pic );

    VlcPictureToIplImage( p_filter, p_pic );
    // Pass the image (as a pointer to the first IplImage*) to the
    // internal OpenCV filter for processing.
    p_sys->p_opencv->pf_video_filter( p_sys->p_opencv, (picture_t*)&(p_sys->p_cv_image[0]) );

    if(p_sys->i_wrapper_output == PROCESSED) {
        // Processed video
        if( (p_sys->p_proc_image) &&
            (p_sys->p_proc_image->i_planes > 0) &&
            (p_sys->i_internal_chroma != CINPUT) ) {
            //p_sys->p_proc_image->format.i_chroma = VLC_CODEC_RGB24;

            video_format_t fmt_out = p_pic->format;
            //picture_Release( p_outpic );

            /*
             * We have to copy out the image from image_Convert(), otherwise
             * you leak pictures for some reason:
             * main video output error: pictures leaked, trying to workaround
             */
            picture_t* p_outpic_tmp = image_Convert(
                        p_sys->p_image,
                        p_sys->p_proc_image,
                        &(p_sys->p_proc_image->format),
                        &fmt_out );

            picture_CopyPixels( p_outpic, p_outpic_tmp );
            CopyInfoAndRelease( p_outpic, p_outpic_tmp );
        } else if( p_sys->i_internal_chroma == CINPUT ) {
            picture_CopyPixels( p_outpic, p_sys->p_proc_image );
            picture_CopyProperties( p_outpic, p_sys->p_proc_image );
        }
    }

    ReleaseImages( p_filter );
    picture_Release( p_pic );

#ifndef NDEBUG
    msg_Dbg( p_filter, "Filter() done" );
#endif

    if( p_sys->i_wrapper_output != NONE ) {
        return p_outpic;
    } else { // NONE
        picture_Release( p_outpic );
        return NULL;
    }
}