#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* fptr_MFCreateMemoryBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* fptr_MFCreateSample ) (int /*<<< orphan*/ **) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  mft; TYPE_4__ mf_handle; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_3__ MFT_INPUT_STREAM_INFO ;
typedef  TYPE_4__ MFHandle ;
typedef  int /*<<< orphan*/  IMFSample ;
typedef  int /*<<< orphan*/  IMFMediaBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMFMediaBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFSample_AddBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFTransform_GetInputStreamInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  __MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int AllocateInputSample(decoder_t *p_dec, DWORD stream_id, IMFSample** result, DWORD size)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    MFHandle *mf = &p_sys->mf_handle;
    HRESULT hr;

    *result = NULL;

    IMFSample *input_sample = NULL;

    MFT_INPUT_STREAM_INFO input_info;
    hr = IMFTransform_GetInputStreamInfo(p_sys->mft, stream_id, &input_info);
    if (FAILED(hr))
        goto error;

    hr = mf->fptr_MFCreateSample(&input_sample);
    if (FAILED(hr))
        goto error;

    IMFMediaBuffer *input_media_buffer = NULL;
    DWORD allocation_size = __MAX(input_info.cbSize, size);
    hr = mf->fptr_MFCreateMemoryBuffer(allocation_size, &input_media_buffer);
    if (FAILED(hr))
        goto error;

    hr = IMFSample_AddBuffer(input_sample, input_media_buffer);
    IMFMediaBuffer_Release(input_media_buffer);
    if (FAILED(hr))
        goto error;

    *result = input_sample;

    return VLC_SUCCESS;

error:
    msg_Err(p_dec, "Error in AllocateInputSample()");
    if (input_sample)
        IMFSample_Release(input_sample);
    if (input_media_buffer)
        IMFMediaBuffer_Release(input_media_buffer);
    return VLC_EGENERIC;
}