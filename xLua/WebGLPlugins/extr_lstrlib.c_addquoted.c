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
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 scalar_t__ iscntrl (scalar_t__) ; 
 int /*<<< orphan*/  isdigit (scalar_t__) ; 
 int /*<<< orphan*/  l_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ uchar (char const) ; 

__attribute__((used)) static void addquoted (luaL_Buffer *b, const char *s, size_t len) {
  luaL_addchar(b, '"');
  while (len--) {
    if (*s == '"' || *s == '\\' || *s == '\n') {
      luaL_addchar(b, '\\');
      luaL_addchar(b, *s);
    }
    else if (iscntrl(uchar(*s))) {
      char buff[10];
      if (!isdigit(uchar(*(s+1))))
        l_sprintf(buff, sizeof(buff), "\\%d", (int)uchar(*s));
      else
        l_sprintf(buff, sizeof(buff), "\\%03d", (int)uchar(*s));
      luaL_addstring(b, buff);
    }
    else
      luaL_addchar(b, *s);
    s++;
  }
  luaL_addchar(b, '"');
}