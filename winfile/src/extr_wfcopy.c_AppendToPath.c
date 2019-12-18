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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__* LPTSTR ;
typedef  scalar_t__* LPCTSTR ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 int /*<<< orphan*/  lstrcpy (scalar_t__*,scalar_t__*) ; 

VOID
AppendToPath(LPTSTR pPath, LPCTSTR pMore)
{

  /* Don't append a \ to empty paths. */
  if (*pPath)
    {
      while (*pPath)
          pPath++;

      if (pPath[-1]!=CHAR_BACKSLASH)
          *pPath++=CHAR_BACKSLASH;
    }

  /* Skip any initial terminators on input. */
  while (*pMore == CHAR_BACKSLASH)
      pMore++;

  lstrcpy(pPath, pMore);
}