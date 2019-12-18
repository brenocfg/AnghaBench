#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ i_cat; } ;
struct TYPE_10__ {TYPE_1__ fmt_in; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* fptr_MFCreateMemoryBuffer ) (scalar_t__,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* fptr_MFCreateAlignedMemoryBuffer ) (scalar_t__,scalar_t__,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* fptr_MFCreateSample ) (int /*<<< orphan*/ **) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  mft; TYPE_5__ mf_handle; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_12__ {int dwFlags; scalar_t__ cbSize; scalar_t__ cbAlignment; } ;
typedef  TYPE_4__ MFT_OUTPUT_STREAM_INFO ;
typedef  TYPE_5__ MFHandle ;
typedef  int /*<<< orphan*/  IMFSample ;
typedef  int /*<<< orphan*/  IMFMediaBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMFSample_AddBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFTransform_GetOutputStreamInfo (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 int MFT_OUTPUT_STREAM_CAN_PROVIDE_SAMPLES ; 
 scalar_t__ MFT_OUTPUT_STREAM_FIXED_SAMPLE_SIZE ; 
 int MFT_OUTPUT_STREAM_PROVIDES_SAMPLES ; 
 scalar_t__ MFT_OUTPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER ; 
 scalar_t__ MFT_OUTPUT_STREAM_WHOLE_SAMPLES ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int AllocateOutputSample(decoder_t *p_dec, DWORD stream_id, IMFSample **result)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    MFHandle *mf = &p_sys->mf_handle;
    HRESULT hr;

    *result = NULL;

    IMFSample *output_sample = NULL;

    MFT_OUTPUT_STREAM_INFO output_info;
    hr = IMFTransform_GetOutputStreamInfo(p_sys->mft, stream_id, &output_info);
    if (FAILED(hr))
        goto error;

    if (output_info.dwFlags & (MFT_OUTPUT_STREAM_PROVIDES_SAMPLES | MFT_OUTPUT_STREAM_CAN_PROVIDE_SAMPLES))
    {
        /* The MFT will provide an allocated sample. */
        return VLC_SUCCESS;
    }

    DWORD expected_flags = 0;
    if (p_dec->fmt_in.i_cat == VIDEO_ES)
        expected_flags |= MFT_OUTPUT_STREAM_WHOLE_SAMPLES
                        | MFT_OUTPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER
                        | MFT_OUTPUT_STREAM_FIXED_SAMPLE_SIZE;
    if ((output_info.dwFlags & expected_flags) != expected_flags)
        goto error;

    hr = mf->fptr_MFCreateSample(&output_sample);
    if (FAILED(hr))
        goto error;

    IMFMediaBuffer *output_media_buffer = NULL;
    DWORD allocation_size = output_info.cbSize;
    DWORD alignment = output_info.cbAlignment;
    if (alignment > 0)
        hr = mf->fptr_MFCreateAlignedMemoryBuffer(allocation_size, alignment - 1, &output_media_buffer);
    else
        hr = mf->fptr_MFCreateMemoryBuffer(allocation_size, &output_media_buffer);
    if (FAILED(hr))
        goto error;

    hr = IMFSample_AddBuffer(output_sample, output_media_buffer);
    if (FAILED(hr))
        goto error;

    *result = output_sample;

    return VLC_SUCCESS;

error:
    msg_Err(p_dec, "Error in AllocateOutputSample()");
    if (output_sample)
        IMFSample_Release(output_sample);
    return VLC_EGENERIC;
}