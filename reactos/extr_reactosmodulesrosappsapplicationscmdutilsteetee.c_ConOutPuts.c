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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int _tcslen (int /*<<< orphan*/ ) ; 

VOID ConOutPuts (LPTSTR szText)
{
	DWORD dwWritten;

	WriteFile (GetStdHandle (STD_OUTPUT_HANDLE), szText, _tcslen(szText), &dwWritten, NULL);
	WriteFile (GetStdHandle (STD_OUTPUT_HANDLE), _T("\n"), 1, &dwWritten, NULL);
}