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
struct TYPE_4__ {int type; int grfMode; int /*<<< orphan*/  clsid; int /*<<< orphan*/ * pwcsName; } ;
typedef  TYPE_1__ STATSTG ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CreateILockBytesOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ILockBytes_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_Stat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STGM_CREATE ; 
 scalar_t__ STGM_READWRITE ; 
 scalar_t__ STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfileOnILockBytes (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ StgIsStorageILockBytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WriteClassStg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  test_stg_cls ; 

__attribute__((used)) static void test_hglobal_storage_stat(void)
{
    ILockBytes *ilb = NULL;
    IStorage *stg = NULL;
    HRESULT r;
    STATSTG stat;
    DWORD mode, refcount;

    r = CreateILockBytesOnHGlobal( NULL, TRUE, &ilb );
    ok( r == S_OK, "CreateILockBytesOnHGlobal failed\n");

    r = StgIsStorageILockBytes( ilb );
    ok( r == S_FALSE, "StgIsStorageILockBytes should have failed\n");

    mode = STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE;/*0x1012*/
    r = StgCreateDocfileOnILockBytes( ilb, mode, 0,  &stg );
    ok( r == S_OK, "StgCreateDocfileOnILockBytes failed\n");

    r = WriteClassStg( stg, &test_stg_cls );
    ok( r == S_OK, "WriteClassStg failed\n");

    r = StgIsStorageILockBytes( ilb );
    ok( r == S_OK, "StgIsStorageILockBytes failed\n");

    memset( &stat, 0, sizeof stat );
    r = IStorage_Stat( stg, &stat, 0 );

    ok( stat.pwcsName == NULL, "storage name not null\n");
    ok( stat.type == 1, "type is wrong\n");
    ok( stat.grfMode == 0x12, "grf mode is incorrect\n");
    ok( !memcmp(&stat.clsid, &test_stg_cls, sizeof test_stg_cls), "CLSID is wrong\n");

    refcount = IStorage_Release( stg );
    ok( refcount == 0, "IStorage refcount is wrong\n");
    refcount = ILockBytes_Release( ilb );
    ok( refcount == 0, "ILockBytes refcount is wrong\n");
}