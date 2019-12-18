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
struct bitmap_data {int dummy; } ;
typedef  int /*<<< orphan*/  colors ;
typedef  int WICColor ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IWICPalette_InitializeCustom (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_multi_encoder (struct bitmap_data const**,int /*<<< orphan*/  const*,struct bitmap_data const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_encoder(const struct bitmap_data *src, const CLSID* clsid_encoder,
    const struct bitmap_data *dst, const CLSID *clsid_decoder, const char *name)
{
    const struct bitmap_data *srcs[2];
    const struct bitmap_data *dsts[2];
    WICColor colors[256];
    IWICPalette *palette;
    HRESULT hr;

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "CreatePalette error %#x\n", hr);

    memset(colors, 0, sizeof(colors));
    colors[0] = 0x11111111;
    colors[1] = 0x22222222;
    colors[2] = 0x33333333;
    colors[3] = 0x44444444;
    colors[4] = 0x55555555;
    /* TIFF decoder fails to decode a 8bpp frame if palette has less than 256 colors */
    hr = IWICPalette_InitializeCustom(palette, colors, 256);
    ok(hr == S_OK, "InitializeCustom error %#x\n", hr);

    srcs[0] = src;
    srcs[1] = NULL;
    dsts[0] = dst;
    dsts[1] = NULL;

    test_multi_encoder(srcs, clsid_encoder, dsts, clsid_decoder, NULL, NULL, name, palette);

    IWICPalette_Release(palette);
}