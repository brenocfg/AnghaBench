#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ WICRect ;
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_9__ {int width; int height; int* bits; int /*<<< orphan*/  dpiY; int /*<<< orphan*/  dpiX; } ;
struct TYPE_8__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  TYPE_3__ IcoFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmapFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BmpDecoder ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BmpDecoder_FindIconMask (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  BmpDecoder_GetWICDecoder (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_GetFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetResolution (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ *,TYPE_1__*,int,int,int*) ; 
 int /*<<< orphan*/  IWICBitmapSource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IcoDibDecoder_CreateInstance (int /*<<< orphan*/ **) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WICConvertBitmapSource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WICDecodeMetadataCacheOnLoad ; 
 int /*<<< orphan*/  pixel_set_trans (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT ReadIcoDib(IStream *stream, IcoFrameDecode *result)
{
    HRESULT hr;
    BmpDecoder *bmp_decoder;
    IWICBitmapDecoder *decoder;
    IWICBitmapFrameDecode *framedecode;
    WICPixelFormatGUID pixelformat;
    IWICBitmapSource *source;
    BOOL has_alpha=FALSE; /* if TRUE, alpha data might be in the image data */
    WICRect rc;

    hr = IcoDibDecoder_CreateInstance(&bmp_decoder);
    if (SUCCEEDED(hr))
    {
        BmpDecoder_GetWICDecoder(bmp_decoder, &decoder);
        hr = IWICBitmapDecoder_Initialize(decoder, stream, WICDecodeMetadataCacheOnLoad);

        if (SUCCEEDED(hr))
            hr = IWICBitmapDecoder_GetFrame(decoder, 0, &framedecode);

        if (SUCCEEDED(hr))
        {
            hr = IWICBitmapFrameDecode_GetSize(framedecode, &result->width, &result->height);

            if (SUCCEEDED(hr))
            {
                result->bits = HeapAlloc(GetProcessHeap(), 0, result->width * result->height * 4);
                if (!result->bits) hr = E_OUTOFMEMORY;
            }

            if (SUCCEEDED(hr))
                hr = IWICBitmapFrameDecode_GetPixelFormat(framedecode, &pixelformat);

            if (IsEqualGUID(&pixelformat, &GUID_WICPixelFormat32bppBGR) ||
                IsEqualGUID(&pixelformat, &GUID_WICPixelFormat32bppBGRA))
            {
                source = (IWICBitmapSource*)framedecode;
                IWICBitmapSource_AddRef(source);
                has_alpha = TRUE;
            }
            else
            {
                hr = WICConvertBitmapSource(&GUID_WICPixelFormat32bppBGRA,
                    (IWICBitmapSource*)framedecode, &source);
                has_alpha = FALSE;
            }

            if (SUCCEEDED(hr))
            {
                rc.X = 0;
                rc.Y = 0;
                rc.Width = result->width;
                rc.Height = result->height;
                hr = IWICBitmapSource_CopyPixels(source, &rc, result->width * 4,
                    result->width * result->height * 4, result->bits);

                IWICBitmapSource_Release(source);
            }

            if (SUCCEEDED(hr))
                hr = IWICBitmapFrameDecode_GetResolution(framedecode, &result->dpiX, &result->dpiY);

            IWICBitmapFrameDecode_Release(framedecode);
        }

        if (SUCCEEDED(hr) && has_alpha)
        {
            /* If the alpha channel is fully transparent, we should ignore it. */
            int nonzero_alpha = 0;
            UINT i;

            for (i=0; i<(result->height*result->width); i++)
            {
                if (result->bits[i*4+3] != 0)
                {
                    nonzero_alpha = 1;
                    break;
                }
            }

            if (!nonzero_alpha)
            {
                for (i=0; i<(result->height*result->width); i++)
                    result->bits[i*4+3] = 0xff;

                has_alpha = FALSE;
            }
        }

        if (SUCCEEDED(hr) && !has_alpha)
        {
            /* set alpha data based on the AND mask */
            UINT andBytesPerRow = (result->width+31)/32*4;
            UINT andBytes = andBytesPerRow * result->height;
            INT andStride;
            BYTE *tempdata=NULL;
            BYTE *andRow;
            BYTE *bitsRow;
            UINT bitsStride = result->width * 4;
            UINT x, y;
            ULONG offset;
            ULONG bytesread;
            LARGE_INTEGER seek;
            int topdown;

            BmpDecoder_FindIconMask(bmp_decoder, &offset, &topdown);

            if (offset)
            {
                seek.QuadPart = offset;

                hr = IStream_Seek(stream, seek, STREAM_SEEK_SET, 0);

                if (SUCCEEDED(hr))
                {
                    tempdata = HeapAlloc(GetProcessHeap(), 0, andBytes);
                    if (!tempdata) hr = E_OUTOFMEMORY;
                }

                if (SUCCEEDED(hr))
                    hr = IStream_Read(stream, tempdata, andBytes, &bytesread);

                if (SUCCEEDED(hr) && bytesread == andBytes)
                {
                    if (topdown)
                    {
                        andStride = andBytesPerRow;
                        andRow = tempdata;
                    }
                    else
                    {
                        andStride = -andBytesPerRow;
                        andRow = tempdata + (result->height-1)*andBytesPerRow;
                    }

                    bitsRow = result->bits;
                    for (y=0; y<result->height; y++) {
                        BYTE *andByte=andRow;
                        DWORD *bitsPixel=(DWORD*)bitsRow;
                        for (x=0; x<result->width; x+=8) {
                            BYTE andVal=*andByte++;
                            pixel_set_trans(bitsPixel++, andVal>>7&1);
                            if (x+1 < result->width) pixel_set_trans(bitsPixel++, andVal>>6&1);
                            if (x+2 < result->width) pixel_set_trans(bitsPixel++, andVal>>5&1);
                            if (x+3 < result->width) pixel_set_trans(bitsPixel++, andVal>>4&1);
                            if (x+4 < result->width) pixel_set_trans(bitsPixel++, andVal>>3&1);
                            if (x+5 < result->width) pixel_set_trans(bitsPixel++, andVal>>2&1);
                            if (x+6 < result->width) pixel_set_trans(bitsPixel++, andVal>>1&1);
                            if (x+7 < result->width) pixel_set_trans(bitsPixel++, andVal&1);
                        }
                        andRow += andStride;
                        bitsRow += bitsStride;
                    }
                }

                HeapFree(GetProcessHeap(), 0, tempdata);
            }
        }

        IWICBitmapDecoder_Release(decoder);
    }

    return hr;
}