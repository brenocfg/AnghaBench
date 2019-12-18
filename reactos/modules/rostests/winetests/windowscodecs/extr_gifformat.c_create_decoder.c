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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_ContainerFormatGif ; 
 scalar_t__ IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapDecoder_GetContainerFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreateDecoderFromStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_stream (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IWICBitmapDecoder *create_decoder(const void *image_data, UINT image_size)
{
    HRESULT hr;
    IWICBitmapDecoder *decoder;
    IStream *stream;
    GUID format;
    LONG refcount;

    stream = create_stream(image_data, image_size);
    if (!stream) return NULL;

    hr = IWICImagingFactory_CreateDecoderFromStream(factory, stream, NULL, 0, &decoder);
    ok(hr == S_OK, "CreateDecoderFromStream error %#x\n", hr);

    hr = IWICBitmapDecoder_GetContainerFormat(decoder, &format);
    ok(hr == S_OK, "GetContainerFormat error %#x\n", hr);
    ok(IsEqualGUID(&format, &GUID_ContainerFormatGif),
       "wrong container format %s\n", wine_dbgstr_guid(&format));

    refcount = IStream_Release(stream);
    ok(refcount > 0, "expected stream refcount > 0\n");

    return decoder;
}