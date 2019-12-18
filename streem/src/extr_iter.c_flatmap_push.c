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
typedef  int /*<<< orphan*/  strm_stream ;
typedef  size_t strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ strm_array_p (int /*<<< orphan*/ ) ; 
 size_t strm_ary_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flatmap_push(strm_stream* strm, strm_array ary, strm_value func, strm_value** p)
{
  strm_value* v = strm_ary_ptr(ary);
  strm_int i, len;

  len = strm_ary_len(ary);
  for (i=0; i<len; i++) {
    if (strm_array_p(v[i])) {
      if (flatmap_push(strm, v[i], func, p) == STRM_NG) {
        return STRM_NG;
      }
    }
    else {
      if (strm_funcall(strm, func, 1, &v[i], *p) == STRM_NG) {
        return STRM_NG;
      }
      *p += 1;
    }
  }
  return STRM_OK;
}