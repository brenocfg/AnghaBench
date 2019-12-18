#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  copy_cache_t ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ArchitectureSpecificCopyData ;

/* Variables and functions */
 int /*<<< orphan*/  CopyCleanCache (int /*<<< orphan*/ *) ; 
 int OMX_COLOR_FormatYUV420SemiPlanar ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_CPU_SSE2 () ; 

void ArchitectureSpecificCopyHooksDestroy( int i_color_format,
                                           ArchitectureSpecificCopyData *p_architecture_specific )
{
    if (!p_architecture_specific->data)
        return;
#ifdef CAN_COMPILE_SSE2
    if( i_color_format == OMX_COLOR_FormatYUV420SemiPlanar && vlc_CPU_SSE2() )
    {
        copy_cache_t *p_surface_cache = (copy_cache_t*)p_architecture_specific->data;
        CopyCleanCache(p_surface_cache);
    }
#endif
    free(p_architecture_specific->data);
    p_architecture_specific->data = NULL;
}