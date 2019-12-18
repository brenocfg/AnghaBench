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
struct strm_task {int dummy; } ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  strm_callback ;

/* Variables and functions */
 int /*<<< orphan*/  strm_foreign_value (int /*<<< orphan*/ *) ; 
 struct strm_task* strm_task_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct strm_task*
io_task(strm_stream* strm, strm_callback func)
{
  return strm_task_new(func, strm_foreign_value(strm));
}