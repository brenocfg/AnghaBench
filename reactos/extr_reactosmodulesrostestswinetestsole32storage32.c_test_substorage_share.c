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
 scalar_t__ IStorage_DestroyElement (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_RenameElement (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STG_E_ACCESSDENIED ; 
 scalar_t__ STG_E_REVERTED ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_substorage_share(void)
{
    IStorage *stg, *stg2, *stg3;
    IStream *stm, *stm2;
    HRESULT r;
    static const WCHAR stgname[] = { 'P','E','R','M','S','T','G',0 };
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR othername[] = { 'N','E','W','N','A','M','E',0 };
    BOOL ret;

    DeleteFileA(filenameA);

    /* create the file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a read/write storage and try to open it again */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        r = IStorage_OpenStorage(stg, stgname, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
        ok(r==STG_E_ACCESSDENIED, "IStorage->OpenStorage should fail %08x\n", r);

        if (r == S_OK)
            IStorage_Release(stg3);

        r = IStorage_OpenStorage(stg, stgname, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
        ok(r==STG_E_ACCESSDENIED, "IStorage->OpenStorage should fail %08x\n", r);

        if (r == S_OK)
            IStorage_Release(stg3);

        /* cannot rename the storage while it's open */
        r = IStorage_RenameElement(stg, stgname, othername);
        ok(r==STG_E_ACCESSDENIED, "IStorage->RenameElement should fail %08x\n", r);
        if (SUCCEEDED(r)) IStorage_RenameElement(stg, othername, stgname);

        /* destroying an object while it's open invalidates it */
        r = IStorage_DestroyElement(stg, stgname);
        ok(r==S_OK, "IStorage->DestroyElement failed, hr=%08x\n", r);

        r = IStorage_CreateStream(stg2, stmname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
        ok(r==STG_E_REVERTED, "IStorage->CreateStream failed, hr=%08x\n", r);

        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Release(stg2);
    }

    /* create a read/write stream and try to open it again */
    r = IStorage_CreateStream(stg, stmname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
    ok(r==S_OK, "IStorage->CreateStream failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        r = IStorage_OpenStream(stg, stmname, NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &stm2);
        ok(r==STG_E_ACCESSDENIED, "IStorage->OpenStream should fail %08x\n", r);

        if (r == S_OK)
            IStream_Release(stm2);

        r = IStorage_OpenStream(stg, stmname, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &stm2);
        ok(r==STG_E_ACCESSDENIED, "IStorage->OpenStream should fail %08x\n", r);

        if (r == S_OK)
            IStream_Release(stm2);

        /* cannot rename the stream while it's open */
        r = IStorage_RenameElement(stg, stmname, othername);
        ok(r==STG_E_ACCESSDENIED, "IStorage->RenameElement should fail %08x\n", r);
        if (SUCCEEDED(r)) IStorage_RenameElement(stg, othername, stmname);

        /* destroying an object while it's open invalidates it */
        r = IStorage_DestroyElement(stg, stmname);
        ok(r==S_OK, "IStorage->DestroyElement failed, hr=%08x\n", r);

        r = IStream_Write(stm, "this shouldn't work\n", 20, NULL);
        ok(r==STG_E_REVERTED, "IStream_Write should fail %08x\n", r);

        IStream_Release(stm);
    }

    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}