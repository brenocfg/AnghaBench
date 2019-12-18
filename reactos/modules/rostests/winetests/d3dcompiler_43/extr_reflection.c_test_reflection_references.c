#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_9__ {TYPE_1__* lpVtbl; } ;
struct TYPE_8__ {int (* Release ) (TYPE_2__*) ;int /*<<< orphan*/  (* QueryInterface ) (TYPE_2__*,int /*<<< orphan*/ *,void**) ;} ;
typedef  TYPE_2__ ID3D11ShaderReflection ;
typedef  int /*<<< orphan*/  ID3D10ShaderReflection1 ;
typedef  int /*<<< orphan*/  ID3D10ShaderReflection ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_ID3D10ShaderReflection ; 
 int /*<<< orphan*/  IID_ID3D10ShaderReflection1 ; 
 int /*<<< orphan*/  IID_ID3D11ShaderReflection ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pD3DReflect (int*,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 
 int stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 
 int stub5 (TYPE_2__*) ; 
 int* test_reflection_blob ; 

__attribute__((used)) static void test_reflection_references(void)
{
    HRESULT hr;
    ULONG count;
    ID3D11ShaderReflection *ref11, *ref11_test;
    ID3D10ShaderReflection *ref10;
    ID3D10ShaderReflection1 *ref10_1;

    hr = pD3DReflect(test_reflection_blob, test_reflection_blob[6], &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == S_OK, "D3DReflect failed, got %x, expected %x\n", hr, S_OK);

    hr = ref11->lpVtbl->QueryInterface(ref11, &IID_ID3D11ShaderReflection, (void **)&ref11_test);
    ok(hr == S_OK, "QueryInterface failed, got %x, expected %x\n", hr, S_OK);

    count = ref11_test->lpVtbl->Release(ref11_test);
    ok(count == 1, "Release failed %u\n", count);

    hr = ref11->lpVtbl->QueryInterface(ref11, &IID_ID3D10ShaderReflection, (void **)&ref10);
    ok(hr == E_NOINTERFACE, "QueryInterface failed, got %x, expected %x\n", hr, E_NOINTERFACE);

    hr = ref11->lpVtbl->QueryInterface(ref11, &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == E_NOINTERFACE, "QueryInterface failed, got %x, expected %x\n", hr, E_NOINTERFACE);

    count = ref11->lpVtbl->Release(ref11);
    ok(count == 0, "Release failed %u\n", count);

    /* check invalid cases */
    hr = pD3DReflect(test_reflection_blob, test_reflection_blob[6], &IID_ID3D10ShaderReflection, (void **)&ref10);
    ok(hr == E_NOINTERFACE, "D3DReflect failed, got %x, expected %x\n", hr, E_NOINTERFACE);

    hr = pD3DReflect(test_reflection_blob, test_reflection_blob[6], &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == E_NOINTERFACE, "D3DReflect failed, got %x, expected %x\n", hr, E_NOINTERFACE);

    hr = pD3DReflect(NULL, test_reflection_blob[6], &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == D3DERR_INVALIDCALL, "D3DReflect failed, got %x, expected %x\n", hr, D3DERR_INVALIDCALL);

    hr = pD3DReflect(NULL, test_reflection_blob[6], &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == D3DERR_INVALIDCALL, "D3DReflect failed, got %x, expected %x\n", hr, D3DERR_INVALIDCALL);

    /* returns different errors with different sizes */
    hr = pD3DReflect(test_reflection_blob, 31, &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == D3DERR_INVALIDCALL, "D3DReflect failed, got %x, expected %x\n", hr, D3DERR_INVALIDCALL);

    hr = pD3DReflect(test_reflection_blob,  32, &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == E_FAIL, "D3DReflect failed, got %x, expected %x\n", hr, E_FAIL);

    hr = pD3DReflect(test_reflection_blob, test_reflection_blob[6]-1, &IID_ID3D10ShaderReflection1, (void **)&ref10_1);
    ok(hr == E_FAIL, "D3DReflect failed, got %x, expected %x\n", hr, E_FAIL);

    hr = pD3DReflect(test_reflection_blob,  31, &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == D3DERR_INVALIDCALL, "D3DReflect failed, got %x, expected %x\n", hr, D3DERR_INVALIDCALL);

    hr = pD3DReflect(test_reflection_blob,  32, &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == E_FAIL, "D3DReflect failed, got %x, expected %x\n", hr, E_FAIL);

    hr = pD3DReflect(test_reflection_blob,  test_reflection_blob[6]-1, &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == E_FAIL, "D3DReflect failed, got %x, expected %x\n", hr, E_FAIL);
}