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
struct TYPE_4__ {struct TYPE_4__* path; } ;
typedef  TYPE_1__ FileTxTask ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 

__attribute__((used)) static void
file_tx_task_free (FileTxTask *task)
{
    if (!task)
        return;

    g_free (task->path);
    g_free (task);
}