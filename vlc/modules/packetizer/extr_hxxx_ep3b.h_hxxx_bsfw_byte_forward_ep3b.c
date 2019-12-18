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
struct hxxx_bsfw_ep3b_ctx_s {int i_bytepos; int /*<<< orphan*/  i_prev; int /*<<< orphan*/  i_bytesize; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p_end; int /*<<< orphan*/ * p; int /*<<< orphan*/ * p_start; scalar_t__ p_priv; } ;
typedef  TYPE_1__ bs_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hxxx_ep3b_to_rbsp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hxxx_ep3b_total_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t hxxx_bsfw_byte_forward_ep3b( bs_t *s, size_t i_count )
{
    struct hxxx_bsfw_ep3b_ctx_s *ctx = (struct hxxx_bsfw_ep3b_ctx_s *) s->p_priv;
    if( s->p == NULL )
    {
        ctx->i_bytesize = hxxx_ep3b_total_size( s->p_start, s->p_end );
        s->p = s->p_start;
        ctx->i_bytepos = 1;
        return 1;
    }

    if( s->p >= s->p_end )
        return 0;

    s->p = hxxx_ep3b_to_rbsp( s->p, s->p_end, &ctx->i_prev, i_count );
    ctx->i_bytepos += i_count;
    return i_count;
}