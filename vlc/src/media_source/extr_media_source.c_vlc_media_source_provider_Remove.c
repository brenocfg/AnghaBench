#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_media_source_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_media_source_provider_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 TYPE_3__* ms_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_media_source_provider_Remove(vlc_media_source_provider_t *provider,
                                 vlc_media_source_t *ms)
{
    vlc_mutex_lock(&provider->lock);
    vlc_list_remove(&ms_priv(ms)->node);
    vlc_mutex_unlock(&provider->lock);
}