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
typedef  int /*<<< orphan*/  strm_value ;
typedef  size_t strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 scalar_t__ strm_array_p (int /*<<< orphan*/ ) ; 
 size_t strm_ary_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
flatmap_len(strm_array ary)
{
  strm_value* v = strm_ary_ptr(ary);
  strm_int i, len, n = 0;

  len = strm_ary_len(ary);
  for (i=0; i<len; i++) {
    if (strm_array_p(v[i])) {
      n += flatmap_len(v[i]);
    }
    else {
      n++;
    }
  }
  return n;
}