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
typedef  int /*<<< orphan*/  LCID ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoA (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAX_ELEM_LEN ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int compare_info(LCID lcid, DWORD flags, char* buff, const char* cmp, BOOL exact)
{
  int len;

  if(!cmp[0])
      return 0;

  buff[0] = 0;
  GetLocaleInfoA(lcid, flags|LOCALE_NOUSEROVERRIDE, buff, MAX_ELEM_LEN);
  if (!buff[0])
    return 0;

  /* Partial matches are only allowed on language/country names */
  len = strlen(cmp);
  if(exact || len<=3)
    return !strcasecmp(cmp, buff);
  else
    return !strncasecmp(cmp, buff, len);
}