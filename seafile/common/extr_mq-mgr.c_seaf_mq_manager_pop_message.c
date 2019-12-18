#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  chans; } ;
typedef  TYPE_2__ SeafMqManager ;
typedef  int /*<<< orphan*/  GAsyncQueue ;

/* Variables and functions */
 char* SEAFILE_NOTIFY_CHAN ; 
 int /*<<< orphan*/ * g_async_queue_try_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

json_t *
seaf_mq_manager_pop_message (SeafMqManager *mgr)
{
    const char *chan = SEAFILE_NOTIFY_CHAN;
    GAsyncQueue *async_queue = g_hash_table_lookup (mgr->priv->chans, chan);
    if (!async_queue) {
        seaf_warning ("Unkonwn message channel %s.\n", chan);
        return NULL;
    }

    return g_async_queue_try_pop (async_queue);
}