#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int LowPart; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFileMoniker (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMoniker_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_SetSize (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wszFileName1 ; 

__attribute__((used)) static void test_save_load_filemoniker(void)
{
    IMoniker* pMk;
    IStream* pStm;
    HRESULT hr;
    ULARGE_INTEGER size;
    LARGE_INTEGER zero_pos, dead_pos, nulls_pos;
    DWORD some_val = 0xFEDCBA98;
    int i;

    /* see FileMonikerImpl_Save docs */
    zero_pos.QuadPart = 0;
    dead_pos.QuadPart = sizeof(WORD) + sizeof(DWORD) + (lstrlenW(wszFileName1) + 1) + sizeof(WORD);
    nulls_pos.QuadPart = dead_pos.QuadPart + sizeof(WORD);

    /* create the stream we're going to write to */
    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStm);
    ok_ole_success(hr, "CreateStreamOnHGlobal");

    size.u.LowPart = 128;
    hr = IStream_SetSize(pStm, size);
    ok_ole_success(hr, "IStream_SetSize");

    /* create and save a moniker */
    hr = CreateFileMoniker(wszFileName1, &pMk);
    ok_ole_success(hr, "CreateFileMoniker");

    hr = IMoniker_Save(pMk, pStm, TRUE);
    ok_ole_success(hr, "IMoniker_Save");
    IMoniker_Release(pMk);

    /* overwrite the constants with various values */
    hr = IStream_Seek(pStm, zero_pos, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");
    hr = IStream_Write(pStm, &some_val, sizeof(WORD), NULL);
    ok_ole_success(hr, "IStream_Write");

    hr = IStream_Seek(pStm, dead_pos, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");
    hr = IStream_Write(pStm, &some_val, sizeof(WORD), NULL);
    ok_ole_success(hr, "IStream_Write");

    hr = IStream_Seek(pStm, nulls_pos, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");
    for(i = 0; i < 5; ++i){
        hr = IStream_Write(pStm, &some_val, sizeof(DWORD), NULL);
        ok_ole_success(hr, "IStream_Write");
    }

    /* go back to the start of the stream */
    hr = IStream_Seek(pStm, zero_pos, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");

    /* create a new moniker and load into it */
    hr = CreateFileMoniker(wszFileName1, &pMk);
    ok_ole_success(hr, "CreateFileMoniker");

    hr = IMoniker_Load(pMk, pStm);
    ok_ole_success(hr, "IMoniker_Load");

    IMoniker_Release(pMk);
    IStream_Release(pStm);
}