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
struct sort_arg {int dummy; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_int ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sort_arg*) ; 
 int /*<<< orphan*/  sort_cmp ; 
 int /*<<< orphan*/  sort_cmpf ; 

__attribute__((used)) static void
mem_sort(strm_value* p, strm_int len, struct sort_arg *arg)
{
  if (arg) {                    /* sort(ary, func) */
    qsort_arg(p, len, sizeof(strm_value), sort_cmpf, arg);
  }
  else {                        /* sort(ary) */
    qsort(p, len, sizeof(strm_value), sort_cmp);
  }
}