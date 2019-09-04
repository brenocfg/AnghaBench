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

/* Variables and functions */
 scalar_t__ MAX_ISOPATHNAME ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ iso9660_is_dchar (char const) ; 
 scalar_t__ strlen (char const*) ; 

bool
iso9660_dirname_valid_p (const char pathname[])
{
  const char *p = pathname;
  int len;

  cdio_assert (pathname != NULL);

  if (*p == '/' || *p == '.' || *p == '\0')
    return false;

  if (strlen (pathname) > MAX_ISOPATHNAME)
    return false;

  len = 0;
  for (; *p; p++)
    if (iso9660_is_dchar (*p))
      {
        len++;
        if (len > 8)
          return false;
      }
    else if (*p == '/')
      {
        if (!len)
          return false;
        len = 0;
      }
    else
      return false; /* unexpected char */

  if (!len)
    return false; /* last char may not be '/' */

  return true;
}