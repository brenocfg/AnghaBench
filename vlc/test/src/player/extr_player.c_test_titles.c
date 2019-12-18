#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_title_list ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_8__ {scalar_t__ size; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ vec_on_titles_changed ;
struct TYPE_9__ {int size; int* data; } ;
typedef  TYPE_3__ vec_on_title_selection_changed ;
struct TYPE_10__ {scalar_t__ size; } ;
typedef  TYPE_4__ vec_on_chapter_selection_changed ;
struct vlc_player_title {int chapter_count; } ;
struct media_params {int title_count; int chapter_count; int null_names; } ;
struct TYPE_7__ {TYPE_4__ on_chapter_selection_changed; TYPE_3__ on_title_selection_changed; TYPE_2__ on_titles_changed; } ;
struct ctx {int /*<<< orphan*/  wait; TYPE_1__ report; int /*<<< orphan*/ * player; } ;
struct TYPE_11__ {size_t const chapter_idx; int title_idx; } ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 TYPE_5__ VEC_LAST (TYPE_4__*) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_normal_state (struct ctx*) ; 
 int /*<<< orphan*/  player_set_next_mock_media (struct ctx*,char*,struct media_params*) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*,int) ; 
 int /*<<< orphan*/  test_prestop (struct ctx*) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_GetTitleList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectChapter (int /*<<< orphan*/ *,struct vlc_player_title const*,size_t const) ; 
 int /*<<< orphan*/  vlc_player_SelectTitle (int /*<<< orphan*/ *,struct vlc_player_title const*) ; 
 struct vlc_player_title* vlc_player_title_list_GetAt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_titles(struct ctx *ctx, bool null_names)
{
    test_log("titles (null_names: %d)\n", null_names);
    vlc_player_t *player = ctx->player;

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_SEC(100));
    params.title_count = 5;
    params.chapter_count = 2000;
    params.null_names = null_names;
    player_set_next_mock_media(ctx, "media1", &params);

    player_start(ctx);

    /* Wait for the title list */
    vlc_player_title_list *titles;
    {
        vec_on_titles_changed *vec = &ctx->report.on_titles_changed;
        while (vec->size == 0)
            vlc_player_CondWait(player, &ctx->wait);
        titles = vec->data[0];
        assert(titles != NULL && titles == vlc_player_GetTitleList(player));
    }

    /* Select a new title and a new chapter */
    const size_t last_chapter_idx = params.chapter_count - 1;
    {
        vec_on_title_selection_changed *vec =
            &ctx->report.on_title_selection_changed;
        while (vec->size == 0)
            vlc_player_CondWait(player, &ctx->wait);
        assert(vec->data[0] == 0);

        const struct vlc_player_title *title =
            vlc_player_title_list_GetAt(titles, 4);
        vlc_player_SelectTitle(player, title);

        while (vec->size == 1)
            vlc_player_CondWait(player, &ctx->wait);
        assert(vec->data[1] == 4);

        assert(title->chapter_count == params.chapter_count);
        vlc_player_SelectChapter(player, title, last_chapter_idx);
    }

    /* Wait for the chapter selection */
    {
        vec_on_chapter_selection_changed *vec =
            &ctx->report.on_chapter_selection_changed;

        while (vec->size == 0 || VEC_LAST(vec).chapter_idx != last_chapter_idx)
            vlc_player_CondWait(player, &ctx->wait);
        assert(VEC_LAST(vec).title_idx == 4);
    }

    test_prestop(ctx);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);
    assert_normal_state(ctx);
    test_end(ctx);
}