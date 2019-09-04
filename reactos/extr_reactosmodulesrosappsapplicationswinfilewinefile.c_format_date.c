#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 scalar_t__ BUFFER_LEN ; 
 int COL_DATE ; 
 int COL_TIME ; 
 int /*<<< orphan*/  FileTimeToLocalFileTime (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sQMarks ; 

__attribute__((used)) static void format_date(const FILETIME* ft, WCHAR* buffer, int visible_cols)
{
	SYSTEMTIME systime;
	FILETIME lft;
	int len = 0;

	*buffer = '\0';

	if (!ft->dwLowDateTime && !ft->dwHighDateTime)
		return;

	if (!FileTimeToLocalFileTime(ft, &lft))
		{err: lstrcpyW(buffer,sQMarks); return;}

	if (!FileTimeToSystemTime(&lft, &systime))
		goto err;

	if (visible_cols & COL_DATE) {
		len = GetDateFormatW(LOCALE_USER_DEFAULT, 0, &systime, 0, buffer, BUFFER_LEN);
		if (!len)
			goto err;
	}

	if (visible_cols & COL_TIME) {
		if (len)
			buffer[len-1] = ' ';

		buffer[len++] = ' ';

		if (!GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &systime, 0, buffer+len, BUFFER_LEN-len))
			buffer[len] = '\0';
	}
}