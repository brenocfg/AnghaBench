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
struct TYPE_3__ {int /*<<< orphan*/  p_config_chain; int /*<<< orphan*/  psz_lang; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ transcode_encoder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void transcode_encoder_config_clean( transcode_encoder_config_t *p_cfg )
{
    free( p_cfg->psz_name );
    free( p_cfg->psz_lang );
    config_ChainDestroy( p_cfg->p_config_chain );
}