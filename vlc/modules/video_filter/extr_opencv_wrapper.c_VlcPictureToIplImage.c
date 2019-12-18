#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int i_width; int i_height; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_25__ {int i_planes; TYPE_4__ format; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_26__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ filter_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_23__ {int i_planes; TYPE_2__ format; } ;
struct TYPE_27__ {int f_scale; scalar_t__ i_internal_chroma; int i_cv_image_size; TYPE_3__ hacked_pic; TYPE_8__* p_proc_image; int /*<<< orphan*/ * p_cv_image; TYPE_8__* p_to_be_freed; int /*<<< orphan*/  p_image; } ;
typedef  TYPE_7__ filter_sys_t ;
struct TYPE_28__ {int i_planes; TYPE_1__* p; } ;
struct TYPE_21__ {int i_visible_pitch; int i_pixel_pitch; int i_visible_lines; int /*<<< orphan*/  i_pitch; scalar_t__ p_pixels; } ;
typedef  int /*<<< orphan*/  CvSize ;

/* Variables and functions */
 scalar_t__ CINPUT ; 
 scalar_t__ GREY ; 
 int /*<<< orphan*/  IPL_DEPTH_8U ; 
 scalar_t__ RGB ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int /*<<< orphan*/  VLC_CODEC_RGB24 ; 
 int abs (int) ; 
 int /*<<< orphan*/  cvCreateImageHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvSetData (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvSize (int,int) ; 
 TYPE_8__* filter_NewPicture (TYPE_6__*) ; 
 TYPE_8__* image_Convert (int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_8__*,TYPE_5__*) ; 

__attribute__((used)) static void VlcPictureToIplImage( filter_t* p_filter, picture_t* p_in )
{
    int planes = p_in->i_planes;    //num input video planes
    // input video size
    CvSize sz = cvSize(p_in->format.i_width, p_in->format.i_height);
    video_format_t fmt_out;
    filter_sys_t* p_sys = p_filter->p_sys;

    memset( &fmt_out, 0, sizeof(video_format_t) );

    //do scale / color conversion according to p_sys config
    if ((p_sys->f_scale != 1) || (p_sys->i_internal_chroma != CINPUT))
    {
        fmt_out = p_in->format;

        //calc the scaled video size
        fmt_out.i_width = p_in->format.i_width * p_sys->f_scale;
        fmt_out.i_height = p_in->format.i_height * p_sys->f_scale;

        if (p_sys->i_internal_chroma == RGB)
        {
            //rgb2 gives 3 separate planes, this gives 1 interleaved plane
            //rv24 gives is about 20% faster but gives r&b the wrong way round
            //and I can't think of an easy way to fix this
            fmt_out.i_chroma = VLC_CODEC_RGB24;
        }
        else if (p_sys->i_internal_chroma == GREY)
        {
            //take the I (gray) plane (video seems to commonly be in this fmt so usually the
            //conversion does nothing)
            fmt_out.i_chroma = VLC_CODEC_I420;
        }

        //convert from the input image
        p_sys->p_proc_image = image_Convert( p_sys->p_image, p_in,
                                     &(p_in->format), &fmt_out );

        if (!p_sys->p_proc_image)
        {
            msg_Err(p_filter, "can't convert (unsupported formats?), aborting...");
            return;
        }


    }
    else    //((p_sys->f_scale != 1) || (p_sys->i_internal_chroma != CINPUT))
    {
        // In theory, you could use the input image without conversion,
        // but it seems to cause weird picture effects (like repeated
        // image filtering) and picture leaking.
        p_sys->p_proc_image = filter_NewPicture( p_filter ); //p_in
        picture_Copy( p_sys->p_proc_image, p_in );
    }
    p_sys->p_to_be_freed = p_sys->p_proc_image;    //remember this so we can free it later

    //Convert to the IplImage array that is to be processed.
    //If there are multiple planes in p_sys->p_proc_image, then 1 IplImage
    //is created for each plane.
    planes = p_sys->p_proc_image->i_planes;
    p_sys->i_cv_image_size = planes;
    for( int i = 0; i < planes; i++ )
    {
        sz = cvSize(abs(p_sys->p_proc_image->p[i].i_visible_pitch /
            p_sys->p_proc_image->p[i].i_pixel_pitch),
            abs(p_sys->p_proc_image->p[i].i_visible_lines));

        p_sys->p_cv_image[i] = cvCreateImageHeader(sz, IPL_DEPTH_8U,
            p_sys->p_proc_image->p[i].i_pixel_pitch);

        cvSetData( p_sys->p_cv_image[i],
            (char*)(p_sys->p_proc_image->p[i].p_pixels), p_sys->p_proc_image->p[i].i_pitch );
    }

    //Hack the above opencv image array into a picture_t so that it can be sent to
    //another video filter
    p_sys->hacked_pic.i_planes = planes;
    p_sys->hacked_pic.format.i_chroma = fmt_out.i_chroma;

#ifndef NDEBUG
    msg_Dbg( p_filter, "VlcPictureToIplImageRgb() completed" );
#endif
}