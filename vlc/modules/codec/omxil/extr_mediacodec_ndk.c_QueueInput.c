#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_codec; } ;
typedef  TYPE_2__ mc_api_sys ;
struct TYPE_8__ {int /*<<< orphan*/  p_obj; TYPE_2__* p_sys; } ;
typedef  TYPE_3__ mc_api ;
struct TYPE_6__ {scalar_t__ (* queueInputBuffer ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/ * (* getInputBuffer ) (int /*<<< orphan*/ ,int,size_t*) ;} ;
struct TYPE_9__ {TYPE_1__ AMediaCodec; } ;

/* Variables and functions */
 int AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM ; 
 int AMEDIACODEC_FLAG_CODEC_CONFIG ; 
 scalar_t__ AMEDIA_OK ; 
 int MC_API_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int,size_t*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ syms ; 

__attribute__((used)) static int QueueInput(mc_api *api, int i_index, const void *p_buf,
                      size_t i_size, vlc_tick_t i_ts, bool b_config)
{
    mc_api_sys *p_sys = api->p_sys;
    uint8_t *p_mc_buf;
    size_t i_mc_size;
    int i_flags = (b_config ? AMEDIACODEC_FLAG_CODEC_CONFIG : 0)
                | (p_buf == NULL ? AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM : 0);

    assert(i_index >= 0);

    p_mc_buf = syms.AMediaCodec.getInputBuffer(p_sys->p_codec,
                                               i_index, &i_mc_size);
    if (!p_mc_buf)
        return MC_API_ERROR;

    if (i_mc_size > i_size)
        i_mc_size = i_size;
    memcpy(p_mc_buf, p_buf, i_mc_size);

    if (syms.AMediaCodec.queueInputBuffer(p_sys->p_codec, i_index, 0, i_mc_size,
                                          i_ts, i_flags) == AMEDIA_OK)
        return 0;
    else
    {
        msg_Err(api->p_obj, "AMediaCodec.queueInputBuffer failed");
        return MC_API_ERROR;
    }
}