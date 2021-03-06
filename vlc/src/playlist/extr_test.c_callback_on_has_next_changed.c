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
struct has_next_changed_report {int has_next; } ;
struct callback_ctx {int /*<<< orphan*/  vec_has_next_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (int /*<<< orphan*/ *,struct has_next_changed_report) ; 

__attribute__((used)) static void
callback_on_has_next_changed(vlc_playlist_t *playlist, bool has_next,
                             void *userdata)
{
    VLC_UNUSED(playlist);
    struct callback_ctx *ctx = userdata;

    struct has_next_changed_report report;
    report.has_next = has_next;
    vlc_vector_push(&ctx->vec_has_next_changed, report);
}