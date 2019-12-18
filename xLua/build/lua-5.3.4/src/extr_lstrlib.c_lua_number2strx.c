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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 size_t SIZELENMOD ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int num2straux (char*,int,int /*<<< orphan*/ ) ; 
 char toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchar (char) ; 

__attribute__((used)) static int lua_number2strx (lua_State *L, char *buff, int sz,
                            const char *fmt, lua_Number x) {
  int n = num2straux(buff, sz, x);
  if (fmt[SIZELENMOD] == 'A') {
    int i;
    for (i = 0; i < n; i++)
      buff[i] = toupper(uchar(buff[i]));
  }
  else if (fmt[SIZELENMOD] != 'a')
    luaL_error(L, "modifiers for format '%%a'/'%%A' not implemented");
  return n;
}