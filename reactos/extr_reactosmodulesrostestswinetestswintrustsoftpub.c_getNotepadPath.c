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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 

__attribute__((used)) static void getNotepadPath(WCHAR *notepadPathW, DWORD size)
{
    static const CHAR notepad[] = "\\notepad.exe";
    CHAR notepadPath[MAX_PATH];

    /* Workaround missing W-functions for win9x */
    GetWindowsDirectoryA(notepadPath, MAX_PATH);
    lstrcatA(notepadPath, notepad);
    MultiByteToWideChar(CP_ACP, 0, notepadPath, -1, notepadPathW, size);
}