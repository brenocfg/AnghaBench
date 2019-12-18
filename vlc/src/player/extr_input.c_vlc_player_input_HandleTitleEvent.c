#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_10__ {float progress; int /*<<< orphan*/  current_title; } ;
struct TYPE_11__ {TYPE_2__ states; } ;
struct vlc_player_input {size_t title_selected; size_t chapter_selected; TYPE_3__ ml; int /*<<< orphan*/  thread; TYPE_5__* titles; int /*<<< orphan*/ * player; } ;
struct TYPE_9__ {size_t count; int /*<<< orphan*/  array; } ;
struct vlc_input_event_title {int action; size_t selected_idx; TYPE_1__ list; } ;
struct TYPE_12__ {int i_title_offset; int i_seekpoint_offset; } ;
typedef  TYPE_4__ input_thread_private_t ;
struct TYPE_13__ {size_t count; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
#define  VLC_INPUT_TITLE_NEW_LIST 129 
#define  VLC_INPUT_TITLE_SELECTED 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  input_SetPosition (int /*<<< orphan*/ ,float,int) ; 
 TYPE_4__* input_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_title_selection_changed ; 
 int /*<<< orphan*/  on_titles_changed ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_player_SelectTitleIdx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_SendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,...) ; 
 TYPE_5__* vlc_player_title_list_Create (int /*<<< orphan*/ ,size_t,int const,int const) ; 
 int /*<<< orphan*/  vlc_player_title_list_Release (TYPE_5__*) ; 

__attribute__((used)) static void
vlc_player_input_HandleTitleEvent(struct vlc_player_input *input,
                                  const struct vlc_input_event_title *ev)
{
    vlc_player_t *player = input->player;
    switch (ev->action)
    {
        case VLC_INPUT_TITLE_NEW_LIST:
        {
            input_thread_private_t *input_th = input_priv(input->thread);
            const int title_offset = input_th->i_title_offset;
            const int chapter_offset = input_th->i_seekpoint_offset;

            if (input->titles)
                vlc_player_title_list_Release(input->titles);
            input->title_selected = input->chapter_selected = 0;
            input->titles =
                vlc_player_title_list_Create(ev->list.array, ev->list.count,
                                             title_offset, chapter_offset);
            vlc_player_SendEvent(player, on_titles_changed, input->titles);
            if (input->titles)
            {
                vlc_player_SendEvent(player, on_title_selection_changed,
                                     &input->titles->array[0], 0);
                if (input->ml.states.current_title >= 0 &&
                    (size_t)input->ml.states.current_title < ev->list.count)
                {
                    vlc_player_SelectTitleIdx(player, input->ml.states.current_title);
                }
            }
            break;
        }
        case VLC_INPUT_TITLE_SELECTED:
            if (!input->titles)
                return; /* a previous VLC_INPUT_TITLE_NEW_LIST failed */
            assert(ev->selected_idx < input->titles->count);
            input->title_selected = ev->selected_idx;
            vlc_player_SendEvent(player, on_title_selection_changed,
                                 &input->titles->array[input->title_selected],
                                 input->title_selected);
            if (input->ml.states.current_title >= 0 &&
                (size_t)input->ml.states.current_title == ev->selected_idx &&
                input->ml.states.progress > .0f)
            {
                input_SetPosition(input->thread, input->ml.states.progress, false);
                /* Reset the wanted title to avoid forcing it or the position
                 * again during the next title change
                 */
                input->ml.states.current_title = 0;
            }
            break;
        default:
            vlc_assert_unreachable();
    }
}