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

/* Variables and functions */
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPicture_get_Type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ OleCreatePictureIndirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ole_expect (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_get_Type(void)
{
    IPicture *pic;
    HRESULT hres;

    hres = OleCreatePictureIndirect(NULL, &IID_IPicture, TRUE, (void **)&pic);
    ok(hres == S_OK, "Failed to create a picture, hr %#x.\n", hres);

    hres = IPicture_get_Type(pic, NULL);
    ole_expect(hres, E_POINTER);

    IPicture_Release(pic);
}