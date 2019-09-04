#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct memstream {int /*<<< orphan*/  IStream_iface; int /*<<< orphan*/  stream; } ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {int LowPart; } ;
struct TYPE_7__ {TYPE_1__ cbSize; } ;
typedef  TYPE_2__ STATSTG ;
typedef  int /*<<< orphan*/  SIZE ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  ILHEAD ;
typedef  char const* HRESULT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int BOOL ;

/* Variables and functions */
 char* GetHGlobalFromStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ILC_MASK ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* IStream_Stat (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 char const* S_OK ; 
 scalar_t__ check_bitmap_data (int /*<<< orphan*/  const*,char*,int,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  check_ilhead_data (int /*<<< orphan*/  const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cleanup_memstream (struct memstream*) ; 
 int /*<<< orphan*/  imagelist_get_bitmap_size (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_memstream (struct memstream*) ; 
 int /*<<< orphan*/  is_v6_header (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pImageList_GetIconSize (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ pImageList_GetImageCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pImageList_Read (int /*<<< orphan*/ *) ; 
 int pImageList_Write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_iml_data(HIMAGELIST himl, INT cx, INT cy, INT cur, INT max, INT grow,
        INT flags, const char *comment)
{
    INT ret, cxx, cyy, size;
    struct memstream stream;
    const ILHEAD *header;
    LARGE_INTEGER mv;
    HIMAGELIST himl2;
    HGLOBAL hglobal;
    STATSTG stat;
    char *data;
    HRESULT hr;
    SIZE bmpsize;
    BOOL b;

    ret = pImageList_GetImageCount(himl);
    ok(ret == cur, "%s: expected image count %d got %d\n", comment, cur, ret);

    ret = pImageList_GetIconSize(himl, &cxx, &cyy);
    ok(ret, "ImageList_GetIconSize failed\n");
    ok(cxx == cx, "%s: wrong cx %d (expected %d)\n", comment, cxx, cx);
    ok(cyy == cy, "%s: wrong cy %d (expected %d)\n", comment, cyy, cy);

    init_memstream(&stream);
    b = pImageList_Write(himl, &stream.IStream_iface);
    ok(b, "%s: ImageList_Write failed\n", comment);

    hr = GetHGlobalFromStream(stream.stream, &hglobal);
    ok(hr == S_OK, "%s: Failed to get hglobal, %#x\n", comment, hr);

    hr = IStream_Stat(stream.stream, &stat, STATFLAG_NONAME);
    ok(hr == S_OK, "Stat() failed, hr %#x.\n", hr);

    data = GlobalLock(hglobal);

    ok(data != 0, "%s: ImageList_Write didn't write any data\n", comment);
    ok(stat.cbSize.LowPart > sizeof(ILHEAD), "%s: ImageList_Write wrote not enough data\n", comment);

    header = (const ILHEAD *)data;
    check_ilhead_data(header, cx, cy, cur, max, grow, flags);
    imagelist_get_bitmap_size(header, &bmpsize);
    size = check_bitmap_data(header, data + sizeof(ILHEAD), stat.cbSize.LowPart - sizeof(ILHEAD),
            &bmpsize, flags & 0xfe, comment);
    if (!is_v6_header(header) && size < stat.cbSize.LowPart - sizeof(ILHEAD))  /* mask is present */
    {
        ok( flags & ILC_MASK, "%s: extra data %u/%u but mask not expected\n", comment, stat.cbSize.LowPart, size );
        check_bitmap_data(header, data + sizeof(ILHEAD) + size, stat.cbSize.LowPart - sizeof(ILHEAD) - size,
            &bmpsize, 1, comment);
    }

    /* rewind and reconstruct from stream */
    mv.QuadPart = 0;
    IStream_Seek(stream.stream, mv, STREAM_SEEK_SET, NULL);
    himl2 = pImageList_Read(&stream.IStream_iface);
    ok(himl2 != NULL, "%s: Failed to deserialize imagelist\n", comment);
    pImageList_Destroy(himl2);

    GlobalUnlock(hglobal);
    cleanup_memstream(&stream);
}