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
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  chans; } ;
typedef  TYPE_2__ SeafMqManager ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_NOTIFY_CHAN ; 
 int /*<<< orphan*/  g_async_queue_new_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ json_decref ; 

void
seaf_mq_manager_init (SeafMqManager *mgr)
{
    g_hash_table_replace (mgr->priv->chans, g_strdup (SEAFILE_NOTIFY_CHAN),
                          g_async_queue_new_full ((GDestroyNotify)json_decref));
}