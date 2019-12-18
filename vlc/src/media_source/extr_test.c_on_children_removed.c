#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
struct children_removed_report {size_t count; int /*<<< orphan*/  first_media; TYPE_1__* node; } ;
struct callback_ctx {int /*<<< orphan*/  vec_children_removed; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ ) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,struct children_removed_report) ; 

__attribute__((used)) static void
on_children_removed(vlc_media_tree_t *tree, input_item_node_t *node,
                    input_item_node_t *const children[], size_t count,
                    void *userdata)
{
    VLC_UNUSED(tree);

    struct callback_ctx *ctx = userdata;

    struct children_removed_report report;
    report.node = node;
    report.first_media = input_item_Hold(children[0]->p_item);
    report.count = count;
    bool ok = vlc_vector_push(&ctx->vec_children_removed, report);
    assert(ok);
}