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
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char const**,int*,char const**,int*) ; 
 int /*<<< orphan*/  strm_str_new (char const*,int) ; 

__attribute__((used)) static int
str_split(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  const char* s;
  strm_int slen;
  const char* b;
  const char* t;
  const char* p;
  strm_int plen;
  const char* pend;
  char c;
  strm_int n = 0;
  strm_array ary;
  strm_value* sps;
  strm_int i;

  strm_get_args(strm, argc, args, "s|s", &p, &plen, &s, &slen);
  if (argc == 1) {
    s = " ";
    slen = 1;
  }

  /* count number of split strings */
  c = s[0];
  b = t = p;
  pend = p + plen - slen;
  n = 0;
  while (p<pend) {
    if (*p == c) {
      if (memcmp(p, s, slen) == 0) {
        if (!(slen == 1 && c == ' ' && (p-t) == 0)) {
          n++;
        }
        t = p + slen;
      }
    }
    p++;
  }
  n++;

  /* actual split */
  ary = strm_ary_new(NULL, n);
  sps = strm_ary_ptr(ary);
  c = s[0];
  p = t = b;
  i = 0;
  while (p<pend) {
    if (*p == c) {
      if (memcmp(p, s, slen) == 0) {
        if (!(slen == 1 && c == ' ' && (p-t) == 0)) {
          sps[i++] = strm_str_new(t, p-t);
        }
        t = p + slen;
      }
    }
    p++;
  }
  pend = b + plen;
  sps[i++] = strm_str_new(t, pend-t);
  *ret = strm_ary_value(ary);
  return STRM_OK;
}