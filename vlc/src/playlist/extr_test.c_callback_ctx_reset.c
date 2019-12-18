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
struct callback_ctx {int /*<<< orphan*/  vec_has_next_changed; int /*<<< orphan*/  vec_has_prev_changed; int /*<<< orphan*/  vec_current_index_changed; int /*<<< orphan*/  vec_playback_order_changed; int /*<<< orphan*/  vec_playback_repeat_changed; int /*<<< orphan*/  vec_items_removed; int /*<<< orphan*/  vec_items_moved; int /*<<< orphan*/  vec_items_added; int /*<<< orphan*/  vec_items_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_vector_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
callback_ctx_reset(struct callback_ctx *ctx)
{
    vlc_vector_clear(&ctx->vec_items_reset);
    vlc_vector_clear(&ctx->vec_items_added);
    vlc_vector_clear(&ctx->vec_items_moved);
    vlc_vector_clear(&ctx->vec_items_removed);
    vlc_vector_clear(&ctx->vec_playback_repeat_changed);
    vlc_vector_clear(&ctx->vec_playback_order_changed);
    vlc_vector_clear(&ctx->vec_current_index_changed);
    vlc_vector_clear(&ctx->vec_has_prev_changed);
    vlc_vector_clear(&ctx->vec_has_next_changed);
}