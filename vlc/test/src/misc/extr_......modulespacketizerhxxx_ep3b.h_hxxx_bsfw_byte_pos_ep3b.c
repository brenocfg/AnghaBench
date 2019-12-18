#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hxxx_bsfw_ep3b_ctx_s {size_t i_bytepos; } ;
struct TYPE_3__ {scalar_t__ p_priv; } ;
typedef  TYPE_1__ bs_t ;

/* Variables and functions */

__attribute__((used)) static size_t hxxx_bsfw_byte_pos_ep3b( const bs_t *s )
{
    struct hxxx_bsfw_ep3b_ctx_s *ctx = (struct hxxx_bsfw_ep3b_ctx_s *) s->p_priv;
    return ctx->i_bytepos;
}