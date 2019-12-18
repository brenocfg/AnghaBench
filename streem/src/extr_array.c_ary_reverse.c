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
typedef  int strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static int
ary_reverse(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value* v;
  strm_value* v2;
  strm_int len;
  strm_array ary;
  strm_int i;

  strm_get_args(strm, argc, args, "a", &v, &len);
  ary = strm_ary_new(NULL, len);
  v2 = strm_ary_ptr(ary);
  for (i=0; i<len; i++) {
    v2[len-i-1] = v[i];
  }
  *ret = strm_ary_value(ary);
  return STRM_OK;
}