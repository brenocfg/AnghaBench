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
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {scalar_t__ mode; } ;
typedef  TYPE_1__ strm_stream ;
typedef  int /*<<< orphan*/  strm_callback ;

/* Variables and functions */
 scalar_t__ strm_dying ; 
 scalar_t__ strm_killed ; 
 int /*<<< orphan*/  strm_task_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_task_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
strm_task_push(strm_stream* strm, strm_callback func, strm_value data)
{
  if (strm->mode == strm_killed || strm->mode == strm_dying)
    return;
  strm_task_add(strm, strm_task_new(func, data));
}