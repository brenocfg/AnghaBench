#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; } ;
typedef  TYPE_1__ GCstr ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int LUA_IDSIZE ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdata (TYPE_1__*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void lj_debug_shortname(char *out, GCstr *str, BCLine line)
{
  const char *src = strdata(str);
  if (*src == '=') {
    strncpy(out, src+1, LUA_IDSIZE);  /* Remove first char. */
    out[LUA_IDSIZE-1] = '\0';  /* Ensures null termination. */
  } else if (*src == '@') {  /* Output "source", or "...source". */
    size_t len = str->len-1;
    src++;  /* Skip the `@' */
    if (len >= LUA_IDSIZE) {
      src += len-(LUA_IDSIZE-4);  /* Get last part of file name. */
      *out++ = '.'; *out++ = '.'; *out++ = '.';
    }
    strcpy(out, src);
  } else {  /* Output [string "string"] or [builtin:name]. */
    size_t len;  /* Length, up to first control char. */
    for (len = 0; len < LUA_IDSIZE-12; len++)
      if (((const unsigned char *)src)[len] < ' ') break;
    strcpy(out, line == ~(BCLine)0 ? "[builtin:" : "[string \""); out += 9;
    if (src[len] != '\0') {  /* Must truncate? */
      if (len > LUA_IDSIZE-15) len = LUA_IDSIZE-15;
      strncpy(out, src, len); out += len;
      strcpy(out, "..."); out += 3;
    } else {
      strcpy(out, src); out += len;
    }
    strcpy(out, line == ~(BCLine)0 ? "]" : "\"]");
  }
}