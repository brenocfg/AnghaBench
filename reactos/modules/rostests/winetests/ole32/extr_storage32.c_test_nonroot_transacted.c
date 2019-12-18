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
 int /*<<< orphan*/  IStorage_Revert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ STG_E_ACCESSDENIED ; 
 scalar_t__ STG_E_FILENOTFOUND ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_nonroot_transacted(void)
{
    IStorage *stg = NULL, *stg2 = NULL, *stg3 = NULL;
    HRESULT r;
    IStream *stm = NULL;
    static const WCHAR stgname[] = { 'P','E','R','M','S','T','G',0 };
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR stmname2[] = { 'F','O','O',0 };
    BOOL ret;

    DeleteFileA(filenameA);

    /* create a transacted file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a transacted substorage */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        /* create and commit stmname */
        r = IStorage_CreateStream(stg2, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
        ok(r==S_OK, "IStorage->CreateStream failed\n");
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Commit(stg2, 0);

        /* create and revert stmname2 */
        r = IStorage_CreateStream(stg2, stmname2, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
        ok(r==S_OK, "IStorage->CreateStream failed\n");
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Revert(stg2);

        /* check that Commit and Revert really worked */
        r = IStorage_OpenStream(stg2, stmname, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
        ok(r==S_OK, "IStorage->OpenStream should succeed %08x\n", r);
        if (r == S_OK)
            IStream_Release(stm);

        r = IStorage_OpenStream(stg2, stmname2, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
        ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStream should fail %08x\n", r);
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Release(stg2);
    }

    /* create a read-only transacted substorage */
    r = IStorage_OpenStorage(stg, stgname, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED, NULL, 0, &stg2);
    ok(r==S_OK, "IStorage->OpenStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        /* The storage can be modified. */
        r = IStorage_CreateStorage(stg2, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg3);
        ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);
        if (r == S_OK)
            IStorage_Release(stg3);

        /* But changes cannot be committed. */
        r = IStorage_Commit(stg2, 0);
        ok(r==STG_E_ACCESSDENIED, "IStorage->Commit should fail, hr=%08x\n", r);

        IStorage_Release(stg2);
    }

    IStorage_Release(stg);

    /* create a non-transacted file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a transacted substorage */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        /* create and commit stmname */
        r = IStorage_CreateStream(stg2, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
        ok(r==S_OK, "IStorage->CreateStream failed\n");
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Commit(stg2, 0);

        /* create and revert stmname2 */
        r = IStorage_CreateStream(stg2, stmname2, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
        ok(r==S_OK, "IStorage->CreateStream failed\n");
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Revert(stg2);

        /* check that Commit and Revert really worked */
        r = IStorage_OpenStream(stg2, stmname, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
        ok(r==S_OK, "IStorage->OpenStream should succeed %08x\n", r);
        if (r == S_OK)
            IStream_Release(stm);

        r = IStorage_OpenStream(stg2, stmname2, NULL, STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stm );
        ok(r==STG_E_FILENOTFOUND, "IStorage->OpenStream should fail %08x\n", r);
        if (r == S_OK)
            IStream_Release(stm);

        IStorage_Release(stg2);
    }

    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}