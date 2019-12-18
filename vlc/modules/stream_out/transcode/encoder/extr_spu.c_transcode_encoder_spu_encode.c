#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* p_encoder; } ;
typedef  TYPE_1__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* pf_encode_sub ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

block_t * transcode_encoder_spu_encode( transcode_encoder_t *p_enc, subpicture_t *p_spu )
{
    return p_enc->p_encoder->pf_encode_sub( p_enc->p_encoder, p_spu );
}