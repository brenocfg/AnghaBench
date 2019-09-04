#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  desc ;
struct TYPE_3__ {int cbSizeofstruct; short picType; } ;
typedef  TYPE_1__ PICTDESC ;
typedef  int OLE_HANDLE ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PALETTE ; 
 int E_FAIL ; 
 int E_UNEXPECTED ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HandleToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 int IPicture_get_Handle (int /*<<< orphan*/ *,int*) ; 
 int IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 int IPicture_get_hPal (int /*<<< orphan*/ *,int*) ; 
 int IPicture_set_hPal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OleCreatePictureIndirect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 short PICTYPE_BITMAP ; 
 short PICTYPE_ENHMETAFILE ; 
 short PICTYPE_NONE ; 
 short PICTYPE_UNINITIALIZED ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int create_picture (short,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,short,...) ; 

__attribute__((used)) static void test_OleCreatePictureIndirect(void)
{
    PICTDESC desc;
    OLE_HANDLE handle;
    IPicture *pict;
    HRESULT hr;
    short type, i;

if (0)
{
    /* crashes on native */
    OleCreatePictureIndirect(NULL, &IID_IPicture, TRUE, NULL);
}

    desc.cbSizeofstruct = sizeof(desc);
    desc.picType = PICTYPE_UNINITIALIZED;
    pict = (void *)0xdeadbeef;
    hr = OleCreatePictureIndirect(&desc, &IID_IPicture, TRUE, (void **)&pict);
    ok(hr == E_UNEXPECTED, "got %#x\n", hr);
    ok(pict == NULL, "got %p\n", pict);

    for (i = PICTYPE_UNINITIALIZED; i <= PICTYPE_ENHMETAFILE; i++)
    {
        hr = create_picture(i, &pict);
        ok(hr == S_OK, "%d: got %#x\n", i, hr);

        type = 0xdead;
        hr = IPicture_get_Type(pict, &type);
        ok(hr == S_OK, "%d: got %#x\n", i, hr);
        ok(type == i, "%d: got %d\n", i, type);

        handle = 0xdeadbeef;
        hr = IPicture_get_Handle(pict, &handle);
        ok(hr == S_OK, "%d: got %#x\n", i, hr);
        if (type == PICTYPE_UNINITIALIZED || type == PICTYPE_NONE)
            ok(handle == 0, "%d: got %#x\n", i, handle);
        else
            ok(handle != 0 && handle != 0xdeadbeef, "%d: got %#x\n", i, handle);

        handle = 0xdeadbeef;
        hr = IPicture_get_hPal(pict, &handle);
        if (type == PICTYPE_BITMAP)
        {
            ok(hr == S_OK, "%d: got %#x\n", i, hr);
            ok(handle == 0xbeefdead, "%d: got %#x\n", i, handle);
        }
        else
        {
            ok(hr == E_FAIL, "%d: got %#x\n", i, hr);
            ok(handle == 0xdeadbeef || handle == 0 /* win64 */, "%d: got %#x\n", i, handle);
        }

        hr = IPicture_set_hPal(pict, HandleToUlong(GetStockObject(DEFAULT_PALETTE)));
        if (type == PICTYPE_BITMAP)
            ok(hr == S_OK, "%d: got %#x\n", i, hr);
        else
            ok(hr == E_FAIL, "%d: got %#x\n", i, hr);

        IPicture_Release(pict);
    }
}