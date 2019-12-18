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
struct hxxx_bsfw_ep3b_ctx_s {scalar_t__ i_bytesize; scalar_t__ i_bytepos; } ;
struct TYPE_3__ {scalar_t__ p_start; scalar_t__ p_end; scalar_t__ p_priv; } ;
typedef  TYPE_1__ bs_t ;

/* Variables and functions */
 scalar_t__ hxxx_ep3b_total_size (scalar_t__,scalar_t__) ; 

__attribute__((used)) static size_t hxxx_bsfw_byte_remain_ep3b( const bs_t *s )
{
    struct hxxx_bsfw_ep3b_ctx_s *ctx = (struct hxxx_bsfw_ep3b_ctx_s *) s->p_priv;
    if( ctx->i_bytesize == 0 && s->p_start != s->p_end )
        ctx->i_bytesize = hxxx_ep3b_total_size( s->p_start, s->p_end );
    return (ctx->i_bytesize > ctx->i_bytepos) ? ctx->i_bytesize - ctx->i_bytepos : 0;
}