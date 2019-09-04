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
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GUID_ContainerFormatTiff ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapDecoder_GetContainerFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreateDecoderFromStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_decoder(const void *image_data, UINT image_size, IWICBitmapDecoder **decoder)
{
    HGLOBAL hmem;
    BYTE *data;
    HRESULT hr;
    IStream *stream;
    GUID format;
    LONG refcount;

    *decoder = NULL;

    hmem = GlobalAlloc(0, image_size);
    data = GlobalLock(hmem);
    memcpy(data, image_data, image_size);
    GlobalUnlock(hmem);

    hr = CreateStreamOnHGlobal(hmem, TRUE, &stream);
    ok(hr == S_OK, "CreateStreamOnHGlobal error %#x\n", hr);

    hr = IWICImagingFactory_CreateDecoderFromStream(factory, stream, NULL, 0, decoder);
    if (hr == S_OK)
    {
        hr = IWICBitmapDecoder_GetContainerFormat(*decoder, &format);
        ok(hr == S_OK, "GetContainerFormat error %#x\n", hr);
        ok(IsEqualGUID(&format, &GUID_ContainerFormatTiff),
           "wrong container format %s\n", wine_dbgstr_guid(&format));

        refcount = IStream_Release(stream);
        ok(refcount > 0, "expected stream refcount > 0\n");
    }

    return hr;
}