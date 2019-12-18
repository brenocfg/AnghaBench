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
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NOTIFIED2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  INTERNET_STATUS_HANDLE_CLOSING ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPECT2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int close_handle_cnt ; 
 int /*<<< orphan*/  complete_event ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_async_handle(HINTERNET handle, int handle_cnt)
{
    BOOL res;

    close_handle_cnt = handle_cnt;

    SET_EXPECT2(INTERNET_STATUS_HANDLE_CLOSING, handle_cnt);
    res = InternetCloseHandle(handle);
    ok(res, "InternetCloseHandle failed: %u\n", GetLastError());
    WaitForSingleObject(complete_event, INFINITE);
    CHECK_NOTIFIED2(INTERNET_STATUS_HANDLE_CLOSING, handle_cnt);
}