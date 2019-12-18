#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct vlc_input_event {int type; int /*<<< orphan*/  subitems; TYPE_1__ state; TYPE_3__ times; } ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_8__ {int /*<<< orphan*/  userdata; TYPE_2__* cbs; int /*<<< orphan*/  state; } ;
typedef  TYPE_4__ input_item_parser_id_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* on_subtree_added ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* on_ended ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  END_S ; 
#define  INPUT_EVENT_DEAD 131 
#define  INPUT_EVENT_STATE 130 
#define  INPUT_EVENT_SUBITEMS 129 
#define  INPUT_EVENT_TIMES 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  input_GetItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_SetDuration (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
input_item_parser_InputEvent(input_thread_t *input,
                             const struct vlc_input_event *event, void *parser_)
{
    input_item_parser_id_t *parser = parser_;

    switch (event->type)
    {
        case INPUT_EVENT_TIMES:
            input_item_SetDuration(input_GetItem(input), event->times.length);
            break;
        case INPUT_EVENT_STATE:
            parser->state = event->state.value;
            break;
        case INPUT_EVENT_DEAD:
        {
            int status = parser->state == END_S ? VLC_SUCCESS : VLC_EGENERIC;
            parser->cbs->on_ended(input_GetItem(input), status, parser->userdata);
            break;
        }
        case INPUT_EVENT_SUBITEMS:
            if (parser->cbs->on_subtree_added)
                parser->cbs->on_subtree_added(input_GetItem(input),
                                              event->subitems, parser->userdata);
            break;
        default:
            break;
    }
}