#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct test_data   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WICColor ;
typedef  int WICBitmapPaletteType ;
typedef  size_t UINT ;
struct test_data {int type; int is_bw; int is_gray; size_t count; int /*<<< orphan*/ * color; int add_transparent; } ;
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int FALSE ; 
 int /*<<< orphan*/  IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICPalette_GetColorCount (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  IWICPalette_GetColors (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  IWICPalette_GetType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_InitializePredefined (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  IWICPalette_IsBlackWhite (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_IsGrayscale (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int WICBitmapPaletteTypeCustom ; 
#define  WICBitmapPaletteTypeFixedBW 138 
#define  WICBitmapPaletteTypeFixedGray16 137 
#define  WICBitmapPaletteTypeFixedGray256 136 
#define  WICBitmapPaletteTypeFixedGray4 135 
#define  WICBitmapPaletteTypeFixedHalftone125 134 
#define  WICBitmapPaletteTypeFixedHalftone216 133 
#define  WICBitmapPaletteTypeFixedHalftone252 132 
#define  WICBitmapPaletteTypeFixedHalftone256 131 
#define  WICBitmapPaletteTypeFixedHalftone27 130 
#define  WICBitmapPaletteTypeFixedHalftone64 129 
#define  WICBitmapPaletteTypeFixedHalftone8 128 
 int WICBitmapPaletteTypeMedianCut ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  generate_gray16_palette (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  generate_gray256_palette (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  generate_halftone125_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone216_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone252_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone256_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone27_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone64_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  generate_halftone8_palette (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 

__attribute__((used)) static void test_predefined_palette(void)
{
    static struct test_data
    {
        WICBitmapPaletteType type;
        BOOL is_bw, is_gray;
        UINT count;
        WICColor color[256];
        BOOL add_transparent;
    } td[] =
    {
        { WICBitmapPaletteTypeFixedBW, 1, 1, 2, { 0xff000000, 0xffffffff } },
        { WICBitmapPaletteTypeFixedBW, 1, 1, 2, { 0xff000000, 0xffffffff }, 1 },
        { WICBitmapPaletteTypeFixedGray4, 0, 1, 4,
          { 0xff000000, 0xff555555, 0xffaaaaaa, 0xffffffff } },
        { WICBitmapPaletteTypeFixedGray4, 0, 1, 4,
          { 0xff000000, 0xff555555, 0xffaaaaaa, 0xffffffff }, 1 },
        { WICBitmapPaletteTypeFixedGray16, 0, 1, 16, { 0 } },
        { WICBitmapPaletteTypeFixedGray16, 0, 1, 16, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedGray256, 0, 1, 256, { 0 } },
        { WICBitmapPaletteTypeFixedGray256, 0, 1, 256, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone8, 0, 0, 16, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone8, 0, 0, 17, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone27, 0, 0, 28, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone27, 0, 0, 29, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone64, 0, 0, 72, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone64, 0, 0, 73, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone125, 0, 0, 126, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone125, 0, 0, 127, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone216, 0, 0, 224, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone216, 0, 0, 225, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone252, 0, 0, 252, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone252, 0, 0, 253, { 0 }, 1 },
        { WICBitmapPaletteTypeFixedHalftone256, 0, 0, 256, { 0 } },
        { WICBitmapPaletteTypeFixedHalftone256, 0, 0, 256, { 0 }, 1 }
    };
    IWICPalette *palette;
    HRESULT hr;
    WICBitmapPaletteType type;
    UINT count, i, ret;
    BOOL bret;
    WICColor color[256];

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "CreatePalette error %#x\n", hr);
    hr = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeCustom, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);
    hr = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeMedianCut, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);
    hr = IWICPalette_InitializePredefined(palette, 0x0f, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);
    IWICPalette_Release(palette);

    for (i = 0; i < ARRAY_SIZE(td); i++)
    {
        hr = IWICImagingFactory_CreatePalette(factory, &palette);
        ok(hr == S_OK, "%u: CreatePalette error %#x\n", i, hr);

        hr = IWICPalette_InitializePredefined(palette, td[i].type, td[i].add_transparent);
        ok(hr == S_OK, "%u: InitializePredefined error %#x\n", i, hr);

        bret = -1;
        hr = IWICPalette_IsBlackWhite(palette, &bret);
        ok(hr == S_OK, "%u: IsBlackWhite error %#x\n", i, hr);
        ok(bret == td[i].is_bw ||
           broken(td[i].type == WICBitmapPaletteTypeFixedBW && bret != td[i].is_bw), /* XP */
           "%u: expected %d, got %d\n",i, td[i].is_bw, bret);

        bret = -1;
        hr = IWICPalette_IsGrayscale(palette, &bret);
        ok(hr == S_OK, "%u: IsGrayscale error %#x\n", i, hr);
        ok(bret == td[i].is_gray, "%u: expected %d, got %d\n", i, td[i].is_gray, bret);

        type = -1;
        hr = IWICPalette_GetType(palette, &type);
        ok(hr == S_OK, "%u: GetType error %#x\n", i, hr);
        ok(type == td[i].type, "%u: expected %#x, got %#x\n", i, td[i].type, type);

        count = 0xdeadbeef;
        hr = IWICPalette_GetColorCount(palette, &count);
        ok(hr == S_OK, "%u: GetColorCount error %#x\n", i, hr);
        ok(count == td[i].count, "%u: expected %u, got %u\n", i, td[i].count, count);

        hr = IWICPalette_GetColors(palette, count, color, &ret);
        ok(hr == S_OK, "%u: GetColors error %#x\n", i, hr);
        ok(ret == count, "%u: expected %u, got %u\n", i, count, ret);
        if (ret == td[i].count)
        {
            UINT j;

            if (td[i].type == WICBitmapPaletteTypeFixedGray16)
                generate_gray16_palette(td[i].color, td[i].count);
            else if (td[i].type == WICBitmapPaletteTypeFixedGray256)
                generate_gray256_palette(td[i].color, td[i].count);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone8)
                generate_halftone8_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone27)
                generate_halftone27_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone64)
                generate_halftone64_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone125)
                generate_halftone125_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone216)
                generate_halftone216_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone252)
                generate_halftone252_palette(td[i].color, td[i].count, td[i].add_transparent);
            else if (td[i].type == WICBitmapPaletteTypeFixedHalftone256)
                generate_halftone256_palette(td[i].color, td[i].count, td[i].add_transparent);

            for (j = 0; j < count; j++)
            {
                ok(color[j] == td[i].color[j], "%u:[%u]: expected %#x, got %#x\n",
                   i, j, td[i].color[j], color[j]);
            }
        }

        IWICPalette_Release(palette);
    }
}