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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct items_removed_report {size_t index; size_t count; int /*<<< orphan*/  state; } ;
struct callback_ctx {int /*<<< orphan*/  vec_items_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_state_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (int /*<<< orphan*/ *,struct items_removed_report) ; 

__attribute__((used)) static void
callback_on_items_removed(vlc_playlist_t *playlist, size_t index, size_t count,
                          void *userdata)
{
    struct callback_ctx *ctx = userdata;

    struct items_removed_report report;
    report.index = index;
    report.count = count;
    playlist_state_init(&report.state, playlist);
    vlc_vector_push(&ctx->vec_items_removed, report);
}