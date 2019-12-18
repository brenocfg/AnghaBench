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
 int L_MAXLENNUM ; 
 int /*<<< orphan*/  cast_uchar (char const) ; 
 char* l_str2dloc (char const*,int /*<<< orphan*/ *,int) ; 
 int ltolower (int /*<<< orphan*/ ) ; 
 char lua_getlocaledecpoint () ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 

__attribute__((used)) static const char *l_str2d (const char *s, lua_Number *result) {
  const char *endptr;
  const char *pmode = strpbrk(s, ".xXnN");
  int mode = pmode ? ltolower(cast_uchar(*pmode)) : 0;
  if (mode == 'n')  /* reject 'inf' and 'nan' */
    return NULL;
  endptr = l_str2dloc(s, result, mode);  /* try to convert */
  if (endptr == NULL) {  /* failed? may be a different locale */
    char buff[L_MAXLENNUM + 1];
    char *pdot = strchr(s, '.');
    if (strlen(s) > L_MAXLENNUM || pdot == NULL)
      return NULL;  /* string too long or no dot; fail */
    strcpy(buff, s);  /* copy string to buffer */
    buff[pdot - s] = lua_getlocaledecpoint();  /* correct decimal point */
    endptr = l_str2dloc(buff, result, mode);  /* try again */
    if (endptr != NULL)
      endptr = s + (endptr - buff);  /* make relative to 's' */
  }
  return endptr;
}