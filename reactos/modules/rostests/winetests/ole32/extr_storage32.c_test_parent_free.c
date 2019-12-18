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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  STATSTG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_SetStateBits (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ IStorage_Stat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ STG_E_REVERTED ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_parent_free(void)
{
    IStorage *stg = NULL, *stg2 = NULL, *stg3 = NULL;
    HRESULT r;
    IStream *stm = NULL;
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR stgname[] = { 'P','E','R','M','S','T','G',0 };
    ULONG ref;
    STATSTG statstg;
    BOOL ret;

    DeleteFileA(filenameA);

    /* create the file */
    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE |
                            STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* create a new storage */
    r = IStorage_CreateStorage(stg, stgname, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stg2);
    ok(r==S_OK, "IStorage->CreateStorage failed, hr=%08x\n", r);

    if (r == S_OK)
    {
        /* now create a stream inside the new storage */
        r = IStorage_CreateStream(stg2, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
        ok(r==S_OK, "IStorage->CreateStream failed\n");

        if (r == S_OK)
        {
            /* create a storage inside the new storage */
            r = IStorage_CreateStorage(stg2, stgname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stg3 );
            ok(r==S_OK, "IStorage->CreateStorage failed\n");
        }

        /* free the parent */
        ref = IStorage_Release(stg2);
        ok(ref == 0, "IStorage still has %u references\n", ref);

        /* child objects are invalid */
        if (r == S_OK)
        {
            r = IStream_Write(stm, "this should fail\n", 17, NULL);
            ok(r==STG_E_REVERTED, "IStream->Write should fail, hr=%x\n", r);

            IStream_Release(stm);

            r = IStorage_Stat(stg3, &statstg, STATFLAG_NONAME);
            ok(r==STG_E_REVERTED, "IStorage_Stat should fail %08x\n", r);

            r = IStorage_SetStateBits(stg3, 1, 1);
            ok(r==STG_E_REVERTED, "IStorage_Stat should fail %08x\n", r);

            IStorage_Release(stg3);
        }
    }

    IStorage_Release(stg);

    ret = DeleteFileA(filenameA);
    ok(ret, "deleted file\n");
}