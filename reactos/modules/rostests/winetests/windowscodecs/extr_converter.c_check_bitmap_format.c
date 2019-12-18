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
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WICBmpEncoder ; 
 int /*<<< orphan*/  CLSID_WICGifEncoder ; 
 int /*<<< orphan*/  CLSID_WICPngEncoder ; 
 int /*<<< orphan*/  CLSID_WICTiffEncoder ; 
 scalar_t__ IStream_Seek (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  check_bmp_format (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  check_gif_format (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  check_png_format (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  check_tiff_format (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void check_bitmap_format(IStream *stream, const CLSID *encoder, const WICPixelFormatGUID *format)
{
    HRESULT hr;
    LARGE_INTEGER pos;

    pos.QuadPart = 0;
    hr = IStream_Seek(stream, pos, SEEK_SET, (ULARGE_INTEGER *)&pos);
    ok(hr == S_OK, "IStream_Seek error %#x\n", hr);

    if (IsEqualGUID(encoder, &CLSID_WICPngEncoder))
        check_png_format(stream, format);
    else if (IsEqualGUID(encoder, &CLSID_WICBmpEncoder))
        check_bmp_format(stream, format);
    else if (IsEqualGUID(encoder, &CLSID_WICTiffEncoder))
        check_tiff_format(stream, format);
    else if (IsEqualGUID(encoder, &CLSID_WICGifEncoder))
        check_gif_format(stream, format);
    else
        ok(0, "unknown encoder %s\n", wine_dbgstr_guid(encoder));

    hr = IStream_Seek(stream, pos, SEEK_SET, NULL);
    ok(hr == S_OK, "IStream_Seek error %#x\n", hr);
}