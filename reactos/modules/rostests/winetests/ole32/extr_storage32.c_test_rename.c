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
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_RenameElement (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STG_E_FILENOTFOUND ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_rename(void)
{
    IStorage *stg, *stg2;
    IStream *stm;
    HRESULT r;
    static const WCHAR stgname[] = { 'P','E','R','M','S','T','G',0 };
    static const WCHAR stgname2[] = { 'S','T','G',0 };
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR stmname2[] = { 'E','N','T','S',0 };
    BOOL ret;

    DeleteFileA(filenameA);

    /* create the file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a substorage */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    /* create a stream in the substorage */
    r = IStorage_CreateStream(stg2, stmname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
    ok(r==S_OK, "IStorage->CreateStream failed, hr=%08x\n", r);
    IStream_Release(stm);

    /* rename the stream */
    r = IStorage_RenameElement(stg2, stmname, stmname2);
    ok(r==S_OK, "IStorage->RenameElement failed, hr=%08x\n", r);

    /* cannot open stream with old name */
    r = IStorage_OpenStream(stg2, stmname, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &stm);
    ok(r==STG_E_FILENOTFOUND, "IStorage_OpenStream should fail, hr=%08x\n", r);
    if (SUCCEEDED(r)) IStream_Release(stm);

    /* can open stream with new name */
    r = IStorage_OpenStream(stg2, stmname2, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &stm);
    ok(r==S_OK, "IStorage_OpenStream failed, hr=%08x\n", r);
    if (SUCCEEDED(r)) IStream_Release(stm);

    IStorage_Release(stg2);

    /* rename the storage */
    IStorage_RenameElement(stg, stgname, stgname2);

    /* cannot open storage with old name */
    r = IStorage_OpenStorage(stg, stgname, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &stg2);
    ok(r==STG_E_FILENOTFOUND, "IStorage_OpenStream should fail, hr=%08x\n", r);
    if (SUCCEEDED(r)) IStorage_Release(stg2);

    /* can open storage with new name */
    r = IStorage_OpenStorage(stg, stgname2, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &stg2);
    ok(r==S_OK, "IStorage_OpenStream should fail, hr=%08x\n", r);
    if (SUCCEEDED(r))
    {
        /* opened storage still has the stream */
        r = IStorage_OpenStream(stg2, stmname2, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &stm);
        ok(r==S_OK, "IStorage_OpenStream failed, hr=%08x\n", r);
        if (SUCCEEDED(r)) IStream_Release(stm);

        IStorage_Release(stg2);
    }

    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}