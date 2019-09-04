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
typedef  int /*<<< orphan*/  metadata_reader_func ;
typedef  int /*<<< orphan*/  REFGUID ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 scalar_t__ decode_frame_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ initialize_decoder_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static GpStatus decode_image_wic(IStream *stream, REFGUID container,
        metadata_reader_func metadata_reader, GpImage **image)
{
    IWICBitmapDecoder *decoder;
    GpStatus status;

    status = initialize_decoder_wic(stream, container, &decoder);
    if(status != Ok)
        return status;

    status = decode_frame_wic(decoder, FALSE, 0, metadata_reader, image);
    IWICBitmapDecoder_Release(decoder);
    return status;
}