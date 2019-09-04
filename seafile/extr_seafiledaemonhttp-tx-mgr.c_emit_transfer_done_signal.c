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
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  g_signal_emit_by_name (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf ; 

__attribute__((used)) static void
emit_transfer_done_signal (HttpTxTask *task)
{
    if (task->type == HTTP_TASK_TYPE_DOWNLOAD)
        g_signal_emit_by_name (seaf, "repo-http-fetched", task);
    else
        g_signal_emit_by_name (seaf, "repo-http-uploaded", task);
}