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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateIcon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_window () ; 
 int /*<<< orphan*/  empty_bits ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  icon_bits ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/ * pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pImageList_Merge (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ pImageList_ReplaceIcon (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_merge(void)
{
    HIMAGELIST himl1, himl2, hmerge;
    HICON hicon1;
    HWND hwnd = create_window();

    himl1 = pImageList_Create(32, 32, 0, 0, 3);
    ok(himl1 != NULL,"failed to create himl1\n");

    himl2 = pImageList_Create(32, 32, 0, 0, 3);
    ok(himl2 != NULL,"failed to create himl2\n");

    hicon1 = CreateIcon(hinst, 32, 32, 1, 1, icon_bits, icon_bits);
    ok(hicon1 != NULL, "failed to create hicon1\n");

    if (!himl1 || !himl2 || !hicon1)
        return;

    ok(0 == pImageList_ReplaceIcon(himl2, -1, hicon1), "Failed to add icon1 to himl2.\n");
    check_bits(hwnd, himl2, 0, 32, icon_bits, "add icon1 to himl2");

    /* If himl1 has no images, merge still succeeds */
    hmerge = pImageList_Merge(himl1, -1, himl2, 0, 0, 0);
    ok(hmerge != NULL, "merge himl1,-1 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl1,-1");
    pImageList_Destroy(hmerge);

    hmerge = pImageList_Merge(himl1, 0, himl2, 0, 0, 0);
    ok(hmerge != NULL,"merge himl1,0 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl1,0");
    pImageList_Destroy(hmerge);

    /* Same happens if himl2 is empty */
    pImageList_Destroy(himl2);
    himl2 = pImageList_Create(32, 32, 0, 0, 3);
    ok(himl2 != NULL,"failed to recreate himl2\n");
    if (!himl2)
        return;

    hmerge = pImageList_Merge(himl1, -1, himl2, -1, 0, 0);
    ok(hmerge != NULL, "merge himl2,-1 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl2,-1");
    pImageList_Destroy(hmerge);

    hmerge = pImageList_Merge(himl1, -1, himl2, 0, 0, 0);
    ok(hmerge != NULL, "merge himl2,0 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl2,0");
    pImageList_Destroy(hmerge);

    /* Now try merging an image with itself */
    ok(0 == pImageList_ReplaceIcon(himl2, -1, hicon1), "Failed to re-add icon1 to himl2.\n");

    hmerge = pImageList_Merge(himl2, 0, himl2, 0, 0, 0);
    ok(hmerge != NULL, "merge himl2 with itself failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl2 with itself");
    pImageList_Destroy(hmerge);

    /* Try merging 2 different image lists */
    ok(0 == pImageList_ReplaceIcon(himl1, -1, hicon1), "Failed to add icon1 to himl1.\n");

    hmerge = pImageList_Merge(himl1, 0, himl2, 0, 0, 0);
    ok(hmerge != NULL, "merge himl1 with himl2 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl1 with himl2");
    pImageList_Destroy(hmerge);

    hmerge = pImageList_Merge(himl1, 0, himl2, 0, 8, 16);
    ok(hmerge != NULL, "merge himl1 with himl2 8,16 failed\n");
    check_bits(hwnd, hmerge, 0, 32, empty_bits, "merge himl1 with himl2, 8,16");
    pImageList_Destroy(hmerge);

    pImageList_Destroy(himl1);
    pImageList_Destroy(himl2);
    DestroyIcon(hicon1);
    DestroyWindow(hwnd);
}