#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_media_source_t ;
struct TYPE_5__ {int /*<<< orphan*/  media_sources; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_media_source_provider_t ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 TYPE_4__* ms_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_media_source_New (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_media_source_t *
vlc_media_source_provider_Add(vlc_media_source_provider_t *provider,
                              const char *name)
{
    vlc_mutex_assert(&provider->lock);

    vlc_media_source_t *ms = vlc_media_source_New(provider, name);
    if (unlikely(!ms))
        return NULL;

    vlc_list_append(&ms_priv(ms)->node, &provider->media_sources);
    return ms;
}