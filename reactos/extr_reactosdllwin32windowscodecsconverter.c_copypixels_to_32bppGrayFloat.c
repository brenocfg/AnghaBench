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
struct TYPE_5__ {scalar_t__ Height; scalar_t__ Width; } ;
typedef  TYPE_1__ WICRect ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  float BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  copypixels_to_32bppBGRA (struct FormatConverter*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int) ; 
#define  format_32bppBGR 131 
#define  format_32bppBGRA 130 
#define  format_32bppGrayFloat 129 
#define  format_32bppPBGRA 128 

__attribute__((used)) static HRESULT copypixels_to_32bppGrayFloat(struct FormatConverter *This, const WICRect *prc,
    UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer, enum pixelformat source_format)
{
    HRESULT hr;

    switch (source_format)
    {
    case format_32bppBGR:
    case format_32bppBGRA:
    case format_32bppPBGRA:
    case format_32bppGrayFloat:
        if (prc)
        {
            hr = IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
            break;
        }
        return S_OK;

    default:
        hr = copypixels_to_32bppBGRA(This, prc, cbStride, cbBufferSize, pbBuffer, source_format);
        break;
    }

    if (SUCCEEDED(hr) && prc && source_format != format_32bppGrayFloat)
    {
        INT x, y;
        BYTE *p = pbBuffer;

        for (y = 0; y < prc->Height; y++)
        {
            BYTE *bgr = p;
            for (x = 0; x < prc->Width; x++)
            {
                float gray = (bgr[2] * 0.2126f + bgr[1] * 0.7152f + bgr[0] * 0.0722f) / 255.0f;
                *(float *)bgr = gray;
                bgr += 4;
            }
            p += cbStride;
        }
    }
    return hr;
}