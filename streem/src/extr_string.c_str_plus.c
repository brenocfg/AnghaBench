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
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_new (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ strm_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
str_plus(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_string str1, str2, str3;
  char *p;

  strm_get_args(strm, argc, args, "SS", &str1, &str2);
  str3 = strm_str_new(NULL, strm_str_len(str1) + strm_str_len(str2));

  p = (char*)strm_str_ptr(str3);
  memcpy(p, strm_str_ptr(str1), strm_str_len(str1));
  memcpy(p+strm_str_len(str1), strm_str_ptr(str2), strm_str_len(str2));
  p[strm_str_len(str3)] = '\0';
  *ret = strm_str_value(str3);
  return STRM_OK;
}