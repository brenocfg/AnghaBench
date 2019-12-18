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
struct strm_task {int /*<<< orphan*/  data; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_callback ;

/* Variables and functions */
 struct strm_task* malloc (int) ; 

struct strm_task*
strm_task_new(strm_callback func, strm_value data)
{
  struct strm_task *t;
 
  t = malloc(sizeof(struct strm_task));
  t->func = func;
  t->data = data;

  return t;
}