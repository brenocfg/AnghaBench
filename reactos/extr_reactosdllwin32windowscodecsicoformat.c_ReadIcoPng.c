#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ WICRect ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/ * bits; int /*<<< orphan*/  dpiY; int /*<<< orphan*/  dpiX; } ;
typedef  TYPE_2__ IcoFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmapFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_IWICBitmapDecoder ; 
 int /*<<< orphan*/  IWICBitmapDecoder_GetFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetResolution (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ *,TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PngDecoder_CreateInstance (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  WICConvertBitmapSource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WICDecodeMetadataCacheOnLoad ; 

__attribute__((used)) static HRESULT ReadIcoPng(IStream *stream, IcoFrameDecode *result)
{
    IWICBitmapDecoder *decoder = NULL;
    IWICBitmapFrameDecode *sourceFrame = NULL;
    IWICBitmapSource *sourceBitmap = NULL;
    WICRect rect;
    HRESULT hr;

    hr = PngDecoder_CreateInstance(&IID_IWICBitmapDecoder, (void**)&decoder);
    if (FAILED(hr))
        goto end;
    hr = IWICBitmapDecoder_Initialize(decoder, stream, WICDecodeMetadataCacheOnLoad);
    if (FAILED(hr))
        goto end;
    hr = IWICBitmapDecoder_GetFrame(decoder, 0, &sourceFrame);
    if (FAILED(hr))
        goto end;
    hr = WICConvertBitmapSource(&GUID_WICPixelFormat32bppBGRA, (IWICBitmapSource*)sourceFrame, &sourceBitmap);
    if (FAILED(hr))
        goto end;
    hr = IWICBitmapFrameDecode_GetSize(sourceFrame, &result->width, &result->height);
    if (FAILED(hr))
        goto end;
    hr = IWICBitmapFrameDecode_GetResolution(sourceFrame, &result->dpiX, &result->dpiY);
    if (FAILED(hr))
        goto end;
    result->bits = HeapAlloc(GetProcessHeap(), 0, 4 * result->width * result->height);
    if (result->bits == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto end;
    }
    rect.X = 0;
    rect.Y = 0;
    rect.Width = result->width;
    rect.Height = result->height;
    hr = IWICBitmapSource_CopyPixels(sourceBitmap, &rect, 4*result->width,
                                     4*result->width*result->height, result->bits);

end:
    if (decoder != NULL)
        IWICBitmapDecoder_Release(decoder);
    if (sourceFrame != NULL)
        IWICBitmapFrameDecode_Release(sourceFrame);
    if (sourceBitmap != NULL)
        IWICBitmapSource_Release(sourceBitmap);
    return hr;
}