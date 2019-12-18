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
 scalar_t__ IStorage_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE ; 
 int STGC_ONLYIFCURRENT ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ STG_E_FILENOTFOUND ; 
 scalar_t__ STG_E_INVALIDFLAG ; 
 scalar_t__ STG_E_INVALIDFUNCTION ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ StgOpenStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_transact(void)
{
    IStorage *stg = NULL, *stg2 = NULL, *stg3 = NULL;
    HRESULT r;
    IStream *stm = NULL;
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR stmname2[] = { 'F','O','O',0 };
    static const WCHAR stgname[] = { 'P','E','R','M','S','T','G',0 };
    static const WCHAR stgname2[] = { 'T','E','M','P','S','T','G',0 };
    BOOL ret;

    DeleteFileA(filenameA);

    /* create the file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | 
                            STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* commit a new stream and storage */
    r = IStorage_CreateStream(stg, stmname2, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==S_OK, "IStorage->CreateStream failed\n");

    r = IStream_Write(stm, "this is stream 1\n", 16, NULL);
    ok(r==S_OK, "IStream->Write failed\n");

    IStream_Release(stm);

    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        /* Create two substorages but only commit one */
        r = IStorage_CreateStorage(stg2, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
        ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

        if (r == S_OK)
            IStorage_Release(stg3);

        r = IStorage_Commit(stg, 0);
        ok(r==S_OK, "IStorage->Commit failed\n");

        r = IStorage_CreateStorage(stg2, stgname2, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
        ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

        if (r == S_OK)
            IStorage_Release(stg3);

        IStorage_Release(stg2);
    }

    /* now create a stream and storage, but don't commit them */
    stm = NULL;
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==S_OK, "IStorage->CreateStream failed\n");

    r = IStream_Write(stm, "this is stream 2\n", 16, NULL);
    ok(r==S_OK, "IStream->Write failed\n");

    /* IStream::Commit does nothing for OLE storage streams */
    r = IStream_Commit(stm, STGC_ONLYIFCURRENT | STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE);
    ok(r==S_OK, "IStream->Commit failed\n");

    r = IStorage_CreateStorage(stg, stgname2, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
        IStorage_Release(stg2);

    IStream_Release(stm);

    IStorage_Release(stg);

    stm = NULL;
    stg = NULL;
    r = StgOpenStorage( filename, NULL, STGM_SHARE_DENY_NONE | STGM_READ | STGM_TRANSACTED, NULL, 0, &stg);
    ok(r==S_OK, "StgOpenStorage failed\n");

    if (!stg)
        return;

    r = IStorage_OpenStream(stg, stmname, NULL, STGM_SHARE_DENY_NONE|STGM_READ, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->OpenStream failed %08x\n", r);

    r = IStorage_OpenStream(stg, stmname, NULL, STGM_DELETEONRELEASE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
    ok(r==STG_E_INVALIDFUNCTION, "IStorage->OpenStream failed %08x\n", r);

    r = IStorage_OpenStream(stg, stmname, NULL, STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
    ok(r==STG_E_INVALIDFUNCTION, "IStorage->OpenStream failed %08x\n", r);

    r = IStorage_OpenStorage(stg, stmname, NULL, STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg2 );
    ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStream failed %08x\n", r);

    r = IStorage_OpenStream(stg, stmname, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
    ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStream should fail %08x\n", r);
    if (r == S_OK)
        IStream_Release(stm);

    r = IStorage_OpenStorage(stg, stgname2, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg2 );
    ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStorage should fail %08x\n", r);
    if (r == S_OK)
        IStorage_Release(stg2);

    r = IStorage_OpenStorage(stg, stmname2, NULL, STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg2 );
    ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStream failed %08x\n", r);

    r = IStorage_OpenStream(stg, stmname2, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
    ok(r==S_OK, "IStorage->OpenStream should succeed %08x\n", r);
    if (r == S_OK)
        IStream_Release(stm);

    r = IStorage_OpenStorage(stg, stgname, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg2 );
    ok(r==S_OK, "IStorage->OpenStorage should succeed %08x\n", r);
    if (r == S_OK)
    {
        r = IStorage_OpenStorage(stg2, stgname, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg3 );
        ok(r==S_OK, "IStorage->OpenStorage should succeed %08x\n", r);
        if (r == S_OK)
            IStorage_Release(stg3);

        r = IStorage_OpenStorage(stg2, stgname2, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, NULL, 0, &stg3 );
        ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStorage should fail %08x\n", r);
        if (r == S_OK)
            IStorage_Release(stg3);

        IStorage_Release(stg2);
    }

    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}