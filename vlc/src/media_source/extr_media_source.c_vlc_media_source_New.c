#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  description; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ vlc_media_source_t ;
typedef  int /*<<< orphan*/  vlc_media_source_provider_t ;
struct services_discovery_owner_t {TYPE_1__* sys; int /*<<< orphan*/ * cbs; } ;
struct TYPE_8__ {int /*<<< orphan*/ * owner; TYPE_3__* sd; int /*<<< orphan*/  name; TYPE_1__ public_data; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ media_source_private_t ;
struct TYPE_9__ {int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sd_cbs ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_New () ; 
 int /*<<< orphan*/  vlc_media_tree_Release (int /*<<< orphan*/ ) ; 
 TYPE_3__* vlc_sd_Create (int /*<<< orphan*/ *,char const*,struct services_discovery_owner_t*) ; 

__attribute__((used)) static vlc_media_source_t *
vlc_media_source_New(vlc_media_source_provider_t *provider, const char *name)
{
    media_source_private_t *priv = malloc(sizeof(*priv) + strlen(name) + 1);
    if (unlikely(!priv))
        return NULL;

    vlc_atomic_rc_init(&priv->rc);

    vlc_media_source_t *ms = &priv->public_data;

    /* vlc_sd_Create() may call services_discovery_item_added(), which will read
     * its tree, so it must be initialized first */
    ms->tree = vlc_media_tree_New();
    if (unlikely(!ms->tree))
    {
        free(priv);
        return NULL;
    }

    strcpy(priv->name, name);

    struct services_discovery_owner_t owner = {
        .cbs = &sd_cbs,
        .sys = ms,
    };

    priv->sd = vlc_sd_Create(provider, name, &owner);
    if (unlikely(!priv->sd))
    {
        vlc_media_tree_Release(ms->tree);
        free(priv);
        return NULL;
    }

    /* sd->description is set during vlc_sd_Create() */
    ms->description = priv->sd->description;

    priv->owner = provider;

    return ms;
}