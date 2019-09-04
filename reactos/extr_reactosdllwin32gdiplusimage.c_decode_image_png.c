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
typedef  int /*<<< orphan*/  IWICBitmapFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_ContainerFormatPng ; 
 int /*<<< orphan*/  GUID_WICPixelFormat1bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat24bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat2bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat4bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppGray ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppIndexed ; 
 scalar_t__ IWICBitmapDecoder_GetFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapFrameDecode_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ decode_frame_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ has_png_transparency_chunk (int /*<<< orphan*/ *) ; 
 scalar_t__ hresult_to_status (scalar_t__) ; 
 scalar_t__ initialize_decoder_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_metadata_reader ; 

__attribute__((used)) static GpStatus decode_image_png(IStream* stream, GpImage **image)
{
    IWICBitmapDecoder *decoder;
    IWICBitmapFrameDecode *frame;
    GpStatus status;
    HRESULT hr;
    GUID format;
    BOOL force_conversion = FALSE;

    status = initialize_decoder_wic(stream, &GUID_ContainerFormatPng, &decoder);
    if (status != Ok)
        return status;

    hr = IWICBitmapDecoder_GetFrame(decoder, 0, &frame);
    if (hr == S_OK)
    {
        hr = IWICBitmapFrameDecode_GetPixelFormat(frame, &format);
        if (hr == S_OK)
        {
            if (IsEqualGUID(&format, &GUID_WICPixelFormat8bppGray))
                force_conversion = TRUE;
            else if ((IsEqualGUID(&format, &GUID_WICPixelFormat8bppIndexed) ||
                      IsEqualGUID(&format, &GUID_WICPixelFormat4bppIndexed) ||
                      IsEqualGUID(&format, &GUID_WICPixelFormat2bppIndexed) ||
                      IsEqualGUID(&format, &GUID_WICPixelFormat1bppIndexed) ||
                      IsEqualGUID(&format, &GUID_WICPixelFormat24bppBGR)) &&
                     has_png_transparency_chunk(stream))
                force_conversion = TRUE;

            status = decode_frame_wic(decoder, force_conversion, 0, png_metadata_reader, image);
        }
        else
            status = hresult_to_status(hr);

        IWICBitmapFrameDecode_Release(frame);
    }
    else
        status = hresult_to_status(hr);

    IWICBitmapDecoder_Release(decoder);
    return status;
}