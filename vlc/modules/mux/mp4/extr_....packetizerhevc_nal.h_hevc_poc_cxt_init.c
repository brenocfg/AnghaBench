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
struct TYPE_5__ {int first_picture; TYPE_1__ prevTid0PicOrderCnt; } ;
typedef  TYPE_2__ hevc_poc_ctx_t ;

/* Variables and functions */

__attribute__((used)) static inline void hevc_poc_cxt_init( hevc_poc_ctx_t *p_ctx )
{
    p_ctx->prevTid0PicOrderCnt.lsb = 0;
    p_ctx->prevTid0PicOrderCnt.msb = 0;
    p_ctx->first_picture = true;
}