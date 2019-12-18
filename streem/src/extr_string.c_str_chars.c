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
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char const**,int*) ; 
 int /*<<< orphan*/  strm_str_new (char const*,int) ; 
 int /*<<< orphan*/  utf8len (char const*,char const*) ; 

__attribute__((used)) static int
str_chars(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  const char* str;
  const char* s;
  const char* prev = NULL;
  strm_int slen;
  strm_array ary;
  strm_int n = 0;
  strm_value* sps;
  strm_int i = 0;

  strm_get_args(strm, argc, args, "s", &str, &slen);

  s = str;

  while (*s) {
    s += utf8len(s, s + slen);
    n++;
  }

  ary = strm_ary_new(NULL, n);
  sps = strm_ary_ptr(ary);
  s = str;

  while (*s) {
    prev = s;
    s += utf8len(s, s + slen);
    sps[i++] = strm_str_new(prev, s - prev);
  }

  *ret = strm_ary_value(ary);
  return STRM_OK;
}