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
typedef  int /*<<< orphan*/  vlc_player_title_list ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  on_titles_changed ; 
 int /*<<< orphan*/  vlc_player_title_list_Hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
player_on_titles_changed(vlc_player_t *player,
                         vlc_player_title_list *titles, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    if (titles)
        vlc_player_title_list_Hold(titles);
    VEC_PUSH(on_titles_changed, titles);
}