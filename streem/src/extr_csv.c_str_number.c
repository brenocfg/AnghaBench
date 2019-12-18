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
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  TYPE_NUM ; 
 int /*<<< orphan*/  csv_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
str_number(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value s;

  strm_get_args(strm, argc, args, "S", &s);
  s = csv_value(strm_str_ptr(s), strm_str_len(s), TYPE_NUM);
  if (!strm_number_p(s)) {
    strm_raise(strm, "invalid string for number");
    return STRM_NG;
  }
  *ret = s;
  return STRM_OK;
}