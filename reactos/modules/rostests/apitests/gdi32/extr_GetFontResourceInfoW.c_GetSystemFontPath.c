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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemFontDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
GetSystemFontPath(LPWSTR pszPath, LPCWSTR pszFile)
{
    GetSystemFontDirectory(pszPath);
    lstrcatW(pszPath, L"\\");
    lstrcatW(pszPath, pszFile);
}