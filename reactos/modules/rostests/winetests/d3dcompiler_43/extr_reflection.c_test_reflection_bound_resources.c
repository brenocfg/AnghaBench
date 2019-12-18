#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_25__ {char* Name; int /*<<< orphan*/  NumSamples; int /*<<< orphan*/  Dimension; int /*<<< orphan*/  ReturnType; int /*<<< orphan*/  uFlags; int /*<<< orphan*/  BindCount; int /*<<< orphan*/  BindPoint; int /*<<< orphan*/  Type; } ;
struct TYPE_24__ {TYPE_1__* lpVtbl; } ;
struct TYPE_23__ {scalar_t__ (* GetResourceBindingDesc ) (TYPE_2__*,int,TYPE_3__*) ;scalar_t__ (* GetResourceBindingDescByName ) (TYPE_2__*,char*,TYPE_3__*) ;scalar_t__ (* Release ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ ID3D11ShaderReflection ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ D3D11_SHADER_INPUT_BIND_DESC ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_ID3D11ShaderReflection ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pD3DReflect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ stub1 (TYPE_2__*,int,TYPE_3__*) ; 
 scalar_t__ stub2 (TYPE_2__*,int,TYPE_3__*) ; 
 scalar_t__ stub3 (TYPE_2__*,char*,TYPE_3__*) ; 
 scalar_t__ stub4 (TYPE_2__*,char*,TYPE_3__*) ; 
 scalar_t__ stub5 (TYPE_2__*,char*,TYPE_3__*) ; 
 scalar_t__ stub6 (TYPE_2__*,char*,TYPE_3__*) ; 
 scalar_t__ stub7 (TYPE_2__*,unsigned int,TYPE_3__*) ; 
 scalar_t__ stub8 (TYPE_2__*,char*,TYPE_3__*) ; 
 scalar_t__ stub9 (TYPE_2__*) ; 
 int /*<<< orphan*/ * test_reflection_bound_resources_blob ; 
 TYPE_3__* test_reflection_bound_resources_result ; 

__attribute__((used)) static void test_reflection_bound_resources(void)
{
    HRESULT hr;
    ULONG count;
    ID3D11ShaderReflection *ref11;
    D3D11_SHADER_INPUT_BIND_DESC desc;
    const D3D11_SHADER_INPUT_BIND_DESC *pdesc;
    unsigned int i;

    hr = pD3DReflect(test_reflection_bound_resources_blob, test_reflection_bound_resources_blob[6], &IID_ID3D11ShaderReflection, (void **)&ref11);
    ok(hr == S_OK, "D3DReflect failed %x\n", hr);

    /* check invalid cases */
    hr = ref11->lpVtbl->GetResourceBindingDesc(ref11, 0, NULL);
    ok(hr == E_INVALIDARG, "GetResourceBindingDesc failed, got %x, expected %x\n", hr, E_INVALIDARG);

    hr = ref11->lpVtbl->GetResourceBindingDesc(ref11, 0xffffffff, &desc);
    ok(hr == E_INVALIDARG, "GetResourceBindingDesc failed, got %x, expected %x\n", hr, E_INVALIDARG);

    hr = ref11->lpVtbl->GetResourceBindingDescByName(ref11, NULL, &desc);
    ok(hr == E_INVALIDARG, "GetResourceBindingDescByName failed, got %x, expected %x\n", hr, E_INVALIDARG);

    hr = ref11->lpVtbl->GetResourceBindingDescByName(ref11, "sam", NULL);
    ok(hr == E_INVALIDARG, "GetResourceBindingDescByName failed, got %x, expected %x\n", hr, E_INVALIDARG);

    hr = ref11->lpVtbl->GetResourceBindingDescByName(ref11, "invalid", NULL);
    ok(hr == E_INVALIDARG, "GetResourceBindingDescByName failed, got %x, expected %x\n", hr, E_INVALIDARG);

    hr = ref11->lpVtbl->GetResourceBindingDescByName(ref11, "invalid", &desc);
    ok(hr == E_INVALIDARG, "GetResourceBindingDescByName failed, got %x, expected %x\n", hr, E_INVALIDARG);

    /* GetResourceBindingDesc */
    for (i = 0; i < ARRAY_SIZE(test_reflection_bound_resources_result); ++i)
    {
        pdesc = &test_reflection_bound_resources_result[i];

        hr = ref11->lpVtbl->GetResourceBindingDesc(ref11, i, &desc);
        ok(hr == S_OK, "GetResourceBindingDesc(%u) failed, got %x, expected %x\n", i, hr, S_OK);

        ok(!strcmp(desc.Name, pdesc->Name), "GetResourceBindingDesc(%u) Name failed, got \"%s\", expected \"%s\"\n",
                i, desc.Name, pdesc->Name);
        ok(desc.Type == pdesc->Type, "GetResourceBindingDesc(%u) Type failed, got %x, expected %x\n",
                i, desc.Type, pdesc->Type);
        ok(desc.BindPoint == pdesc->BindPoint, "GetResourceBindingDesc(%u) BindPoint failed, got %u, expected %u\n",
                i, desc.BindPoint, pdesc->BindPoint);
        ok(desc.BindCount == pdesc->BindCount, "GetResourceBindingDesc(%u) BindCount failed, got %u, expected %u\n",
                i, desc.BindCount, pdesc->BindCount);
        ok(desc.uFlags == pdesc->uFlags, "GetResourceBindingDesc(%u) uFlags failed, got %u, expected %u\n",
                i, desc.uFlags, pdesc->uFlags);
        ok(desc.ReturnType == pdesc->ReturnType, "GetResourceBindingDesc(%u) ReturnType failed, got %x, expected %x\n",
                i, desc.ReturnType, pdesc->ReturnType);
        ok(desc.Dimension == pdesc->Dimension, "GetResourceBindingDesc(%u) Dimension failed, got %x, expected %x\n",
                i, desc.Dimension, pdesc->Dimension);
        ok(desc.NumSamples == pdesc->NumSamples, "GetResourceBindingDesc(%u) NumSamples failed, got %u, expected %u\n",
                i, desc.NumSamples, pdesc->NumSamples);
    }

    /* GetResourceBindingDescByName */
    for (i = 0; i < ARRAY_SIZE(test_reflection_bound_resources_result); ++i)
    {
        pdesc = &test_reflection_bound_resources_result[i];

        hr = ref11->lpVtbl->GetResourceBindingDescByName(ref11, pdesc->Name, &desc);
        ok(hr == S_OK, "GetResourceBindingDescByName(%u) failed, got %x, expected %x\n", i, hr, S_OK);

        ok(!strcmp(desc.Name, pdesc->Name), "GetResourceBindingDescByName(%u) Name failed, got \"%s\", expected \"%s\"\n",
                i, desc.Name, pdesc->Name);
        ok(desc.Type == pdesc->Type, "GetResourceBindingDescByName(%u) Type failed, got %x, expected %x\n",
                i, desc.Type, pdesc->Type);
        ok(desc.BindPoint == pdesc->BindPoint, "GetResourceBindingDescByName(%u) BindPoint failed, got %u, expected %u\n",
                i, desc.BindPoint, pdesc->BindPoint);
        ok(desc.BindCount == pdesc->BindCount, "GetResourceBindingDescByName(%u) BindCount failed, got %u, expected %u\n",
                i, desc.BindCount, pdesc->BindCount);
        ok(desc.uFlags == pdesc->uFlags, "GetResourceBindingDescByName(%u) uFlags failed, got %u, expected %u\n",
                i, desc.uFlags, pdesc->uFlags);
        ok(desc.ReturnType == pdesc->ReturnType, "GetResourceBindingDescByName(%u) ReturnType failed, got %x, expected %x\n",
                i, desc.ReturnType, pdesc->ReturnType);
        ok(desc.Dimension == pdesc->Dimension, "GetResourceBindingDescByName(%u) Dimension failed, got %x, expected %x\n",
                i, desc.Dimension, pdesc->Dimension);
        ok(desc.NumSamples == pdesc->NumSamples, "GetResourceBindingDescByName(%u) NumSamples failed, got %u, expected %u\n",
                i, desc.NumSamples, pdesc->NumSamples);
    }

    count = ref11->lpVtbl->Release(ref11);
    ok(count == 0, "Release failed %u\n", count);
}