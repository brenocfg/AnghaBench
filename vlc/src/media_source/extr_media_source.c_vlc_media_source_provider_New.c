#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  media_sources; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_media_source_provider_t ;

/* Variables and functions */
 TYPE_1__* CreateObject (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

vlc_media_source_provider_t *
vlc_media_source_provider_New(vlc_object_t *parent)
{
    vlc_media_source_provider_t *provider =
            CreateObject(parent, sizeof(*provider), "media-source-provider");
    if (unlikely(!provider))
        return NULL;

    vlc_mutex_init(&provider->lock);
    vlc_list_init(&provider->media_sources);
    return provider;
}