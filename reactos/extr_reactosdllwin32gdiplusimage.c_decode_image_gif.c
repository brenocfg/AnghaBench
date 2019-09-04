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
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * palette; } ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_1__ GpImage ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUID_ContainerFormatGif ; 
 int /*<<< orphan*/  IWICBitmapDecoder_GetFrameCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 scalar_t__ decode_frame_wic (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  gif_metadata_reader ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 scalar_t__ hresult_to_status (int /*<<< orphan*/ ) ; 
 scalar_t__ initialize_decoder_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static GpStatus decode_image_gif(IStream* stream, GpImage **image)
{
    IWICBitmapDecoder *decoder;
    UINT frame_count;
    GpStatus status;
    HRESULT hr;

    status = initialize_decoder_wic(stream, &GUID_ContainerFormatGif, &decoder);
    if(status != Ok)
        return status;

    hr = IWICBitmapDecoder_GetFrameCount(decoder, &frame_count);
    if(FAILED(hr))
        return hresult_to_status(hr);

    status = decode_frame_wic(decoder, frame_count > 1, 0, gif_metadata_reader, image);
    IWICBitmapDecoder_Release(decoder);
    if(status != Ok)
        return status;

    if(frame_count > 1) {
        heap_free((*image)->palette);
        (*image)->palette = NULL;
    }
    return Ok;
}