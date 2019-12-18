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

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ary_each(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value* v;
  strm_int len;
  strm_value func;
  strm_int i;
  strm_value r;

  strm_get_args(strm, argc, args, "av", &v, &len, &func);

  for (i=0; i<len; i++) {
    if (strm_funcall(strm, func, 1, &v[i], &r) == STRM_NG) {
      return STRM_NG;
    }
  }
  *ret = strm_ary_value(args[0]);
  return STRM_OK;
}