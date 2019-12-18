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
typedef  scalar_t__ strm_string ;
typedef  int /*<<< orphan*/  strm_state ;
typedef  int strm_int ;
typedef  scalar_t__ strm_array ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,int) ; 
 scalar_t__ str_dump (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_dump_len (scalar_t__) ; 
 int /*<<< orphan*/  str_symbol_p (scalar_t__) ; 
 scalar_t__ strm_array_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_ary_headers (scalar_t__) ; 
 int strm_ary_len (scalar_t__) ; 
 int /*<<< orphan*/ * strm_ary_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (scalar_t__) ; 
 scalar_t__ strm_ns_name (int /*<<< orphan*/ *) ; 
 int strm_str_len (scalar_t__) ; 
 scalar_t__ strm_str_new (char*,int) ; 
 scalar_t__ strm_str_null ; 
 int /*<<< orphan*/  strm_str_ptr (scalar_t__) ; 
 scalar_t__ strm_string_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_ary (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_str (int /*<<< orphan*/ ) ; 

strm_string
strm_inspect(strm_value v)
{
  if (strm_string_p(v)) {
    strm_string str = strm_value_str(v);
    return str_dump(str, str_dump_len(str));
  }
  else if (strm_array_p(v)) {
    strm_state* ns = strm_ary_ns(v);
    char *buf = malloc(32);
    strm_int i, bi = 0, capa = 32;
    strm_array a = strm_value_ary(v);

    if (buf == NULL) return STRM_NG;
    buf[bi++] = '[';
    if (ns) {
      strm_string name = strm_ns_name(ns);
      strm_int nlen = strm_str_len(name);

      if (name != strm_str_null) {
        buf[bi++] = '@';
        if (bi+nlen+2 > capa) {
          char* p;
          capa *= 2;
          p = realloc(buf, capa);
          if (p == NULL) {
            free(buf);
            return STRM_NG;
          }
          buf = p;
        }
        memcpy(buf+bi, strm_str_ptr(name), nlen);
        bi += nlen;
        if (strm_ary_len(a) > 0) {
          buf[bi++] = ' ';
        }
      }
    }
    for (i=0; i<strm_ary_len(a); i++) {
      strm_string str = strm_inspect(strm_ary_ptr(a)[i]);
      strm_string key = (strm_ary_headers(a) &&
                         strm_string_p(strm_ary_ptr(strm_ary_headers(a))[i])) ?
        strm_value_str(strm_ary_ptr(strm_ary_headers(a))[i]) : strm_str_null;
      strm_int slen = (key ? (strm_str_len(key)+1) : 0) + strm_str_len(str) + 3;

      if (bi+slen > capa) {
        capa *= 2;
        buf = realloc(buf, capa);
      }
      if (i > 0) {
        buf[bi++] = ',';
        buf[bi++] = ' ';
      }
      if (key) {
        if (!str_symbol_p(key)) {
          key = str_dump(key, str_dump_len(key));
        }
        memcpy(buf+bi, strm_str_ptr(key), strm_str_len(key));
        bi += strm_str_len(key);
        buf[bi++] = ':';
      }
      memcpy(buf+bi, strm_str_ptr(str), strm_str_len(str));
      bi += strm_str_len(str);
    }
    buf[bi++] = ']';
    return strm_str_new(buf, bi);
  }
  else {
    return strm_to_str(v);
  }
}