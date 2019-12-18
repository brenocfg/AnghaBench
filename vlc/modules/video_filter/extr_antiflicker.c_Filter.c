#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_20__ {TYPE_6__* p; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_18__ {int i_width; } ;
struct TYPE_19__ {TYPE_1__ video; } ;
struct TYPE_21__ {TYPE_2__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_22__ {int* ia_luminance_data; int* p_old_data; int /*<<< orphan*/  i_softening; int /*<<< orphan*/  i_window_size; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_23__ {int* p_pixels; int i_visible_lines; int i_visible_pitch; int i_pitch; } ;

/* Variables and functions */
 TYPE_3__* CopyInfoAndRelease (TYPE_3__*,TYPE_3__*) ; 
 int GetLuminanceAvg (TYPE_3__*) ; 
 scalar_t__ SCENE_CHANGE_THRESHOLD ; 
 size_t U_PLANE ; 
 size_t V_PLANE ; 
 size_t Y_PLANE ; 
 int __MIN (float,int) ; 
 scalar_t__ abs (int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 TYPE_3__* filter_NewPicture (TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  plane_CopyPixels (TYPE_6__*,TYPE_6__*) ; 

__attribute__((used)) static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    if( !p_pic ) return NULL;

    picture_t *p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_pic );
        return NULL;
    }

    /****************** Get variables *************************/

    filter_sys_t *p_sys = p_filter->p_sys;

    int i_window_size = atomic_load( &p_sys->i_window_size );
    int i_softening = atomic_load( &p_sys->i_softening );

    uint8_t *p_yplane_in = p_pic->p[Y_PLANE].p_pixels;
    uint8_t *p_yplane_out = p_outpic->p[Y_PLANE].p_pixels;
    bool scene_changed = false;

    int i_num_lines = p_pic->p[Y_PLANE].i_visible_lines;
    int i_num_cols = p_pic->p[Y_PLANE].i_visible_pitch;
    int i_in_pitch = p_pic->p[Y_PLANE].i_pitch;
    int i_out_pitch = p_outpic->p[Y_PLANE].i_pitch;

    /******** Get the luminance average for the current picture ********/
    int lum_avg = GetLuminanceAvg(p_pic);

    /*Identify as scene change if the luminance average deviates
     more than the threshold value or if it is the first frame*/

    if( abs(lum_avg - p_sys->
        ia_luminance_data[i_window_size - 1]) > SCENE_CHANGE_THRESHOLD
        || p_sys->ia_luminance_data[i_window_size - 1] == 256)
    {
        scene_changed = true;
    }

    if ( scene_changed )
    {
        //reset the luminance data
        for (int i = 0; i < i_window_size; ++i)
            p_sys->ia_luminance_data[i] = lum_avg;
        plane_CopyPixels( &p_outpic->p[Y_PLANE], &p_pic->p[Y_PLANE] );
    }
    else
    {
        /******* Compute the adjustment factor using moving average ********/
        for (int i = 0; i < i_window_size-1 ; ++i)
            p_sys->ia_luminance_data[i] =
                           p_sys->ia_luminance_data[i+1];

        p_sys->ia_luminance_data[i_window_size - 1] = lum_avg;

        float scale = 1.0;
        if (lum_avg > 0)
        {
             float filt = 0;
             for (int i = 0; i < i_window_size; i++)
                  filt += (float) p_sys->ia_luminance_data[i];
             scale = filt/(i_window_size*lum_avg);
        }

        /******* Apply the adjustment factor to each pixel on Y_PLANE ********/
        uint8_t shift = 8;
        int scale_num = __MIN(scale,255) * ( 1 << shift );

        for( int i_line = 0 ; i_line < i_num_lines ; i_line++ )
        {
            for( int i_col = 0; i_col < i_num_cols  ; i_col++ )
            {
                uint8_t pixel_data = p_yplane_in[i_line*i_in_pitch+i_col];
                int pixel_val = ( scale_num * pixel_data +
                       (1<<(shift -1)) ) >> shift;
                p_yplane_out[i_line*i_out_pitch+i_col] =
                       (pixel_val>255) ? 255:pixel_val;
            }
        }
    }

    /***************** Copy the UV plane as such *****************************/
    plane_CopyPixels( &p_outpic->p[U_PLANE], &p_pic->p[U_PLANE] );
    plane_CopyPixels( &p_outpic->p[V_PLANE], &p_pic->p[V_PLANE] );

    if (scene_changed || i_softening == 0)
    {
       return CopyInfoAndRelease( p_outpic, p_pic );
    }

    /******* Temporal softening phase. Adapted from code by Steven Don ******/
    uint8_t *p_yplane_out_old = p_sys->p_old_data;
    int i_video_width = p_filter->fmt_in.video.i_width;

    for( int i_line = 0 ; i_line < i_num_lines ; i_line++ )
    {
        for( int i_col = 0; i_col < i_num_cols  ; i_col++ )
        {
            uint8_t pixel_data = p_yplane_out[i_line*i_out_pitch+i_col];
            uint8_t pixel_old = p_yplane_out_old[i_line*i_video_width+i_col];
            int diff = abs(pixel_data - pixel_old);
            if (diff < i_softening)
            {
                if (diff > (i_softening >> 1))
                {
                    p_yplane_out_old[i_line*i_video_width+i_col] =
                        ((pixel_data * 2) + pixel_old) /3;
                }
            }
            else
            {
                p_yplane_out_old[i_line*i_video_width+i_col] = pixel_data;
            }
            p_yplane_out[i_line*i_out_pitch+i_col] =
                p_yplane_out_old[i_line*i_video_width+i_col];
        }
    }

    return CopyInfoAndRelease( p_outpic, p_pic );
}