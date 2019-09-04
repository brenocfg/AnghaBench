#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct FormatConverter {int /*<<< orphan*/  source; } ;
typedef  enum pixelformat { ____Placeholder_pixelformat } pixelformat ;
struct TYPE_5__ {int Width; int Height; } ;
typedef  TYPE_1__ WICRect ;
typedef  int UINT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  float BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 float* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ ,TYPE_1__ const*,int,int,float*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  copypixels_to_24bppBGR (struct FormatConverter*,TYPE_1__ const*,int,int,float*,int) ; 
 scalar_t__ floorf (float) ; 
 int format_32bppGrayFloat ; 
 int format_8bppGray ; 
 float to_sRGB_component (float) ; 

__attribute__((used)) static HRESULT copypixels_to_8bppGray(struct FormatConverter *This, const WICRect *prc,
    UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer, enum pixelformat source_format)
{
    HRESULT hr;
    BYTE *srcdata;
    UINT srcstride, srcdatasize;

    if (source_format == format_8bppGray)
    {
        if (prc)
            return IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);

        return S_OK;
    }

    if (source_format == format_32bppGrayFloat)
    {
        hr = S_OK;

        if (prc)
        {
            srcstride = 4 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            hr = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);
            if (SUCCEEDED(hr))
            {
                INT x, y;
                BYTE *src = srcdata, *dst = pbBuffer;

                for (y=0; y < prc->Height; y++)
                {
                    float *srcpixel = (float*)src;
                    BYTE *dstpixel = dst;

                    for (x=0; x < prc->Width; x++)
                        *dstpixel++ = (BYTE)floorf(to_sRGB_component(*srcpixel++) * 255.0f + 0.51f);

                    src += srcstride;
                    dst += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);
        }

        return hr;
    }

    srcstride = 3 * prc->Width;
    srcdatasize = srcstride * prc->Height;

    srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
    if (!srcdata) return E_OUTOFMEMORY;

    hr = copypixels_to_24bppBGR(This, prc, srcstride, srcdatasize, srcdata, source_format);
    if (SUCCEEDED(hr) && prc)
    {
        INT x, y;
        BYTE *src = srcdata, *dst = pbBuffer;

        for (y = 0; y < prc->Height; y++)
        {
            BYTE *bgr = src;

            for (x = 0; x < prc->Width; x++)
            {
                float gray = (bgr[2] * 0.2126f + bgr[1] * 0.7152f + bgr[0] * 0.0722f) / 255.0f;

                gray = to_sRGB_component(gray) * 255.0f;
                dst[x] = (BYTE)floorf(gray + 0.51f);
                bgr += 3;
            }
            src += srcstride;
            dst += cbStride;
        }
    }

    HeapFree(GetProcessHeap(), 0, srcdata);
    return hr;
}