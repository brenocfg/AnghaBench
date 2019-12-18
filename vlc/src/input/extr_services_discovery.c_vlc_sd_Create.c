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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct services_discovery_owner_t {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_module; int /*<<< orphan*/  psz_name; struct services_discovery_owner_t owner; int /*<<< orphan*/ * description; int /*<<< orphan*/  p_cfg; } ;
typedef  TYPE_1__ services_discovery_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_ChainCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_sd_Destroy (TYPE_1__*) ; 

services_discovery_t *vlc_sd_Create(vlc_object_t *parent, const char *cfg,
    const struct services_discovery_owner_t *restrict owner)
{
    services_discovery_t *sd = vlc_custom_create(parent, sizeof (*sd),
                                                 "services discovery");
    if (unlikely(sd == NULL))
        return NULL;

    free(config_ChainCreate(&sd->psz_name, &sd->p_cfg, cfg));
    sd->description = NULL;
    sd->owner = *owner;

    sd->p_module = module_need(sd, "services_discovery",
                               sd->psz_name, true);
    if (sd->p_module == NULL)
    {
        msg_Err(sd, "no suitable services discovery module");
        vlc_sd_Destroy(sd);
        sd = NULL;
    }

    return sd;
}