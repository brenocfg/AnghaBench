#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  aom_codec_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOM_ERR (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DropFrame ; 
 int /*<<< orphan*/  PopFrames (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PushFrame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VLCDEC_SUCCESS ; 

__attribute__((used)) static void FlushDecoder(decoder_t *dec)
{
    decoder_sys_t *p_sys = dec->p_sys;
    aom_codec_ctx_t *ctx = &p_sys->ctx;

    if(PushFrame(dec, NULL) != VLCDEC_SUCCESS)
        AOM_ERR(dec, ctx, "Failed to flush decoder");
    else
        PopFrames(dec, DropFrame);
}