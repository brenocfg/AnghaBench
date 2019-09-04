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
typedef  int /*<<< orphan*/  data ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,int const*,int,int*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int STGM_DIRECT ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgOpenStorage (int*,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void set_admin_property_stream(LPCSTR file)
{
    IStorage *stg;
    IStream *stm;
    WCHAR fileW[MAX_PATH];
    HRESULT hr;
    DWORD count;
    const DWORD mode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;

    /* AdminProperties */
    static const WCHAR stmname[] = {0x41ca,0x4330,0x3e71,0x44b5,0x4233,0x45f5,0x422c,0x4836,0};
    static const WCHAR data[] = {'M','Y','P','R','O','P','=','2','7','1','8',' ',
        'M','y','P','r','o','p','=','4','2',0};

    MultiByteToWideChar(CP_ACP, 0, file, -1, fileW, MAX_PATH);

    hr = StgOpenStorage(fileW, NULL, mode, NULL, 0, &stg);
    ok(hr == S_OK, "Expected S_OK, got %d\n", hr);
    if (!stg)
        return;

    hr = IStorage_CreateStream(stg, stmname, STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
    ok(hr == S_OK, "Expected S_OK, got %d\n", hr);

    hr = IStream_Write(stm, data, sizeof(data), &count);
    ok(hr == S_OK, "Expected S_OK, got %d\n", hr);

    IStream_Release(stm);
    IStorage_Release(stg);
}