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
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
typedef  int UINT ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_ContainerFormatPng ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IWICBitmapDecoder_GetContainerFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreateDecoderFromStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SHCreateMemStream (void const*,int) ; 
 int /*<<< orphan*/  STREAM_SEEK_CUR ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_decoder(const void *image_data, UINT image_size, IWICBitmapDecoder **decoder)
{
    HRESULT hr;
    IStream *stream;
    GUID format;
    LONG refcount;
    ULARGE_INTEGER pos;
    LARGE_INTEGER zero;

    *decoder = NULL;

    stream = SHCreateMemStream (image_data, image_size);
    ok(stream != NULL, "SHCreateMemStream error\n");

    hr = IWICImagingFactory_CreateDecoderFromStream(factory, stream, NULL, 0, decoder);
    if (hr == S_OK)
    {
        hr = IWICBitmapDecoder_GetContainerFormat(*decoder, &format);
        ok(hr == S_OK, "GetContainerFormat error %#x\n", hr);
        ok(IsEqualGUID(&format, &GUID_ContainerFormatPng),
           "wrong container format %s\n", wine_dbgstr_guid(&format));

        zero.QuadPart = 0;
        IStream_Seek (stream, zero, STREAM_SEEK_CUR, &pos);
        ok(pos.QuadPart < image_size, "seek beyond the end of stream: %x%08x >= %x\n",
           (UINT)(pos.QuadPart >> 32), (UINT)pos.QuadPart, image_size);

        refcount = IStream_Release(stream);
        ok(refcount > 0, "expected stream refcount > 0\n");
    }
    else
        IStream_Release(stream);

    return hr;
}