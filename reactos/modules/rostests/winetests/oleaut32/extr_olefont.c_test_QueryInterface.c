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
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IFont ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_POINTER ; 
 int IFont_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFont_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFont ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pOleCreateFontIndirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_QueryInterface(void)
{
    LPVOID pvObj = NULL;
    HRESULT hr;
    IFont*  font = NULL;
    LONG ref;

    hr = pOleCreateFontIndirect(NULL, &IID_IFont, NULL);
    EXPECT_HR(hr, E_POINTER);

    hr = pOleCreateFontIndirect(NULL, &IID_IFont, &pvObj);
    font = pvObj;

    EXPECT_HR(hr, S_OK);
    ok(font != NULL,"OCFI (NULL,..) returns NULL, instead of !NULL\n");

    pvObj = NULL;
    hr = IFont_QueryInterface( font, &IID_IFont, &pvObj);
    EXPECT_HR(hr, S_OK);

    /* Test if QueryInterface increments ref counter for IFONTs */
    ref = IFont_AddRef(font);
    ok(ref == 3 ||
       broken(ref == 1), /* win95 */
           "IFont_QI expected ref value 3 but instead got %d\n", ref);
    IFont_Release(font);

    ok(pvObj != NULL,"IFont_QI does return NULL, instead of a ptr\n");

    IFont_Release(font);
    IFont_Release(font);
}