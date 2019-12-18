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
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  OemToCharBuffW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  get_file_nameA (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 

void get_file_nameW(CHAR** command_line, WCHAR* filename, int max_filename)
{
    CHAR filenameA[_MAX_PATH];
    int len;

    get_file_nameA(command_line, filenameA, _MAX_PATH);
    len = strlen(filenameA);
    OemToCharBuffW(filenameA, filename, max_filename);
    filename[len] = _T('\0');
/*
    UNICODE_STRING UnicodeString;
    ANSI_STRING AnsiString;
    CHAR filenameA[_MAX_PATH];

    get_file_nameA(command_line, filenameA, _MAX_PATH);

    //RtlInitAnsiString(&AnsiString, filenameA);
    UnicodeString.Buffer = filename;
    UnicodeString.MaximumLength = max_filename;//MAX_PATH;
    RtlAnsiStringToUnicodeString(&UnicodeString, &AnsiString, FALSE);
 */
}