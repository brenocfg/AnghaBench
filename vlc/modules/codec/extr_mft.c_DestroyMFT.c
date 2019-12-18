#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mft; int /*<<< orphan*/ * output_type; int /*<<< orphan*/ * output_sample; int /*<<< orphan*/ * input_type; int /*<<< orphan*/ * event_generator; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  IMFMediaBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IMFMediaEventGenerator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFMediaType_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFSample_GetBufferByIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMFSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMFTransform_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyMFT(decoder_t *p_dec)
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if (p_sys->event_generator)
        IMFMediaEventGenerator_Release(p_sys->event_generator);
    if (p_sys->input_type)
        IMFMediaType_Release(p_sys->input_type);
    if (p_sys->output_sample)
    {
        IMFMediaBuffer *output_media_buffer = NULL;
        HRESULT hr = IMFSample_GetBufferByIndex(p_sys->output_sample, 0, &output_media_buffer);
        if (SUCCEEDED(hr))
            IMFSample_Release(output_media_buffer);
        IMFSample_Release(p_sys->output_sample);
    }
    if (p_sys->output_type)
        IMFMediaType_Release(p_sys->output_type);
    if (p_sys->mft)
        IMFTransform_Release(p_sys->mft);

    p_sys->event_generator = NULL;
    p_sys->input_type = NULL;
    p_sys->output_sample = NULL;
    p_sys->output_type = NULL;
    p_sys->mft = NULL;
}