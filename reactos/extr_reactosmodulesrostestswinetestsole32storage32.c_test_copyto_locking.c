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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ IStorage_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_copyto_locking(void)
{
    IStorage *stg, *stg2, *stg3, *stg4;
    IStream *stm;
    HRESULT r;
    static const WCHAR stgname[] = { 'S','T','G','1',0 };
    static const WCHAR stgname2[] = { 'S','T','G','2',0 };
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    BOOL ret;

    DeleteFileA(filenameA);

    /* create the file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a substorage */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    /* create another substorage */
    r = IStorage_CreateStorage(stg, stgname2, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    /* add a stream, and leave it open */
    r = IStorage_CreateStream(stg2, stmname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
    ok(r==S_OK, "IStorage->CreateStream failed, hr=%08x\n", r);

    /* Try to copy the storage while the stream is open */
    r = IStorage_CopyTo(stg2, 0, NULL, NULL, stg3);
    ok(r==S_OK, "IStorage->CopyTo failed, hr=%08x\n", r);

    IStream_Release(stm);

    /* create a substorage */
    r = IStorage_CreateStorage(stg2, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg4);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    /* Try to copy the storage while the substorage is open */
    r = IStorage_CopyTo(stg2, 0, NULL, NULL, stg3);
    ok(r==S_OK, "IStorage->CopyTo failed, hr=%08x\n", r);

    IStorage_Release(stg4);
    IStorage_Release(stg3);
    IStorage_Release(stg2);
    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}