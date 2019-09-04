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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  upload_tasks; int /*<<< orphan*/  download_tasks; } ;
typedef  TYPE_2__ HttpTxManager ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_foreach_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_task_help ; 

__attribute__((used)) static void
clean_tasks_for_repo (HttpTxManager *manager, const char *repo_id)
{
    g_hash_table_foreach_remove (manager->priv->download_tasks,
                                 remove_task_help, (gpointer)repo_id);

    g_hash_table_foreach_remove (manager->priv->upload_tasks,
                                 remove_task_help, (gpointer)repo_id);
}