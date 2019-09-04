#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int QuadPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_8__ {int LowPart; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_11__ {TYPE_2__ cbSize; int /*<<< orphan*/  clsid; } ;
typedef  TYPE_4__ STATSTG ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateILockBytesOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  ILockBytes_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ILockBytes_Stat (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ILockBytes_WriteAt (int /*<<< orphan*/ *,TYPE_3__,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_Stat (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsEqualCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_CREATE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfileOnILockBytes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ StgOpenStorageOnILockBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_hglobal_storage_creation(void)
{
    ILockBytes *ilb = NULL;
    IStorage *stg = NULL;
    HRESULT r;
    STATSTG stat;
    char junk[512];
    ULARGE_INTEGER offset;

    r = CreateILockBytesOnHGlobal(NULL, TRUE, &ilb);
    ok(r == S_OK, "CreateILockBytesOnHGlobal failed, hr=%x\n", r);

    offset.QuadPart = 0;
    memset(junk, 0xaa, 512);
    r = ILockBytes_WriteAt(ilb, offset, junk, 512, NULL);
    ok(r == S_OK, "ILockBytes_WriteAt failed, hr=%x\n", r);

    offset.QuadPart = 2000;
    r = ILockBytes_WriteAt(ilb, offset, junk, 512, NULL);
    ok(r == S_OK, "ILockBytes_WriteAt failed, hr=%x\n", r);

    r = StgCreateDocfileOnILockBytes(ilb, STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0,  &stg);
    ok(r == S_OK, "StgCreateDocfileOnILockBytes failed, hr=%x\n", r);

    IStorage_Release(stg);

    r = StgOpenStorageOnILockBytes(ilb, NULL, STGM_READ|STGM_SHARE_EXCLUSIVE,
        NULL, 0, &stg);
    ok(r == S_OK, "StgOpenStorageOnILockBytes failed, hr=%x\n", r);

    if (SUCCEEDED(r))
    {
        r = IStorage_Stat(stg, &stat, STATFLAG_NONAME);
        ok(r == S_OK, "StgOpenStorageOnILockBytes failed, hr=%x\n", r);
        ok(IsEqualCLSID(&stat.clsid, &GUID_NULL), "unexpected CLSID value\n");

        IStorage_Release(stg);
    }

    r = ILockBytes_Stat(ilb, &stat, STATFLAG_NONAME);
    ok(r == S_OK, "ILockBytes_Stat failed, hr=%x\n", r);
    ok(stat.cbSize.u.LowPart < 2512, "expected truncated size, got %d\n", stat.cbSize.u.LowPart);

    ILockBytes_Release(ilb);
}