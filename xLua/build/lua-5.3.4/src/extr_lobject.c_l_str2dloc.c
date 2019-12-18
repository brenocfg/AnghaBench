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
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  cast_uchar (char) ; 
 scalar_t__ lisspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_str2number (char const*,char**) ; 
 int /*<<< orphan*/  lua_strx2number (char const*,char**) ; 

__attribute__((used)) static const char *l_str2dloc (const char *s, lua_Number *result, int mode) {
  char *endptr;
  *result = (mode == 'x') ? lua_strx2number(s, &endptr)  /* try to convert */
                          : lua_str2number(s, &endptr);
  if (endptr == s) return NULL;  /* nothing recognized? */
  while (lisspace(cast_uchar(*endptr))) endptr++;  /* skip trailing spaces */
  return (*endptr == '\0') ? endptr : NULL;  /* OK if no trailing characters */
}