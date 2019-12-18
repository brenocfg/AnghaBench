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
struct sort_arg {int /*<<< orphan*/  func; int /*<<< orphan*/ * strm; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  mem_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sort_arg*) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ary_sort(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_array ary;
  strm_value* p;
  strm_int len;
  strm_value func;

  strm_get_args(strm, argc, args, "a|v", &p, &len, &func);

  ary = strm_ary_new(p, len);
  p = strm_ary_ptr(ary);
  if (argc == 1) {
    mem_sort(p, len, NULL);
  }
  else {
    struct sort_arg arg;

    arg.strm = strm;
    arg.func = func;
    mem_sort(p, len, &arg);
  }
  *ret = strm_ary_value(ary);
  return STRM_OK;
}