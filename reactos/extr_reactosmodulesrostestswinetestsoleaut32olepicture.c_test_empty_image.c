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
typedef  int /*<<< orphan*/  seekto ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
typedef  short OLE_HANDLE ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPSTREAM ;
typedef  scalar_t__ LPBYTE ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  short HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  short DWORD ;

/* Variables and functions */
 short CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 short IPicture_get_Attributes (int /*<<< orphan*/ *,short*) ; 
 short IPicture_get_Handle (int /*<<< orphan*/ *,short*) ; 
 short IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 short IStream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 short PICTYPE_NONE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 short S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 short pOleLoadPicture (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_empty_image(void) {
	LPBYTE		data;
	LPSTREAM	stream;
	IPicture*	pic = NULL;
	HRESULT		hres;
	LPVOID		pvObj = NULL;
	HGLOBAL		hglob;
	OLE_HANDLE	handle;
	ULARGE_INTEGER	newpos1;
	LARGE_INTEGER	seekto;
	short		type;
	DWORD		attr;

	/* Empty image. Happens occasionally in VB programs. */
	hglob = GlobalAlloc (0, 8);
	data = GlobalLock (hglob);
	memcpy(data,"lt\0\0",4);
	((DWORD*)data)[1] = 0;
	hres = CreateStreamOnHGlobal (hglob, TRUE, &stream);
	ok (hres == S_OK, "CreatestreamOnHGlobal failed? doubt it... hres 0x%08x\n", hres);

	memset(&seekto,0,sizeof(seekto));
	hres = IStream_Seek(stream,seekto,SEEK_CUR,&newpos1);
	ok (hres == S_OK, "istream seek failed? doubt it... hres 0x%08x\n", hres);

	pvObj = NULL;
	hres = pOleLoadPicture(stream, 8, TRUE, &IID_IPicture, &pvObj);
	pic = pvObj;
	ok(hres == S_OK,"empty picture not loaded, hres 0x%08x\n", hres);
	ok(pic != NULL,"empty picture not loaded, pic is NULL\n");

	hres = IPicture_get_Type (pic, &type);
	ok (hres == S_OK,"empty picture get type failed with hres 0x%08x\n", hres);
	ok (type == PICTYPE_NONE,"type is %d, but should be PICTYPE_NONE(0)\n", type);

	attr = 0xdeadbeef;
	hres = IPicture_get_Attributes (pic, &attr);
	ok (hres == S_OK,"empty picture get attributes failed with hres 0x%08x\n", hres);
	ok (attr == 0,"attr is %d, but should be 0\n", attr);

	hres = IPicture_get_Handle (pic, &handle);
	ok (hres == S_OK,"empty picture get handle failed with hres 0x%08x\n", hres);
	ok (handle == 0, "empty picture get handle did not return 0, but 0x%08x\n", handle);
	IPicture_Release (pic);
	IStream_Release (stream);
}