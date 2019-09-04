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
typedef  int /*<<< orphan*/  IPicture ;
typedef  scalar_t__ HRESULT ;
typedef  short DWORD ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPicture_get_Attributes (int /*<<< orphan*/ *,short*) ; 
 scalar_t__ IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 scalar_t__ OleCreatePictureIndirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 short PICTYPE_UNINITIALIZED ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,short) ; 
 int /*<<< orphan*/  ole_expect (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_get_Attributes(void)
{
    IPicture *pic;
    HRESULT hres;
    short type;
    DWORD attr;

    hres = OleCreatePictureIndirect(NULL, &IID_IPicture, TRUE, (void **)&pic);
    ok(hres == S_OK, "Failed to create a picture, hr %#x.\n", hres);
    hres = IPicture_get_Type(pic, &type);
    ok(hres == S_OK, "IPicture_get_Type does not return S_OK, but 0x%08x\n", hres);
    ok(type == PICTYPE_UNINITIALIZED, "Expected type = PICTYPE_UNINITIALIZED, got = %d\n", type);

    hres = IPicture_get_Attributes(pic, NULL);
    ole_expect(hres, E_POINTER);

    attr = 0xdeadbeef;
    hres = IPicture_get_Attributes(pic, &attr);
    ole_expect(hres, S_OK);
    ok(attr == 0, "IPicture_get_Attributes does not reset attr to zero, got %d\n", attr);

    IPicture_Release(pic);
}