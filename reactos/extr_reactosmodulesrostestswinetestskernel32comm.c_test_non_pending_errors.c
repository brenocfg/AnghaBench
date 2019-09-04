#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ByteSize; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;

/* Variables and functions */
 int CE_MODE ; 
 int /*<<< orphan*/  ClearCommError (scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetCommState (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_non_pending_errors(void)
{
    HANDLE hcom;
    DCB dcb;
    DWORD err;

    hcom = test_OpenComm(FALSE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    ok(GetCommState(hcom, &dcb), "GetCommState failed\n");
    dcb.ByteSize = 255; /* likely bogus */
    ok(!SetCommState(hcom, &dcb), "SetCommState should have failed\n");
    ok(ClearCommError(hcom, &err, NULL), "ClearCommError should succeed\n");
    ok(!(err & CE_MODE), "ClearCommError shouldn't set CE_MODE byte in this case (%x)\n", err);

    CloseHandle(hcom);
}