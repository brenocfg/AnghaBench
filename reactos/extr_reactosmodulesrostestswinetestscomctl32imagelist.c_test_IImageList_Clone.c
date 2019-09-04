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
typedef  int /*<<< orphan*/  IImageList ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IImageList ; 
 scalar_t__ IImageList_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IImageList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_Clone(void)
{
    IImageList *imgl, *imgl2;
    HIMAGELIST himl;
    HRESULT hr;
    ULONG ref;

    himl = pImageList_Create(16, 16, ILC_COLOR16, 0, 3);
    imgl = (IImageList*)himl;

if (0)
{
    /* crashes on native */
    IImageList_Clone(imgl, &IID_IImageList, NULL);
}

    hr = IImageList_Clone(imgl, &IID_IImageList, (void**)&imgl2);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ref = IImageList_Release(imgl2);
    ok(ref == 0, "got %u\n", ref);

    IImageList_Release(imgl);
}