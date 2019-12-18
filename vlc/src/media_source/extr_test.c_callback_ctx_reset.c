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
struct callback_ctx {int /*<<< orphan*/  vec_children_removed; int /*<<< orphan*/  vec_children_added; int /*<<< orphan*/  vec_children_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_ctx_destroy_reports (struct callback_ctx*) ; 
 int /*<<< orphan*/  vlc_vector_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
callback_ctx_reset(struct callback_ctx *ctx)
{
    callback_ctx_destroy_reports(ctx);
    vlc_vector_clear(&ctx->vec_children_reset);
    vlc_vector_clear(&ctx->vec_children_added);
    vlc_vector_clear(&ctx->vec_children_removed);
}