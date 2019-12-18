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
 int MAX_ISOPATHNAME ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int iso9660_dirname_valid_p (char*) ; 
 scalar_t__ iso9660_is_dchar (char const) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

bool
iso9660_pathname_valid_p (const char pathname[])
{
  const char *p = NULL;

  cdio_assert (pathname != NULL);

  if ((p = strrchr (pathname, '/')))
    {
      bool rc;
      char *_tmp = strdup (pathname);

      *strrchr (_tmp, '/') = '\0';

      rc = iso9660_dirname_valid_p (_tmp);

      free (_tmp);

      if (!rc)
        return false;

      p++;
    }
  else
    p = pathname;

  if (strlen (pathname) > (MAX_ISOPATHNAME - 6))
    return false;

  {
    int len = 0;
    int dots = 0;

    for (; *p; p++)
      if (iso9660_is_dchar (*p))
        {
          len++;
          if (dots == 0 ? len > 8 : len > 3)
            return false;
        }
      else if (*p == '.')
        {
          dots++;
          if (dots > 1)
            return false;
          if (!len)
            return false;
          len = 0;
        }
      else
        return false;

    if (dots != 1)
      return false;
  }

  return true;
}