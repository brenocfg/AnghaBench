#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int ULONG ;
struct TYPE_6__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IID_IPersist ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_DestroyElement (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IStream_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,unsigned char*,int,int*) ; 
 scalar_t__ IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int,TYPE_1__*) ; 
 scalar_t__ IStream_SetSize (int /*<<< orphan*/ *,TYPE_1__) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  STGC_DEFAULT ; 
 int STGM_CREATE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int STGM_SHARE_DENY_WRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 int STGM_WRITE ; 
 scalar_t__ STG_E_FILEALREADYEXISTS ; 
 scalar_t__ STG_E_INVALIDFLAG ; 
 scalar_t__ STG_E_INVALIDFUNCTION ; 
 scalar_t__ STG_E_INVALIDNAME ; 
 scalar_t__ STG_E_INVALIDPARAMETER ; 
 scalar_t__ STG_E_INVALIDPOINTER ; 
 scalar_t__ STG_E_REVERTED ; 
 int STREAM_SEEK_END ; 
 int STREAM_SEEK_SET ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ StgOpenStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_storage_stream(void)
{
    static const WCHAR stmname[] = { 'C','O','N','T','E','N','T','S',0 };
    static const WCHAR longname[] = {
        'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a',
        'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a',0
    };
    IStorage *stg = NULL;
    HRESULT r;
    IStream *stm = NULL;
    IStream *stm2 = NULL;
    ULONG count = 0;
    LARGE_INTEGER pos;
    ULARGE_INTEGER p;
    unsigned char buffer[0x100];
    IUnknown *unk;
    BOOL ret;

    DeleteFileA(filenameA);

    r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
    ok(r==S_OK, "StgCreateDocfile failed\n");

    /* try create some invalid streams */
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 1, 0, &stm );
    ok(r==STG_E_INVALIDPARAMETER, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 1, &stm );
    ok(r==STG_E_INVALIDPARAMETER, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, NULL );
    ok(r==STG_E_INVALIDPOINTER, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, NULL, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==STG_E_INVALIDNAME, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, longname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==STG_E_INVALIDNAME || broken(r==S_OK) /* nt4 */,
       "IStorage->CreateStream wrong error, got %d GetLastError()=%d\n", r, GetLastError());
    r = IStorage_CreateStream(stg, stmname, STGM_READWRITE, 0, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_READ, 0, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_WRITE, 0, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_DENY_NONE | STGM_READWRITE, 0, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->CreateStream wrong error\n");
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_DENY_NONE | STGM_READ, 0, 0, &stm );
    ok(r==STG_E_INVALIDFLAG, "IStorage->CreateStream wrong error\n");

    /* now really create a stream and delete it */
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==S_OK, "IStorage->CreateStream failed\n");

    /* test for support interfaces */
    r = IStream_QueryInterface(stm, &IID_IPersist, (void**)&unk);
    ok(r==E_NOINTERFACE, "got 0x%08x\n", r);
    r = IStream_QueryInterface(stm, &IID_IPersistStream, (void**)&unk);
    ok(r==E_NOINTERFACE, "got 0x%08x\n", r);

    r = IStream_Release(stm);
    ok(r == 0, "wrong ref count\n");
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==STG_E_FILEALREADYEXISTS, "IStorage->CreateStream failed\n");
    r = IStorage_DestroyElement(stg,stmname);
    ok(r==S_OK, "IStorage->DestroyElement failed\n");

    /* create a stream and write to it */
    r = IStorage_CreateStream(stg, stmname, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm );
    ok(r==S_OK, "IStorage->CreateStream failed\n");

    r = IStream_Clone(stm, &stm2);
    ok(r==S_OK, "failed to clone stream\n");

    r = IStream_Write(stm, NULL, 0, NULL );
    ok(r==STG_E_INVALIDPOINTER, "IStream->Write wrong error\n");
    r = IStream_Write(stm, "Hello\n", 0, NULL );
    ok(r==S_OK, "failed to write stream\n");
    r = IStream_Write(stm, "Hello\n", 0, &count );
    ok(r==S_OK, "failed to write stream\n");
    r = IStream_Write(stm, "Hello\n", 6, &count );
    ok(r==S_OK, "failed to write stream\n");
    r = IStream_Commit(stm, STGC_DEFAULT );
    ok(r==S_OK, "failed to commit stream\n");
    r = IStream_Commit(stm, STGC_DEFAULT );
    ok(r==S_OK, "failed to commit stream\n");

    /* Read past the end of the stream. */
    pos.QuadPart = 3;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 3, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 3, "read bytes past end of stream\n");
    pos.QuadPart = 10;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 10, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 0, "read bytes past end of stream\n");
    pos.QuadPart = 10000;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 10000, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 0, "read bytes past end of stream\n");

    /* Convert to a big block stream, and read past the end. */
    p.QuadPart = 5000;
    r = IStream_SetSize(stm,p);
    ok(r==S_OK, "failed to set pos\n");
    pos.QuadPart = 4997;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 4997, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 3, "read bytes past end of stream\n");
    pos.QuadPart = 5001;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 5001, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 0, "read bytes past end of stream\n");
    pos.QuadPart = 10000;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 10000, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to read\n");
    ok(count == 0, "read bytes past end of stream\n");

    /* seek round a bit, reset the stream size */
    pos.QuadPart = 0;
    r = IStream_Seek(stm, pos, 3, &p );
    ok(r==STG_E_INVALIDFUNCTION, "IStream->Seek returned wrong error\n");
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, NULL);
    ok(r==S_OK, "failed to seek stream\n");
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    r = IStream_SetSize(stm,p);
    ok(r==S_OK, "failed to set pos\n");
    pos.QuadPart = 10;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 10, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to set pos\n");
    ok(count == 0, "read bytes from empty stream\n");
    pos.QuadPart = 10000;
    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 10000, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to set pos\n");
    ok(count == 0, "read bytes from empty stream\n");
    pos.QuadPart = 0;
    r = IStream_Seek(stm, pos, STREAM_SEEK_END, &p );
    ok(r==S_OK, "failed to seek stream\n");
    ok(p.QuadPart == 0, "at wrong place\n");
    r = IStream_Read(stm, buffer, sizeof buffer, &count );
    ok(r==S_OK, "failed to set pos\n");
    ok(count == 0, "read bytes from empty stream\n");

    /* wrap up */
    r = IStream_Release(stm2);
    ok(r == 0, "wrong ref count\n");

    /* create a stream and write to it */
    r = IStorage_CreateStream(stg, stmname, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stm2 );
    ok(r==S_OK, "IStorage->CreateStream failed\n");

    r = IStream_Seek(stm, pos, STREAM_SEEK_SET, &p);
    ok(r==STG_E_REVERTED, "overwritten stream should return STG_E_REVERTED instead of 0x%08x\n", r);

    r = IStream_Release(stm2);
    ok(r == 0, "wrong ref count\n");
    r = IStream_Release(stm);
    ok(r == 0, "wrong ref count\n");

    r = IStorage_Release(stg);
    ok(r == 0, "wrong ref count\n");

    /* try create some invalid streams */
    stg = NULL;
    stm = NULL;
    r = StgOpenStorage(filename, NULL, STGM_READ | STGM_SHARE_DENY_WRITE, NULL, 0, &stg);
    ok(r == S_OK, "should succeed\n");
    if (stg)
    {
        r = IStorage_OpenStream(stg, stmname, NULL, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stm);
        ok(r == STG_E_INVALIDFLAG, "IStorage->OpenStream should return STG_E_INVALIDFLAG instead of 0x%08x\n", r);
        IStorage_Release(stg);
    }

    ret = DeleteFileA(filenameA);
    ok(ret, "file should exist\n");
}