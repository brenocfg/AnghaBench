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
struct timeval {int dummy; } ;
struct strm_time {int utc_offset; struct timeval tv; int /*<<< orphan*/  ns; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  strm_value ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 struct strm_time* malloc (int) ; 
 int /*<<< orphan*/  ns_time ; 
 int /*<<< orphan*/  strm_ptr_value (struct strm_time*) ; 

__attribute__((used)) static int
time_alloc(struct timeval* tv, int utc_offset, strm_value* ret)
{
  struct strm_time* t = malloc(sizeof(struct strm_time));

  if (!t) return STRM_NG;
  t->type = STRM_PTR_AUX;
  t->ns = ns_time;
  t->tv = *tv;
  t->utc_offset = utc_offset;
  *ret = strm_ptr_value(t);
  return STRM_OK;
}