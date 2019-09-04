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
struct FormatConverter {int /*<<< orphan*/  source; } ;
typedef  enum pixelformat { ____Placeholder_pixelformat } pixelformat ;
typedef  int WORD ;
struct TYPE_4__ {int Width; int Height; } ;
typedef  TYPE_1__ WICRect ;
typedef  void* WICColor ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPalette (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ ,TYPE_1__ const*,int,int,int*) ; 
 int /*<<< orphan*/  IWICPalette_GetColors (int /*<<< orphan*/ *,int,void**,int*) ; 
 int /*<<< orphan*/  IWICPalette_InitializePredefined (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PaletteImpl_Create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedBW ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedGray16 ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedGray4 ; 
 int /*<<< orphan*/  WINCODEC_ERR_UNSUPPORTEDOPERATION ; 
#define  format_16bppBGR555 147 
#define  format_16bppBGR565 146 
#define  format_16bppBGRA5551 145 
#define  format_16bppGray 144 
#define  format_1bppIndexed 143 
#define  format_24bppBGR 142 
#define  format_24bppRGB 141 
#define  format_2bppGray 140 
#define  format_2bppIndexed 139 
#define  format_32bppBGR 138 
#define  format_32bppBGRA 137 
#define  format_32bppCMYK 136 
#define  format_32bppPBGRA 135 
#define  format_48bppRGB 134 
#define  format_4bppGray 133 
#define  format_4bppIndexed 132 
#define  format_64bppRGBA 131 
#define  format_8bppGray 130 
#define  format_8bppIndexed 129 
#define  format_BlackWhite 128 

__attribute__((used)) static HRESULT copypixels_to_32bppBGRA(struct FormatConverter *This, const WICRect *prc,
    UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer, enum pixelformat source_format)
{
    switch (source_format)
    {
    case format_1bppIndexed:
    case format_BlackWhite:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;
            WICColor colors[2];
            IWICPalette *palette;
            UINT actualcolors;

            res = PaletteImpl_Create(&palette);
            if (FAILED(res)) return res;

            if (source_format == format_1bppIndexed)
                res = IWICBitmapSource_CopyPalette(This->source, palette);
            else
                res = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeFixedBW, FALSE);

            if (SUCCEEDED(res))
                res = IWICPalette_GetColors(palette, 2, colors, &actualcolors);

            IWICPalette_Release(palette);
            if (FAILED(res)) return res;

            srcstride = (prc->Width+7)/8;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x+=8) {
                        BYTE srcval;
                        srcval=*srcbyte++;
                        *dstpixel++ = colors[srcval>>7&1];
                        if (x+1 < prc->Width) *dstpixel++ = colors[srcval>>6&1];
                        if (x+2 < prc->Width) *dstpixel++ = colors[srcval>>5&1];
                        if (x+3 < prc->Width) *dstpixel++ = colors[srcval>>4&1];
                        if (x+4 < prc->Width) *dstpixel++ = colors[srcval>>3&1];
                        if (x+5 < prc->Width) *dstpixel++ = colors[srcval>>2&1];
                        if (x+6 < prc->Width) *dstpixel++ = colors[srcval>>1&1];
                        if (x+7 < prc->Width) *dstpixel++ = colors[srcval&1];
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_2bppIndexed:
    case format_2bppGray:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;
            WICColor colors[4];
            IWICPalette *palette;
            UINT actualcolors;

            res = PaletteImpl_Create(&palette);
            if (FAILED(res)) return res;

            if (source_format == format_2bppIndexed)
                res = IWICBitmapSource_CopyPalette(This->source, palette);
            else
                res = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeFixedGray4, FALSE);

            if (SUCCEEDED(res))
                res = IWICPalette_GetColors(palette, 4, colors, &actualcolors);

            IWICPalette_Release(palette);
            if (FAILED(res)) return res;

            srcstride = (prc->Width+3)/4;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x+=4) {
                        BYTE srcval;
                        srcval=*srcbyte++;
                        *dstpixel++ = colors[srcval>>6];
                        if (x+1 < prc->Width) *dstpixel++ = colors[srcval>>4&0x3];
                        if (x+2 < prc->Width) *dstpixel++ = colors[srcval>>2&0x3];
                        if (x+3 < prc->Width) *dstpixel++ = colors[srcval&0x3];
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_4bppIndexed:
    case format_4bppGray:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;
            WICColor colors[16];
            IWICPalette *palette;
            UINT actualcolors;

            res = PaletteImpl_Create(&palette);
            if (FAILED(res)) return res;

            if (source_format == format_4bppIndexed)
                res = IWICBitmapSource_CopyPalette(This->source, palette);
            else
                res = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeFixedGray16, FALSE);

            if (SUCCEEDED(res))
                res = IWICPalette_GetColors(palette, 16, colors, &actualcolors);

            IWICPalette_Release(palette);
            if (FAILED(res)) return res;

            srcstride = (prc->Width+1)/2;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x+=2) {
                        BYTE srcval;
                        srcval=*srcbyte++;
                        *dstpixel++ = colors[srcval>>4];
                        if (x+1 < prc->Width) *dstpixel++ = colors[srcval&0xf];
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_8bppGray:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++)
                    {
                        *dstpixel++ = 0xff000000|(*srcbyte<<16)|(*srcbyte<<8)|*srcbyte;
                        srcbyte++;
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_8bppIndexed:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;
            WICColor colors[256];
            IWICPalette *palette;
            UINT actualcolors;

            res = PaletteImpl_Create(&palette);
            if (FAILED(res)) return res;

            res = IWICBitmapSource_CopyPalette(This->source, palette);
            if (SUCCEEDED(res))
                res = IWICPalette_GetColors(palette, 256, colors, &actualcolors);

            IWICPalette_Release(palette);

            if (FAILED(res)) return res;

            srcstride = prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++)
                        *dstpixel++ = colors[*srcbyte++];
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_16bppGray:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcbyte;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = prc->Width * 2;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcbyte = srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++)
                    {
                        *dstpixel++ = 0xff000000|(*srcbyte<<16)|(*srcbyte<<8)|*srcbyte;
                        srcbyte+=2;
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_16bppBGR555:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const WORD *srcpixel;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = 2 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=(const WORD*)srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++) {
                        WORD srcval;
                        srcval=*srcpixel++;
                        *dstpixel++=0xff000000 | /* constant 255 alpha */
                                    ((srcval << 9) & 0xf80000) | /* r */
                                    ((srcval << 4) & 0x070000) | /* r - 3 bits */
                                    ((srcval << 6) & 0x00f800) | /* g */
                                    ((srcval << 1) & 0x000700) | /* g - 3 bits */
                                    ((srcval << 3) & 0x0000f8) | /* b */
                                    ((srcval >> 2) & 0x000007);  /* b - 3 bits */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_16bppBGR565:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const WORD *srcpixel;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = 2 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=(const WORD*)srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++) {
                        WORD srcval;
                        srcval=*srcpixel++;
                        *dstpixel++=0xff000000 | /* constant 255 alpha */
                                    ((srcval << 8) & 0xf80000) | /* r */
                                    ((srcval << 3) & 0x070000) | /* r - 3 bits */
                                    ((srcval << 5) & 0x00fc00) | /* g */
                                    ((srcval >> 1) & 0x000300) | /* g - 2 bits */
                                    ((srcval << 3) & 0x0000f8) | /* b */
                                    ((srcval >> 2) & 0x000007);  /* b - 3 bits */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_16bppBGRA5551:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const WORD *srcpixel;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = 2 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=(const WORD*)srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++) {
                        WORD srcval;
                        srcval=*srcpixel++;
                        *dstpixel++=((srcval & 0x8000) ? 0xff000000 : 0) | /* alpha */
                                    ((srcval << 9) & 0xf80000) | /* r */
                                    ((srcval << 4) & 0x070000) | /* r - 3 bits */
                                    ((srcval << 6) & 0x00f800) | /* g */
                                    ((srcval << 1) & 0x000700) | /* g - 3 bits */
                                    ((srcval << 3) & 0x0000f8) | /* b */
                                    ((srcval >> 2) & 0x000007);  /* b - 3 bits */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_24bppBGR:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcpixel;
            BYTE *dstrow;
            BYTE *dstpixel;

            srcstride = 3 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=srcrow;
                    dstpixel=dstrow;
                    for (x=0; x<prc->Width; x++) {
                        *dstpixel++=*srcpixel++; /* blue */
                        *dstpixel++=*srcpixel++; /* green */
                        *dstpixel++=*srcpixel++; /* red */
                        *dstpixel++=255; /* alpha */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_24bppRGB:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcpixel;
            BYTE *dstrow;
            BYTE *dstpixel;
            BYTE tmppixel[3];

            srcstride = 3 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=srcrow;
                    dstpixel=dstrow;
                    for (x=0; x<prc->Width; x++) {
                        tmppixel[0]=*srcpixel++; /* red */
                        tmppixel[1]=*srcpixel++; /* green */
                        tmppixel[2]=*srcpixel++; /* blue */

                        *dstpixel++=tmppixel[2]; /* blue */
                        *dstpixel++=tmppixel[1]; /* green */
                        *dstpixel++=tmppixel[0]; /* red */
                        *dstpixel++=255; /* alpha */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_32bppBGR:
        if (prc)
        {
            HRESULT res;
            INT x, y;

            res = IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
            if (FAILED(res)) return res;

            /* set all alpha values to 255 */
            for (y=0; y<prc->Height; y++)
                for (x=0; x<prc->Width; x++)
                    pbBuffer[cbStride*y+4*x+3] = 0xff;
        }
        return S_OK;
    case format_32bppBGRA:
        if (prc)
            return IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
        return S_OK;
    case format_32bppPBGRA:
        if (prc)
        {
            HRESULT res;
            INT x, y;

            res = IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
            if (FAILED(res)) return res;

            for (y=0; y<prc->Height; y++)
                for (x=0; x<prc->Width; x++)
                {
                    BYTE alpha = pbBuffer[cbStride*y+4*x+3];
                    if (alpha != 0 && alpha != 255)
                    {
                        pbBuffer[cbStride*y+4*x] = pbBuffer[cbStride*y+4*x] * 255 / alpha;
                        pbBuffer[cbStride*y+4*x+1] = pbBuffer[cbStride*y+4*x+1] * 255 / alpha;
                        pbBuffer[cbStride*y+4*x+2] = pbBuffer[cbStride*y+4*x+2] * 255 / alpha;
                    }
                }
        }
        return S_OK;
    case format_48bppRGB:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcpixel;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = 6 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++) {
                        BYTE red, green, blue;
                        red = *srcpixel++; srcpixel++;
                        green = *srcpixel++; srcpixel++;
                        blue = *srcpixel++; srcpixel++;
                        *dstpixel++=0xff000000|red<<16|green<<8|blue;
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_64bppRGBA:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcpixel;
            BYTE *dstrow;
            DWORD *dstpixel;

            srcstride = 8 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=srcrow;
                    dstpixel=(DWORD*)dstrow;
                    for (x=0; x<prc->Width; x++) {
                        BYTE red, green, blue, alpha;
                        red = *srcpixel++; srcpixel++;
                        green = *srcpixel++; srcpixel++;
                        blue = *srcpixel++; srcpixel++;
                        alpha = *srcpixel++; srcpixel++;
                        *dstpixel++=alpha<<24|red<<16|green<<8|blue;
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    case format_32bppCMYK:
        if (prc)
        {
            HRESULT res;
            UINT x, y;

            res = IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
            if (FAILED(res)) return res;

            for (y=0; y<prc->Height; y++)
                for (x=0; x<prc->Width; x++)
                {
                    BYTE *pixel = pbBuffer+cbStride*y+4*x;
                    BYTE c=pixel[0], m=pixel[1], y=pixel[2], k=pixel[3];
                    pixel[0] = (255-y)*(255-k)/255; /* blue */
                    pixel[1] = (255-m)*(255-k)/255; /* green */
                    pixel[2] = (255-c)*(255-k)/255; /* red */
                    pixel[3] = 255; /* alpha */
                }
        }
        return S_OK;
    default:
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }
}