#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int i_visible_width; unsigned int i_width; int i_visible_height; unsigned int i_height; double i_sar_den; scalar_t__ i_sar_num; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 unsigned int __MAX (int,unsigned int) ; 
 unsigned int lroundf (float) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,unsigned int,...) ; 

__attribute__((used)) static void transcode_video_scale_apply( vlc_object_t *p_obj,
                                        const video_format_t *p_src,
                                        float f_scale,
                                        unsigned i_maxwidth,
                                        unsigned i_maxheight,
                                        video_format_t *p_dst )
{
    /* Calculate scaling
     * width/height of source */
    unsigned i_src_width = p_src->i_visible_width ? p_src->i_visible_width : p_src->i_width;
    unsigned i_src_height = p_src->i_visible_height ? p_src->i_visible_height : p_src->i_height;

    /* with/height scaling */
    float f_scale_width = 1;
    float f_scale_height = 1;

    /* aspect ratio */
    float f_aspect = (double)p_src->i_sar_num * p_src->i_width /
                             p_src->i_sar_den / p_src->i_height;

    msg_Dbg( p_obj, "decoder aspect is %f:1", f_aspect );

    /* Change f_aspect from source frame to source pixel */
    f_aspect = f_aspect * i_src_height / i_src_width;
    msg_Dbg( p_obj, "source pixel aspect is %f:1", f_aspect );

    /* Calculate scaling factor for specified parameters */
    if( p_dst->i_visible_width == 0 && p_dst->i_visible_height == 0 && f_scale )
    {
        /* Global scaling. Make sure width will remain a factor of 16 */
        float f_real_scale;
        unsigned i_new_height;
        unsigned i_new_width = i_src_width * f_scale;

        if( i_new_width % 16 <= 7 && i_new_width >= 16 )
            i_new_width -= i_new_width % 16;
        else
            i_new_width += 16 - i_new_width % 16;

        f_real_scale = (float)( i_new_width ) / (float) i_src_width;

        i_new_height = __MAX( 16, i_src_height * (float)f_real_scale );

        f_scale_width = f_real_scale;
        f_scale_height = (float) i_new_height / (float) i_src_height;
    }
    else if( p_dst->i_visible_width && p_dst->i_visible_height == 0 )
    {
        /* Only width specified */
        f_scale_width = (float)p_dst->i_visible_width / i_src_width;
        f_scale_height = f_scale_width;
    }
    else if( p_dst->i_visible_width == 0 && p_dst->i_visible_height )
    {
         /* Only height specified */
         f_scale_height = (float)p_dst->i_visible_height / i_src_height;
         f_scale_width = f_scale_height;
     }
     else if( p_dst->i_visible_width && p_dst->i_visible_height )
     {
         /* Width and height specified */
         f_scale_width = (float)p_dst->i_visible_width / i_src_width;
         f_scale_height = (float)p_dst->i_visible_height / i_src_height;
     }

     /* check maxwidth and maxheight */
     if( i_maxwidth && f_scale_width > (float)i_maxwidth / i_src_width )
     {
         f_scale_width = (float)i_maxwidth / i_src_width;
     }

     if( i_maxheight && f_scale_height > (float)i_maxheight / i_src_height )
     {
         f_scale_height = (float)i_maxheight / i_src_height;
     }


     /* Change aspect ratio from source pixel to scaled pixel */
     f_aspect = f_aspect * f_scale_height / f_scale_width;
     msg_Dbg( p_obj, "scaled pixel aspect is %f:1", f_aspect );

     /* f_scale_width and f_scale_height are now final */
     /* Calculate width, height from scaling
      * Make sure its multiple of 2
      */
     /* width/height of output stream */
     unsigned i_dst_visible_width =  lroundf(f_scale_width*i_src_width);
     unsigned i_dst_visible_height = lroundf(f_scale_height*i_src_height);
     unsigned i_dst_width =  lroundf(f_scale_width*p_src->i_width);
     unsigned i_dst_height = lroundf(f_scale_height*p_src->i_height);

     if( i_dst_visible_width & 1 ) ++i_dst_visible_width;
     if( i_dst_visible_height & 1 ) ++i_dst_visible_height;
     if( i_dst_width & 1 ) ++i_dst_width;
     if( i_dst_height & 1 ) ++i_dst_height;

     /* Store calculated values */
     p_dst->i_width = i_dst_width;
     p_dst->i_visible_width = i_dst_visible_width;
     p_dst->i_height = i_dst_height;
     p_dst->i_visible_height = i_dst_visible_height;

     msg_Dbg( p_obj, "source %ux%u, destination %ux%u",
                     i_src_width, i_src_height,
                     i_dst_visible_width, i_dst_visible_height );
}