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
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
struct children_reset_report {int /*<<< orphan*/ * node; } ;
struct callback_ctx {int /*<<< orphan*/  vec_children_reset; } ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,struct children_reset_report) ; 

__attribute__((used)) static void
on_children_reset(vlc_media_tree_t *tree, input_item_node_t *node,
                  void *userdata)
{
    VLC_UNUSED(tree);

    struct callback_ctx *ctx = userdata;

    struct children_reset_report report;
    report.node = node;
    bool ok = vlc_vector_push(&ctx->vec_children_reset, report);
    assert(ok);
}