#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strm_task {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_task_add (int /*<<< orphan*/ *,struct strm_task*) ; 
 int /*<<< orphan*/ * strm_value_foreign (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
io_task_add(struct strm_task* task)
{
  strm_stream* strm = strm_value_foreign(task->data);
  task->data = strm_nil_value();
  strm_task_add(strm, task);
}