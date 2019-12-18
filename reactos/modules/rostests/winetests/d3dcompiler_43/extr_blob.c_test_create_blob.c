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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  ID3D10Blob ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ D3DERR_INVALIDCALL ; 
 scalar_t__ ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pD3DCreateBlob (int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_create_blob(void)
{
    ID3D10Blob *blob;
    HRESULT hr;
    ULONG refcount;

    hr = pD3DCreateBlob(1, NULL);
    ok(hr == D3DERR_INVALIDCALL, "D3DCreateBlob failed with %x\n", hr);

    hr = pD3DCreateBlob(0, NULL);
    ok(hr == D3DERR_INVALIDCALL, "D3DCreateBlob failed with %x\n", hr);

    hr = pD3DCreateBlob(0, &blob);
    ok(hr == S_OK, "D3DCreateBlob failed with %x\n", hr);

    refcount = ID3D10Blob_Release(blob);
    ok(!refcount, "ID3DBlob has %u references left\n", refcount);
}