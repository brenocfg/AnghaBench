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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ CHAR_COLON ; 
 int /*<<< orphan*/  COUNTOF (scalar_t__*) ; 
 int /*<<< orphan*/  GetWindowText (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  lstrcpy (scalar_t__*,scalar_t__*) ; 

VOID
GetSearchPath(HWND hWnd, LPWSTR pszPath)
{
   LPWSTR p;

   WCHAR szTemp[MAXPATHLEN+32];

   // the search window doesn't have a current directory
   GetWindowText(hWnd, szTemp, COUNTOF(szTemp));

   // the window text looks like "Search Results: C:\FOO\BAR\*.*"

   p = szTemp;
   while (*p && *p != CHAR_COLON) // find the :
      ++p;

   p += 2;                 // skip the ": "

   lstrcpy(pszPath, p);
}