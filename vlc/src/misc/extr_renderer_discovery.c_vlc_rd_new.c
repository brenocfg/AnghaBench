#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vlc_renderer_discovery_owner {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  psz_name; int /*<<< orphan*/ * p_module; struct vlc_renderer_discovery_owner owner; } ;
typedef  TYPE_1__ vlc_renderer_discovery_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char const*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

vlc_renderer_discovery_t *
vlc_rd_new(vlc_object_t *p_obj, const char *psz_name,
           const struct vlc_renderer_discovery_owner *restrict owner)
{
    vlc_renderer_discovery_t *p_rd;

    p_rd = vlc_custom_create(p_obj, sizeof(*p_rd), "renderer discovery");
    if(!p_rd)
        return NULL;
    free(config_ChainCreate(&p_rd->psz_name, &p_rd->p_cfg, psz_name));

    p_rd->owner = *owner;
    p_rd->p_module = module_need(p_rd, "renderer_discovery",
                                 p_rd->psz_name, true);
    if (p_rd->p_module == NULL)
    {
        msg_Err(p_rd, "no suitable renderer discovery module for '%s'",
            psz_name);
        free(p_rd->psz_name);
        config_ChainDestroy(p_rd->p_cfg);
        vlc_object_delete(p_rd);
        p_rd = NULL;
    }

    return p_rd;
}