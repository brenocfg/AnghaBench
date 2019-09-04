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
typedef  int /*<<< orphan*/  cdio_log_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _handler ; 

cdio_log_handler_t
cdio_log_set_handler(cdio_log_handler_t new_handler)
{
  cdio_log_handler_t old_handler = _handler;

  _handler = new_handler;

  return old_handler;
}