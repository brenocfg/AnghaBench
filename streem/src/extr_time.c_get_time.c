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
struct strm_time {scalar_t__ ns; } ;
typedef  int /*<<< orphan*/  strm_value ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 scalar_t__ ns_time ; 
 scalar_t__ strm_value_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct strm_time*
get_time(strm_value val)
{
  struct strm_time* t = (struct strm_time*)strm_value_ptr(val, STRM_PTR_AUX);
  if (t->ns != ns_time) return NULL;
  return t;
}