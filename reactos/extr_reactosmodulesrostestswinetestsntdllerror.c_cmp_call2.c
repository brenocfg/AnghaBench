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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ ERROR_MR_MID_NOT_FOUND ; 
 int /*<<< orphan*/  ok (int,char*,char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pRtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strict ; 

__attribute__((used)) static void cmp_call2(NTSTATUS win_nt, ULONG win32, const char* message)
{
    ULONG err;

    err = pRtlNtStatusToDosError(win_nt);
    ok(err == win32 ||
       (!strict && err == ERROR_MR_MID_NOT_FOUND),
       "%s (%x): got %u, expected %u (or MID_NOT_FOUND)\n",
       message, win_nt, err, win32);
}