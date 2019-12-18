#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  desc ;
struct TYPE_10__ {int iType; int dSignature; } ;
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {scalar_t__ hemf; } ;
struct TYPE_8__ {int cbSizeofstruct; short picType; TYPE_1__ emf; } ;
typedef  TYPE_2__ PICTDESC ;
typedef  int OLE_HANDLE ;
typedef  int LONG ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  int /*<<< orphan*/  IPersistStream ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  scalar_t__ HDC ;
typedef  TYPE_4__ ENHMETAHEADER ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CloseEnhMetaFile (scalar_t__) ; 
 scalar_t__ CreateEnhMetaFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (scalar_t__) ; 
 int EMR_HEADER ; 
 int ENHMETA_SIGNATURE ; 
 int E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPersistStream_Release (int /*<<< orphan*/ *) ; 
 int IPersistStream_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IPicture_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 int IPicture_SaveAsFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int IPicture_get_Handle (int /*<<< orphan*/ *,int*) ; 
 int IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int IStream_Seek (int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IntToPtr (int) ; 
 int OleCreatePictureIndirect (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 short PICTYPE_ENHMETAFILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_load_save_emf(void)
{
    HDC hdc;
    IPicture *pic;
    PICTDESC desc;
    short type;
    OLE_HANDLE handle;
    HGLOBAL hmem;
    DWORD *mem;
    ENHMETAHEADER *emh;
    IPersistStream *src_stream;
    IStream *dst_stream;
    LARGE_INTEGER offset;
    HRESULT hr;
    LONG size;

    hdc = CreateEnhMetaFileA(0, NULL, NULL, NULL);
    ok(hdc != 0, "CreateEnhMetaFileA failed\n");

    desc.cbSizeofstruct = sizeof(desc);
    desc.picType = PICTYPE_ENHMETAFILE;
    desc.emf.hemf = CloseEnhMetaFile(hdc);
    ok(desc.emf.hemf != 0, "CloseEnhMetaFile failed\n");
    hr = OleCreatePictureIndirect(&desc, &IID_IPicture, FALSE, (void**)&pic);
    ok(hr == S_OK, "OleCreatePictureIndirect error %#x\n", hr);

    type = -1;
    hr = IPicture_get_Type(pic, &type);
    ok(hr == S_OK,"get_Type error %#8x\n", hr);
    ok(type == PICTYPE_ENHMETAFILE,"expected PICTYPE_ENHMETAFILE, got %d\n", type);

    hr = IPicture_get_Handle(pic, &handle);
    ok(hr == S_OK,"get_Handle error %#8x\n", hr);
    ok(IntToPtr(handle) == desc.emf.hemf, "get_Handle returned wrong handle %#x\n", handle);

    hmem = GlobalAlloc(GMEM_MOVEABLE, 0);
    hr = CreateStreamOnHGlobal(hmem, FALSE, &dst_stream);
    ok(hr == S_OK, "createstreamonhglobal error %#x\n", hr);

    size = -1;
    hr = IPicture_SaveAsFile(pic, dst_stream, TRUE, &size);
    ok(hr == S_OK, "IPicture_SaveasFile error %#x\n", hr);
    ok(size == 128, "expected 128, got %d\n", size);
    emh = GlobalLock(hmem);
if (size)
{
    ok(emh->iType == EMR_HEADER, "wrong iType %04x\n", emh->iType);
    ok(emh->dSignature == ENHMETA_SIGNATURE, "wrong dSignature %08x\n", emh->dSignature);
}
    GlobalUnlock(hmem);

    size = -1;
    hr = IPicture_SaveAsFile(pic, dst_stream, FALSE, &size);
    ok(hr == E_FAIL, "expected E_FAIL, got %#x\n", hr);
    ok(size == -1, "expected -1, got %d\n", size);

    offset.QuadPart = 0;
    hr = IStream_Seek(dst_stream, offset, SEEK_SET, NULL);
    ok(hr == S_OK, "IStream_Seek %#x\n", hr);

    hr = IPicture_QueryInterface(pic, &IID_IPersistStream, (void **)&src_stream);
    ok(hr == S_OK, "QueryInterface error %#x\n", hr);

    hr = IPersistStream_Save(src_stream, dst_stream, TRUE);
    ok(hr == S_OK, "Save error %#x\n", hr);

    IPersistStream_Release(src_stream);
    IStream_Release(dst_stream);

    mem = GlobalLock(hmem);
    ok(!memcmp(mem, "lt\0\0", 4), "got wrong stream header %04x\n", mem[0]);
    ok(mem[1] == 128, "expected 128, got %u\n", mem[1]);
    emh = (ENHMETAHEADER *)(mem + 2);
    ok(emh->iType == EMR_HEADER, "wrong iType %04x\n", emh->iType);
    ok(emh->dSignature == ENHMETA_SIGNATURE, "wrong dSignature %08x\n", emh->dSignature);

    GlobalUnlock(hmem);
    GlobalFree(hmem);

    DeleteEnhMetaFile(desc.emf.hemf);
    IPicture_Release(pic);
}