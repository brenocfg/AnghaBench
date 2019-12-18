#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_cat; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_7__ {int b_frame_drop_allowed; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; int /*<<< orphan*/ * p_module; int /*<<< orphan*/ * pf_flush; int /*<<< orphan*/ * pf_packetize; int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/ * pf_decode; scalar_t__ i_extra_picture_buffers; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void decoder_Init( decoder_t *p_dec, const es_format_t *restrict p_fmt )
{
    p_dec->i_extra_picture_buffers = 0;
    p_dec->b_frame_drop_allowed = false;

    p_dec->pf_decode = NULL;
    p_dec->pf_get_cc = NULL;
    p_dec->pf_packetize = NULL;
    p_dec->pf_flush = NULL;
    p_dec->p_module = NULL;

    es_format_Copy( &p_dec->fmt_in, p_fmt );
    es_format_Init( &p_dec->fmt_out, p_fmt->i_cat, 0 );
}