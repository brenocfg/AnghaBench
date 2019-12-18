#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_22__ {TYPE_1__ format; TYPE_2__* p; } ;
typedef  TYPE_3__ picture_t ;
typedef  int int32_t ;
struct TYPE_23__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_24__ {scalar_t__ (* pf_process_sat_hue_clip ) (TYPE_3__*,TYPE_3__*,int,int,int,int,int) ;scalar_t__ (* pf_process_sat_hue ) (TYPE_3__*,TYPE_3__*,int,int,int,int,int) ;int /*<<< orphan*/  b_brightness_threshold; int /*<<< orphan*/  f_gamma; int /*<<< orphan*/  f_saturation; int /*<<< orphan*/  f_hue; int /*<<< orphan*/  f_brightness; int /*<<< orphan*/  f_contrast; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_21__ {int i_pitch; int i_visible_pitch; size_t* p_pixels; int i_visible_lines; } ;

/* Variables and functions */
 TYPE_3__* CopyInfoAndRelease (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ GetPackedYuvOffsets (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int M_PI ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 
 size_t clip_uint8_vlc (int) ; 
 int cos (double) ; 
 TYPE_3__* filter_NewPicture (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 double pow (int,double) ; 
 int sin (double) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_3__*,int,int,int,int,int) ; 
 scalar_t__ stub2 (TYPE_3__*,TYPE_3__*,int,int,int,int,int) ; 
 double vlc_atomic_load_float (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *FilterPacked( filter_t *p_filter, picture_t *p_pic )
{
    int pi_luma[256];
    int pi_gamma[256];

    picture_t *p_outpic;
    uint8_t *p_in, *p_in_end, *p_line_end;
    uint8_t *p_out;
    int i_y_offset, i_u_offset, i_v_offset;

    int i_pitch, i_visible_pitch;

    double  f_hue;
    double  f_gamma;
    int32_t i_cont, i_lum;
    int i_sat, i_sin, i_cos, i_x, i_y;

    filter_sys_t *p_sys = p_filter->p_sys;

    if( !p_pic ) return NULL;

    i_pitch = p_pic->p->i_pitch;
    i_visible_pitch = p_pic->p->i_visible_pitch;

    if( GetPackedYuvOffsets( p_pic->format.i_chroma, &i_y_offset,
                             &i_u_offset, &i_v_offset ) != VLC_SUCCESS )
    {
        msg_Warn( p_filter, "Unsupported input chroma (%4.4s)",
                  (char*)&(p_pic->format.i_chroma) );

        picture_Release( p_pic );
        return NULL;
    }

    p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        msg_Warn( p_filter, "can't get output picture" );

        picture_Release( p_pic );
        return NULL;
    }

    /* Get variables */
    i_cont = (int)( vlc_atomic_load_float( &p_sys->f_contrast ) * 255 );
    i_lum = (int)( (vlc_atomic_load_float( &p_sys->f_brightness ) - 1.0)*255 );
    f_hue = vlc_atomic_load_float( &p_sys->f_hue ) * (float)(M_PI / 180.);
    i_sat = (int)( vlc_atomic_load_float( &p_sys->f_saturation ) * 256 );
    f_gamma = 1.0 / vlc_atomic_load_float( &p_sys->f_gamma );

    /*
     * Threshold mode drops out everything about luma, contrast and gamma.
     */
    if( !atomic_load( &p_sys->b_brightness_threshold ) )
    {

        /* Contrast is a fast but kludged function, so I put this gap to be
         * cleaner :) */
        i_lum += 128 - i_cont / 2;

        /* Fill the gamma lookup table */
        for( int i = 0 ; i < 256 ; i++ )
        {
          pi_gamma[ i ] = clip_uint8_vlc( pow(i / 255.0, f_gamma) * 255.0);
        }

        /* Fill the luma lookup table */
        for( int i = 0 ; i < 256 ; i++ )
        {
            pi_luma[ i ] = pi_gamma[clip_uint8_vlc( i_lum + i_cont * i / 256)];
        }
    }
    else
    {
        /*
         * We get luma as threshold value: the higher it is, the darker is
         * the image. Should I reverse this?
         */
        for( int i = 0 ; i < 256 ; i++ )
        {
            pi_luma[ i ] = (i < i_lum) ? 0 : 255;
        }

        /*
         * Desaturates image to avoid that strange yellow halo...
         */
        i_sat = 0;
    }

    /*
     * Do the Y plane
     */

    p_in = p_pic->p->p_pixels + i_y_offset;
    p_in_end = p_in + p_pic->p->i_visible_lines * p_pic->p->i_pitch - 8 * 4;

    p_out = p_outpic->p->p_pixels + i_y_offset;

    for( ; p_in < p_in_end ; )
    {
        p_line_end = p_in + i_visible_pitch - 8 * 4;

        for( ; p_in < p_line_end ; )
        {
            /* Do 8 pixels at a time */
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
        }

        p_line_end += 8 * 4;

        for( ; p_in < p_line_end ; )
        {
            *p_out = pi_luma[ *p_in ]; p_in += 2; p_out += 2;
        }

        p_in += i_pitch - p_pic->p->i_visible_pitch;
        p_out += i_pitch - p_outpic->p->i_visible_pitch;
    }

    /*
     * Do the U and V planes
     */

    i_sin = sin(f_hue) * 256;
    i_cos = cos(f_hue) * 256;

    i_x = ( cos(f_hue) + sin(f_hue) ) * 32768;
    i_y = ( cos(f_hue) - sin(f_hue) ) * 32768;

    if ( i_sat > 256 )
    {
        if ( p_sys->pf_process_sat_hue_clip( p_pic, p_outpic, i_sin, i_cos, i_sat,
                                             i_x, i_y ) != VLC_SUCCESS )
        {
            /* Currently only one error can happen in the function, but if there
             * will be more of them, this message must go away */
            msg_Warn( p_filter, "Unsupported input chroma (%4.4s)",
                      (char*)&(p_pic->format.i_chroma) );
            picture_Release( p_pic );
            return NULL;
        }
    }
    else
    {
        if ( p_sys->pf_process_sat_hue( p_pic, p_outpic, i_sin, i_cos, i_sat,
                                        i_x, i_y ) != VLC_SUCCESS )
        {
            /* Currently only one error can happen in the function, but if there
             * will be more of them, this message must go away */
            msg_Warn( p_filter, "Unsupported input chroma (%4.4s)",
                      (char*)&(p_pic->format.i_chroma) );
            picture_Release( p_pic );
            return NULL;
        }
    }

    return CopyInfoAndRelease( p_outpic, p_pic );
}