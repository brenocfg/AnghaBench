#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ vlc_media_source_t ;
struct TYPE_9__ {int /*<<< orphan*/  sd; int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ media_source_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* ms_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_source_provider_Remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sd_Destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_media_source_Delete(vlc_media_source_t *ms)
{
    media_source_private_t *priv = ms_priv(ms);
    vlc_media_source_provider_Remove(priv->owner, ms);
    vlc_sd_Destroy(priv->sd);
    vlc_media_tree_Release(ms->tree);
    free(priv);
}