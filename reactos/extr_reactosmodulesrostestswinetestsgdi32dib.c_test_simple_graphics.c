#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ds ;
typedef  int /*<<< orphan*/  bmibuf ;
struct TYPE_12__ {int biSize; int biHeight; int biWidth; int biBitCount; int biPlanes; int biClrUsed; void* biCompression; } ;
struct TYPE_15__ {TYPE_2__ bmiHeader; TYPE_3__* bmiColors; } ;
struct TYPE_11__ {void* biCompression; } ;
struct TYPE_14__ {int* dsBitfields; TYPE_1__ dsBmih; } ;
struct TYPE_13__ {int rgbRed; int rgbGreen; int rgbBlue; } ;
typedef  TYPE_3__ RGBQUAD ;
typedef  int /*<<< orphan*/ * HPALETTE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_4__ DIBSECTION ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_5__ BITMAPINFO ;

/* Variables and functions */
 void* BI_BITFIELDS ; 
 void* BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectPalette (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_default_palette (int) ; 
 int /*<<< orphan*/  current_sha1 ; 
 int /*<<< orphan*/  draw_graphics (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 char* dst_format ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sha1_graphics_1 ; 
 int /*<<< orphan*/  sha1_graphics_24 ; 
 int /*<<< orphan*/  sha1_graphics_4 ; 
 int /*<<< orphan*/  sha1_graphics_4_grayscale ; 
 int /*<<< orphan*/  sha1_graphics_8 ; 
 int /*<<< orphan*/  sha1_graphics_8_color ; 
 int /*<<< orphan*/  sha1_graphics_8_grayscale ; 
 int /*<<< orphan*/  sha1_graphics_a8b8g8r8 ; 
 int /*<<< orphan*/  sha1_graphics_a8r8g8b8 ; 
 int /*<<< orphan*/  sha1_graphics_a8r8g8b8_bitfields ; 
 int /*<<< orphan*/  sha1_graphics_r10g10b10 ; 
 int /*<<< orphan*/  sha1_graphics_r4g4b4 ; 
 int /*<<< orphan*/  sha1_graphics_r5g5b5 ; 
 int /*<<< orphan*/  sha1_graphics_r6g6b6 ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_simple_graphics(void)
{
    char bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    BITMAPINFO *bmi = (BITMAPINFO *)bmibuf;
    RGBQUAD *colors = bmi->bmiColors;
    DWORD *bit_fields = (DWORD*)(bmibuf + sizeof(BITMAPINFOHEADER));
    HDC mem_dc;
    BYTE *bits;
    HBITMAP dib, orig_bm;
    DIBSECTION ds;
    HPALETTE default_palette, old_hpal;
    int i;

    mem_dc = CreateCompatibleDC(NULL);

    /* a8r8g8b8 */
    trace("8888\n");
    memset(bmi, 0, sizeof(bmibuf));
    bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
    bmi->bmiHeader.biHeight = 512;
    bmi->bmiHeader.biWidth = 512;
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biCompression = BI_RGB;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_RGB, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    default_palette = create_default_palette( 8 );
    old_hpal = SelectPalette( mem_dc, default_palette, FALSE );

    dst_format = "8888";
    current_sha1 = sha1_graphics_a8r8g8b8;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* a8r8g8b8 - bitfields.  Should be the same as the regular 32 bit case.*/
    trace("8888 - bitfields\n");
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_BITFIELDS;
    bit_fields[0] = 0xff0000;
    bit_fields[1] = 0x00ff00;
    bit_fields[2] = 0x0000ff;

    dib = CreateDIBSection(mem_dc, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0xff0000, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x00ff00, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0x0000ff, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);
    SelectPalette( mem_dc, default_palette, FALSE );

    dst_format = "8888 - bitfields";
    current_sha1 = sha1_graphics_a8r8g8b8_bitfields;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* a8b8g8r8. */
    trace("a8b8g8r8\n");
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_BITFIELDS;
    bit_fields[0] = 0x0000ff;
    bit_fields[1] = 0x00ff00;
    bit_fields[2] = 0xff0000;

    dib = CreateDIBSection(mem_dc, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0x0000ff, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x00ff00, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0xff0000, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "a8b8g8r8";
    current_sha1 = sha1_graphics_a8b8g8r8;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* r10g10b10. */
    trace("r10g10b10\n");
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_BITFIELDS;
    bit_fields[0] = 0x3ff00000;
    bit_fields[1] = 0x000ffc00;
    bit_fields[2] = 0x000003ff;

    dib = CreateDIBSection(mem_dc, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0x3ff00000, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x000ffc00, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0x000003ff, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "r10g10b10";
    current_sha1 = sha1_graphics_r10g10b10;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* r6g6b6. */
    trace("r6g6b6\n");
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_BITFIELDS;
    bit_fields[0] = 0x0003f000;
    bit_fields[1] = 0x00000fc0;
    bit_fields[2] = 0x0000003f;

    dib = CreateDIBSection(mem_dc, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0x0003f000, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x00000fc0, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0x0000003f, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "r6g6b6";
    current_sha1 = sha1_graphics_r6g6b6;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 24 */
    trace("24\n");
    bmi->bmiHeader.biBitCount = 24;
    bmi->bmiHeader.biCompression = BI_RGB;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "24";
    current_sha1 = sha1_graphics_24;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* r5g5b5 */
    trace("555\n");
    bmi->bmiHeader.biBitCount = 16;
    bmi->bmiHeader.biCompression = BI_RGB;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0x7c00, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x03e0, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0x001f, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "r5g5b5";
    current_sha1 = sha1_graphics_r5g5b5;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* r4g4b4 */
    trace("444\n");
    bmi->bmiHeader.biBitCount = 16;
    bmi->bmiHeader.biCompression = BI_BITFIELDS;
    bit_fields[0] = 0x0f00;
    bit_fields[1] = 0x00f0;
    bit_fields[2] = 0x000f;
    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");
    ok(GetObjectW( dib, sizeof(ds), &ds ), "GetObject failed\n");
    ok(ds.dsBitfields[0] == 0x0f00, "got %08x\n", ds.dsBitfields[0]);
    ok(ds.dsBitfields[1] == 0x00f0, "got %08x\n", ds.dsBitfields[1]);
    ok(ds.dsBitfields[2] == 0x000f, "got %08x\n", ds.dsBitfields[2]);
    ok(ds.dsBmih.biCompression == BI_BITFIELDS, "got %x\n", ds.dsBmih.biCompression);

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "r4g4b4";
    current_sha1 = sha1_graphics_r4g4b4;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 8 color */
    trace("8 color\n");
    bmi->bmiHeader.biBitCount = 8;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biClrUsed = 236;
    for (i = 0; i < 236; i++)
    {
        colors[i].rgbRed   = (i & 0x07) << 5;
        colors[i].rgbGreen = (i & 0x38) << 2;
        colors[i].rgbBlue  =  i & 0xc0;
    }
    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "8 color";
    current_sha1 = sha1_graphics_8_color;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 8 grayscale */
    trace("8 grayscale\n");
    bmi->bmiHeader.biBitCount = 8;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biClrUsed = 256;
    for (i = 0; i < 256; i++) colors[i].rgbRed = colors[i].rgbGreen = colors[i].rgbBlue = i;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "8 grayscale";
    current_sha1 = sha1_graphics_8_grayscale;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 8 */
    trace("8\n");
    bmi->bmiHeader.biBitCount = 8;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biClrUsed = 5;
    colors[0].rgbRed = 0xff;
    colors[0].rgbGreen = 0xff;
    colors[0].rgbBlue = 0xff;
    colors[1].rgbRed = 0;
    colors[1].rgbGreen = 0;
    colors[1].rgbBlue = 0;
    colors[2].rgbRed = 0xff;
    colors[2].rgbGreen = 0;
    colors[2].rgbBlue = 0;
    colors[3].rgbRed = 0;
    colors[3].rgbGreen = 0xff;
    colors[3].rgbBlue = 0;
    colors[4].rgbRed = 0;
    colors[4].rgbGreen = 0;
    colors[4].rgbBlue = 0xff;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "8";
    current_sha1 = sha1_graphics_8;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 4 */
    trace("4\n");
    bmi->bmiHeader.biBitCount = 4;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);
    DeleteObject( SelectPalette( mem_dc, create_default_palette(4), FALSE ));

    dst_format = "4";
    current_sha1 = sha1_graphics_4;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 4 grayscale */
    trace("4 grayscale\n");
    bmi->bmiHeader.biClrUsed = 16;
    for (i = 0; i < 16; i++) colors[i].rgbRed = colors[i].rgbGreen = colors[i].rgbBlue = i * 17;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);

    dst_format = "4 grayscale";
    current_sha1 = sha1_graphics_4_grayscale;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    /* 1 */
    trace("1\n");
    bmi->bmiHeader.biBitCount = 1;
    bmi->bmiHeader.biClrUsed = 2;

    colors[0].rgbRed = 0x00;
    colors[0].rgbGreen = 0x01;
    colors[0].rgbBlue = 0xff;
    colors[1].rgbRed = 0xff;
    colors[1].rgbGreen = 0x00;
    colors[1].rgbBlue = 0x00;

    dib = CreateDIBSection(0, bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(dib != NULL, "ret NULL\n");

    orig_bm = SelectObject(mem_dc, dib);
    DeleteObject( SelectPalette( mem_dc, create_default_palette(1), FALSE ));

    dst_format = "1";
    current_sha1 = sha1_graphics_1;
    draw_graphics(mem_dc, bmi, bits);
    draw_text(mem_dc, bmi, bits);

    DeleteObject( SelectPalette( mem_dc, old_hpal, FALSE ));
    SelectObject(mem_dc, orig_bm);
    DeleteObject(dib);

    DeleteDC(mem_dc);
}