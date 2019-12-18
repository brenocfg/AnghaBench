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
typedef  int /*<<< orphan*/  vlc_media_source_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_media_source_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_media_source_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_media_source_provider_Add (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * vlc_media_source_provider_Find (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_media_source_t *
vlc_media_source_provider_GetMediaSource(vlc_media_source_provider_t *provider,
                                         const char *name)
{
    vlc_mutex_lock(&provider->lock);
    vlc_media_source_t *ms = vlc_media_source_provider_Find(provider, name);
    if (ms)
        vlc_media_source_Hold(ms);
    else
        ms = vlc_media_source_provider_Add(provider, name);
    vlc_mutex_unlock(&provider->lock);

    return ms;
}