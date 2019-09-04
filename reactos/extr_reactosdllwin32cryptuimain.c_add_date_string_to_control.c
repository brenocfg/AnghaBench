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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_SSHORTDATE ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  add_unformatted_text_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_date_string_to_control(HWND hwnd, const FILETIME *fileTime)
{
    WCHAR dateFmt[80]; /* sufficient for all versions of LOCALE_SSHORTDATE */
    WCHAR date[80];
    SYSTEMTIME sysTime;

    GetLocaleInfoW(LOCALE_SYSTEM_DEFAULT, LOCALE_SSHORTDATE, dateFmt, ARRAY_SIZE(dateFmt));
    FileTimeToSystemTime(fileTime, &sysTime);
    GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &sysTime, dateFmt, date, ARRAY_SIZE(date));
    add_unformatted_text_to_control(hwnd, date, lstrlenW(date));
}