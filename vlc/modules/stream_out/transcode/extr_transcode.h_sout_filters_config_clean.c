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
struct TYPE_4__ {scalar_t__ psz_spu_sources; int /*<<< orphan*/  p_deinterlace_cfg; scalar_t__ psz_deinterlace; } ;
struct TYPE_5__ {TYPE_1__ video; scalar_t__ psz_filters; } ;
typedef  TYPE_2__ sout_filters_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static inline
void sout_filters_config_clean( sout_filters_config_t *p_cfg )
{
    free( p_cfg->psz_filters );
    if( p_cfg->video.psz_deinterlace )
    {
        free( p_cfg->video.psz_deinterlace );
        config_ChainDestroy( p_cfg->video.p_deinterlace_cfg );
    }
    free( p_cfg->video.psz_spu_sources );
}