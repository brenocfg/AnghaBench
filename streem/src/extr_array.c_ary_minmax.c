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

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ary_minmax(strm_stream* strm, int argc, strm_value* args, strm_value* ret, int min)
{
  strm_value func = strm_nil_value();
  int i, len;
  strm_value* v;
  strm_value e, val;
  double num, f;

  strm_get_args(strm, argc, args, "a|v", &v, &len, &func);
  if (len == 0) {
    *ret = strm_nil_value();
    return STRM_OK;
  }
  val = v[0];
  if (argc == 2) {
    if (strm_funcall(strm, func, 1, &v[0], &e) == STRM_NG) {
      return STRM_NG;
    }
  }
  else {
    e = v[0];
  }
  num = strm_value_float(e);
  for (i=1; i<len; i++) {
    if (argc == 2) {
      if (strm_funcall(strm, func, 1, &v[i], &e) == STRM_NG) {
        return STRM_NG;
      }
    }
    else {
      e = v[0];
    }
    f = strm_value_float(e);
    if (min) {
      if (num > f) {
        num = f;
        val = v[i];
      }
    }
    else {
      if (num < f) {
        num = f;
        val = v[i];
      }
    }
  }
  *ret = val;
  return STRM_OK;
}