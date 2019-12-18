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
struct TYPE_4__ {scalar_t__ msb; scalar_t__ lsb; } ;
struct TYPE_5__ {int prevRefPictureIsBottomField; int prevRefPictureHasMMCO5; scalar_t__ prevFrameNumOffset; scalar_t__ prevFrameNum; TYPE_1__ prevPicOrderCnt; } ;
typedef  TYPE_2__ h264_poc_context_t ;

/* Variables and functions */

__attribute__((used)) static inline void h264_poc_context_init( h264_poc_context_t *p_ctx )
{
    p_ctx->prevPicOrderCnt.lsb = 0;
    p_ctx->prevPicOrderCnt.msb = 0;
    p_ctx->prevFrameNum = 0;
    p_ctx->prevFrameNumOffset = 0;
    p_ctx->prevRefPictureIsBottomField = false;
    p_ctx->prevRefPictureHasMMCO5 = false;
}