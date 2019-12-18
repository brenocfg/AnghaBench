#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  psz_name; int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ vlc_renderer_discovery_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void vlc_rd_release(vlc_renderer_discovery_t *p_rd)
{
    module_unneed(p_rd, p_rd->p_module);
    config_ChainDestroy(p_rd->p_cfg);
    free(p_rd->psz_name);
    vlc_object_delete(p_rd);
}