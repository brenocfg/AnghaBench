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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  LPSYSTEMTIME ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  FileTimeToLocalFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnixTimeToFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void UnixTimeToSystemTime(time_t t, LPSYSTEMTIME pst)
{
    /* Windows specific */
    FILETIME ft;
    UnixTimeToFileTime(t, &ft);
    FileTimeToLocalFileTime(&ft, &ft);   /* Adjust from UTC to local time zone */
    FileTimeToSystemTime(&ft, pst);
}