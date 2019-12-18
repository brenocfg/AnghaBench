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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_title {int dummy; } ;
struct vlc_player_chapter {int dummy; } ;
struct report_chapter_selection {size_t title_idx; size_t chapter_idx; } ;
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,struct report_chapter_selection) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_chapter_selection_changed ; 

__attribute__((used)) static void
player_on_chapter_selection_changed(vlc_player_t *player,
                                    const struct vlc_player_title *title,
                                    size_t title_idx,
                                    const struct vlc_player_chapter *chapter,
                                    size_t chapter_idx, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    struct report_chapter_selection report = {
        .title_idx = title_idx,
        .chapter_idx = chapter_idx,
    };
    VEC_PUSH(on_chapter_selection_changed, report);
    (void) title;
    (void) chapter;
}