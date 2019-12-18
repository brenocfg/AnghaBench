#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hxxx_bsfw_ep3b_ctx_s {scalar_t__ i_bytesize; scalar_t__ i_bytepos; scalar_t__ i_prev; } ;

/* Variables and functions */

__attribute__((used)) static void hxxx_bsfw_ep3b_ctx_init( struct hxxx_bsfw_ep3b_ctx_s *ctx )
{
    ctx->i_prev = 0;
    ctx->i_bytepos = 0;
    ctx->i_bytesize = 0;
}