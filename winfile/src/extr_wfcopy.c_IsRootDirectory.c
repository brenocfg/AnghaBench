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
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SZ_BACKSLASH ; 
 int /*<<< orphan*/  SZ_COLON ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpi (scalar_t__*,int /*<<< orphan*/ ) ; 

BOOL
IsRootDirectory(register LPTSTR pPath)
{
  if (!lstrcmpi(pPath+1, TEXT(":\\")))
      return(TRUE);
  if (!lstrcmpi(pPath, SZ_BACKSLASH))
      return(TRUE);
  if (!lstrcmpi(pPath+1, SZ_COLON))
      return(TRUE);

   // checking unc!

  if (*pPath == CHAR_BACKSLASH && *(pPath+1) == CHAR_BACKSLASH) {   /* some sort of UNC name */
    LPTSTR p;
    int cBackslashes=0;

    for (p=pPath+2; *p; ) {
      if (*p == CHAR_BACKSLASH && (++cBackslashes > 1))
   return FALSE;  /* not a bare UNC name, therefore not a root dir */

   p++;

    }
    return TRUE;  /* end of string with only 1 more backslash */
                  /* must be a bare UNC, which looks like a root dir */
  }

  return(FALSE);
}