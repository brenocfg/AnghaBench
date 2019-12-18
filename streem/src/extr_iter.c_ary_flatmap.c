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
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  flatmap_len (int /*<<< orphan*/ ) ; 
 scalar_t__ flatmap_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ary_flatmap(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_array ary;
  strm_value func;
  strm_array a2;
  strm_value* v2;

  strm_get_args(strm, argc, args, "Av", &ary, &func);
  a2 = strm_ary_new(NULL, flatmap_len(ary));
  v2 = strm_ary_ptr(a2);
  if (flatmap_push(strm, ary, func, &v2) == STRM_NG) {
    return STRM_NG;
  }
  *ret = strm_ary_value(a2);
  return STRM_OK;
}