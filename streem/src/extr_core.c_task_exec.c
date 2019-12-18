#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct strm_task {scalar_t__ (* func ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_7__ {scalar_t__ mode; } ;
typedef  TYPE_1__ strm_stream ;
typedef  scalar_t__ (* strm_callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int /*<<< orphan*/  free (struct strm_task*) ; 
 scalar_t__ strm_dying ; 
 int /*<<< orphan*/  strm_eprint (TYPE_1__*) ; 
 scalar_t__ strm_killed ; 
 scalar_t__ strm_option_verbose ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
task_exec(strm_stream* strm, struct strm_task* task)
{
  strm_callback func = task->func;
  strm_value data = task->data;

  free(task);
  if (strm->mode == strm_killed) return;
  if ((*func)(strm, data) == STRM_NG) {
    if (strm_option_verbose) {
      strm_eprint(strm);
    }
  }
  if (strm->mode == strm_dying) {
    strm_stream_close(strm);
  }
}