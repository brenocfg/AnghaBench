#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bih ;
typedef  int /*<<< orphan*/  bfh ;
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
struct TYPE_4__ {int bfType; int bfReserved1; int bfReserved2; int bfOffBits; int bV5Width; int bV5Height; int bV5Planes; int bV5BitCount; int bV5ClrUsed; int bV5ClrImportant; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;
typedef  TYPE_1__ BITMAPV5HEADER ;
typedef  TYPE_1__ BITMAPFILEHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_WICPixelFormat1bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat4bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppIndexed ; 
 int IStream_Read (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void check_bmp_format(IStream *stream, const WICPixelFormatGUID *format)
{
    HRESULT hr;
    BITMAPFILEHEADER bfh;
    BITMAPV5HEADER bih;

    hr = IStream_Read(stream, &bfh, sizeof(bfh), NULL);
    ok(hr == S_OK, "IStream_Read error %#x\n", hr);

    ok(bfh.bfType == 0x4d42, "wrong BMP signature %02x\n", bfh.bfType);
    ok(bfh.bfReserved1 == 0, "wrong bfReserved1 %02x\n", bfh.bfReserved1);
    ok(bfh.bfReserved2 == 0, "wrong bfReserved2 %02x\n", bfh.bfReserved2);

    hr = IStream_Read(stream, &bih, sizeof(bih), NULL);
    ok(hr == S_OK, "IStream_Read error %#x\n", hr);

    if (IsEqualGUID(format, &GUID_WICPixelFormat1bppIndexed))
    {
        ok(bfh.bfOffBits == 0x0436, "wrong bfOffBits %08x\n", bfh.bfOffBits);

        ok(bih.bV5Width == 32, "wrong width %u\n", bih.bV5Width);
        ok(bih.bV5Height == 2, "wrong height %u\n", bih.bV5Height);

        ok(bih.bV5Planes == 1, "wrong Planes %d\n", bih.bV5Planes);
        ok(bih.bV5BitCount == 1, "wrong BitCount %d\n", bih.bV5BitCount);
        ok(bih.bV5ClrUsed == 256, "wrong ClrUsed %d\n", bih.bV5ClrUsed);
        ok(bih.bV5ClrImportant == 256, "wrong ClrImportant %d\n", bih.bV5ClrImportant);
    }
    else if (IsEqualGUID(format, &GUID_WICPixelFormat4bppIndexed))
    {
        ok(bfh.bfOffBits == 0x0436, "wrong bfOffBits %08x\n", bfh.bfOffBits);

        ok(bih.bV5Width == 32, "wrong width %u\n", bih.bV5Width);
        ok(bih.bV5Height == 2, "wrong height %u\n", bih.bV5Height);

        ok(bih.bV5Planes == 1, "wrong Planes %d\n", bih.bV5Planes);
        ok(bih.bV5BitCount == 4, "wrong BitCount %d\n", bih.bV5BitCount);
        ok(bih.bV5ClrUsed == 256, "wrong ClrUsed %d\n", bih.bV5ClrUsed);
        ok(bih.bV5ClrImportant == 256, "wrong ClrImportant %d\n", bih.bV5ClrImportant);
    }
    else if (IsEqualGUID(format, &GUID_WICPixelFormat8bppIndexed))
    {
        ok(bfh.bfOffBits == 0x0436, "wrong bfOffBits %08x\n", bfh.bfOffBits);

        ok(bih.bV5Width == 32, "wrong width %u\n", bih.bV5Width);
        ok(bih.bV5Height == 2, "wrong height %u\n", bih.bV5Height);

        ok(bih.bV5Planes == 1, "wrong Planes %d\n", bih.bV5Planes);
        ok(bih.bV5BitCount == 8, "wrong BitCount %d\n", bih.bV5BitCount);
        ok(bih.bV5ClrUsed == 256, "wrong ClrUsed %d\n", bih.bV5ClrUsed);
        ok(bih.bV5ClrImportant == 256, "wrong ClrImportant %d\n", bih.bV5ClrImportant);
    }
    else if (IsEqualGUID(format, &GUID_WICPixelFormat32bppBGR))
    {
        ok(bfh.bfOffBits == 0x0036, "wrong bfOffBits %08x\n", bfh.bfOffBits);

        ok(bih.bV5Width == 32, "wrong width %u\n", bih.bV5Width);
        ok(bih.bV5Height == 2, "wrong height %u\n", bih.bV5Height);

        ok(bih.bV5Planes == 1, "wrong Planes %d\n", bih.bV5Planes);
        ok(bih.bV5BitCount == 32, "wrong BitCount %d\n", bih.bV5BitCount);
        ok(bih.bV5ClrUsed == 0, "wrong ClrUsed %d\n", bih.bV5ClrUsed);
        ok(bih.bV5ClrImportant == 0, "wrong ClrImportant %d\n", bih.bV5ClrImportant);
    }
    else
        ok(0, "unknown BMP pixel format %s\n", wine_dbgstr_guid(format));
}