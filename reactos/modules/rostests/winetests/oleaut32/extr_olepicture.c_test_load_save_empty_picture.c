#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pic ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
struct TYPE_5__ {int cbSizeofstruct; short picType; } ;
typedef  TYPE_1__ PICTDESC ;
typedef  short OLE_HANDLE ;
typedef  int LONG ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  int /*<<< orphan*/  IPersistStream ;
typedef  short HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  short DWORD ;

/* Variables and functions */
 short CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GMEM_ZEROINIT ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 short* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPersistStream_Release (int /*<<< orphan*/ *) ; 
 short IPersistStream_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 short IPicture_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 short IPicture_SaveAsFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 short IPicture_get_Handle (int /*<<< orphan*/ *,short*) ; 
 short IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 short IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NoStatStream_Construct (int /*<<< orphan*/ ) ; 
 short OleCreatePictureIndirect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 short PICTYPE_NONE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 short S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcmp (short*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 short pOleLoadPicture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void test_load_save_empty_picture(void)
{
    IPicture *pic;
    PICTDESC desc;
    short type;
    OLE_HANDLE handle;
    HGLOBAL hmem;
    DWORD *mem;
    IPersistStream *src_stream;
    IStream *dst_stream, *stream;
    LARGE_INTEGER offset;
    HRESULT hr;
    LONG size;

    memset(&pic, 0, sizeof(pic));
    desc.cbSizeofstruct = sizeof(desc);
    desc.picType = PICTYPE_NONE;
    hr = OleCreatePictureIndirect(&desc, &IID_IPicture, FALSE, (void **)&pic);
    ok(hr == S_OK, "OleCreatePictureIndirect error %#x\n", hr);

    type = -1;
    hr = IPicture_get_Type(pic, &type);
    ok(hr == S_OK, "get_Type error %#x\n", hr);
    ok(type == PICTYPE_NONE,"expected picture type PICTYPE_NONE, got %d\n", type);

    handle = (OLE_HANDLE)0xdeadbeef;
    hr = IPicture_get_Handle(pic, &handle);
    ok(hr == S_OK,"get_Handle error %#8x\n", hr);
    ok(!handle, "get_Handle returned wrong handle %#x\n", handle);

    hmem = GlobalAlloc(GMEM_ZEROINIT, 4096);
    hr = CreateStreamOnHGlobal(hmem, FALSE, &dst_stream);
    ok(hr == S_OK, "createstreamonhglobal error %#x\n", hr);

    size = -1;
    hr = IPicture_SaveAsFile(pic, dst_stream, TRUE, &size);
    ok(hr == S_OK, "IPicture_SaveasFile error %#x\n", hr);
    ok(size == -1, "expected -1, got %d\n", size);

    size = -1;
    hr = IPicture_SaveAsFile(pic, dst_stream, FALSE, &size);
    ok(hr == S_OK, "IPicture_SaveasFile error %#x\n", hr);
    ok(size == -1, "expected -1, got %d\n", size);

    hr = IPicture_QueryInterface(pic, &IID_IPersistStream, (void **)&src_stream);
    ok(hr == S_OK, "QueryInterface error %#x\n", hr);

    hr = IPersistStream_Save(src_stream, dst_stream, TRUE);
    ok(hr == S_OK, "Save error %#x\n", hr);

    mem = GlobalLock(hmem);
    ok(!memcmp(mem, "lt\0\0", 4), "got wrong stream header %04x\n", mem[0]);
    ok(mem[1] == 0, "expected stream size 0, got %u\n", mem[1]);
    GlobalUnlock(hmem);

    IPersistStream_Release(src_stream);
    IPicture_Release(pic);

    /* first with statable and seekable stream */
    offset.QuadPart = 0;
    hr = IStream_Seek(dst_stream, offset, SEEK_SET, NULL);
    ok(hr == S_OK, "IStream_Seek %#x\n", hr);

    pic = NULL;
    hr = pOleLoadPicture(dst_stream, 0, FALSE, &IID_IPicture, (void **)&pic);
    ok(hr == S_OK, "OleLoadPicture error %#x\n", hr);
    ok(pic != NULL,"picture should not be not NULL\n");
    if (pic != NULL)
    {
        type = -1;
        hr = IPicture_get_Type(pic, &type);
        ok(hr == S_OK,"get_Type error %#8x\n", hr);
        ok(type == PICTYPE_NONE,"expected picture type PICTYPE_NONE, got %d\n", type);

        handle = (OLE_HANDLE)0xdeadbeef;
        hr = IPicture_get_Handle(pic, &handle);
        ok(hr == S_OK,"get_Handle error %#8x\n", hr);
        ok(!handle, "get_Handle returned wrong handle %#x\n", handle);

        IPicture_Release(pic);
    }
    IStream_Release(dst_stream);

    /* again with non-statable and non-seekable stream */
    stream = NoStatStream_Construct(hmem);
    ok(stream != NULL, "failed to create empty image stream\n");

    pic = NULL;
    hr = pOleLoadPicture(stream, 0, FALSE, &IID_IPicture, (void **)&pic);
    ok(hr == S_OK, "OleLoadPicture error %#x\n", hr);
    ok(pic != NULL,"picture should not be not NULL\n");
    if (pic != NULL)
    {
        type = -1;
        hr = IPicture_get_Type(pic, &type);
        ok(hr == S_OK,"get_Type error %#8x\n", hr);
        ok(type == PICTYPE_NONE,"expected picture type PICTYPE_NONE, got %d\n", type);

        handle = (OLE_HANDLE)0xdeadbeef;
        hr = IPicture_get_Handle(pic, &handle);
        ok(hr == S_OK,"get_Handle error %#8x\n", hr);
        ok(!handle, "get_Handle returned wrong handle %#x\n", handle);

        IPicture_Release(pic);
    }
    /* Non-statable impl always deletes on release */
    IStream_Release(stream);
}