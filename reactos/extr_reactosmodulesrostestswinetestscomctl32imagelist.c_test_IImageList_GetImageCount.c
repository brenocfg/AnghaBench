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
typedef  int /*<<< orphan*/  IImageList ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HIMAGELIST ;

/* Variables and functions */
 scalar_t__ IImageList_GetImageCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IImageList_GetImageCount(void)
{
    IImageList *imgl;
    HIMAGELIST himl;
    int count;
    HRESULT hr;

    himl = pImageList_Create(16, 16, ILC_COLOR16, 0, 3);
    imgl = (IImageList*)himl;

if (0)
{
    /* crashes on native */
    IImageList_GetImageCount(imgl, NULL);
}

    count = -1;
    hr = IImageList_GetImageCount(imgl, &count);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(count == 0, "got %d\n", count);

    IImageList_Release(imgl);
}