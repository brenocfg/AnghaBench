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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ const ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const*) ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  stgA_name ; 
 int /*<<< orphan*/  stgB_name ; 
 int /*<<< orphan*/  strmA_name ; 
 int /*<<< orphan*/  strmB_name ; 
 int /*<<< orphan*/  strmC_name ; 

__attribute__((used)) static HRESULT create_test_file(IStorage *dest)
{
    IStorage *stgA = NULL, *stgB = NULL;
    IStream *strmA = NULL, *strmB = NULL, *strmC = NULL;
    const ULONG strmA_name_size = lstrlenW(strmA_name) * sizeof(WCHAR);
    const ULONG strmB_name_size = lstrlenW(strmB_name) * sizeof(WCHAR);
    const ULONG strmC_name_size = lstrlenW(strmC_name) * sizeof(WCHAR);
    ULONG bytes;
    HRESULT hr;

    hr = IStorage_CreateStorage(dest, stgA_name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stgA);
    ok(hr == S_OK, "IStorage_CreateStorage failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = IStorage_CreateStream(stgA, strmA_name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &strmA);
    ok(hr == S_OK, "IStorage_CreateStream failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = IStream_Write(strmA, strmA_name, strmA_name_size, &bytes);
    ok(hr == S_OK && bytes == strmA_name_size, "IStream_Write failed: 0x%08x, %d of %d bytes written\n", hr, bytes, strmA_name_size);

    hr = IStorage_CreateStorage(dest, stgB_name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stgB);
    ok(hr == S_OK, "IStorage_CreateStorage failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = IStorage_CreateStream(stgB, strmB_name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &strmB);
    ok(hr == S_OK, "IStorage_CreateStream failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = IStream_Write(strmB, strmB_name, strmB_name_size, &bytes);
    ok(hr == S_OK && bytes == strmB_name_size, "IStream_Write failed: 0x%08x, %d of %d bytes written\n", hr, bytes, strmB_name_size);

    hr = IStorage_CreateStream(dest, strmC_name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &strmC);
    ok(hr == S_OK, "IStorage_CreateStream failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = IStream_Write(strmC, strmC_name, strmC_name_size, &bytes);
    ok(hr == S_OK && bytes == strmC_name_size, "IStream_Write failed: 0x%08x, %d of %d bytes written\n", hr, bytes, strmC_name_size);

cleanup:
    if(strmC)
        IStream_Release(strmC);
    if(strmB)
        IStream_Release(strmB);
    if(stgB)
        IStorage_Release(stgB);
    if(strmA)
        IStream_Release(strmA);
    if(stgA)
        IStorage_Release(stgA);

    return hr;
}