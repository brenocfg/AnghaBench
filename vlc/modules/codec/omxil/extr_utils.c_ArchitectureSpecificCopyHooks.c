#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_7__ {TYPE_1__ fmt_out; } ;
typedef  TYPE_2__ decoder_t ;
typedef  int /*<<< orphan*/  copy_cache_t ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ArchitectureSpecificCopyData ;

/* Variables and functions */
 scalar_t__ CopyInitCache (int /*<<< orphan*/ *,int) ; 
 int OMX_COLOR_FormatYUV420SemiPlanar ; 
 int /*<<< orphan*/  VLC_CODEC_YV12 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ vlc_CPU_SSE2 () ; 

void ArchitectureSpecificCopyHooks( decoder_t *p_dec, int i_color_format,
                                    int i_slice_height, int i_src_stride,
                                    ArchitectureSpecificCopyData *p_architecture_specific )
{
    (void)i_slice_height;

#ifdef CAN_COMPILE_SSE2
    if( i_color_format == OMX_COLOR_FormatYUV420SemiPlanar && vlc_CPU_SSE2() )
    {
        copy_cache_t *p_surface_cache = malloc( sizeof(copy_cache_t) );
        if( !p_surface_cache || CopyInitCache( p_surface_cache, i_src_stride ) )
        {
            free( p_surface_cache );
            return;
        }
        p_architecture_specific->data = p_surface_cache;
        p_dec->fmt_out.i_codec = VLC_CODEC_YV12;
    }
#endif
}