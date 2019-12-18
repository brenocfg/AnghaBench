#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int i_output; TYPE_2__* p_output; } ;
typedef  TYPE_1__ video_splitter_t ;
struct TYPE_5__ {int /*<<< orphan*/  fmt; struct TYPE_5__* psz_module; } ;
typedef  TYPE_2__ video_splitter_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    video_splitter_t *p_splitter = (video_splitter_t*)p_this;

    for( int i = 0; i < p_splitter->i_output; i++ )
    {
        video_splitter_output_t *p_cfg = &p_splitter->p_output[i];

        free( p_cfg->psz_module );
        video_format_Clean( &p_cfg->fmt );
    }
    free( p_splitter->p_output );
}