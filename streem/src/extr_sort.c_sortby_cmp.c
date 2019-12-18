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
struct sortby_value {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sortby_cmp(const void* a_p, const void* b_p)
{
  struct sortby_value* av = (struct sortby_value*)a_p;
  struct sortby_value* bv = (struct sortby_value*)b_p;
  double a, b;

  if (strm_number_p(av->v)) {
    a = strm_value_float(av->v);
  }
  else {
    if (strm_number_p(bv->v)) {
      return 1;
    }
    return 0;
  }
  if (strm_number_p(bv->v)) {
    b = strm_value_float(bv->v);
  }
  else {
    return -1;
  }
  if(a > b)
    return 1;
  else if(a < b)
    return -1;
  return 0;
}