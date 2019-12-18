#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int sort; int case_sensitive; } ;
struct TYPE_12__ {int /*<<< orphan*/  UTF8_STRING; } ;
struct TYPE_14__ {int /*<<< orphan*/  connection; TYPE_1__ ewmh; } ;
struct TYPE_13__ {int retv; unsigned int filtered_lines; void* quit; void** line_map; void* selected_line; int /*<<< orphan*/  list_view; void* refilter; int /*<<< orphan*/  text; int /*<<< orphan*/ * case_indicator; } ;
struct TYPE_11__ {int /*<<< orphan*/  main_window; } ;
typedef  TYPE_2__ RofiViewState ;
typedef  int KeyBindingAction ;

/* Variables and functions */
#define  ACCEPT_ALT 192 
#define  ACCEPT_CUSTOM 191 
#define  ACCEPT_ENTRY 190 
#define  CANCEL 189 
#define  CHANGE_ELLIPSIZE 188 
#define  CLEAR_LINE 187 
 size_t CLIPBOARD ; 
#define  CUSTOM_1 186 
#define  CUSTOM_10 185 
#define  CUSTOM_11 184 
#define  CUSTOM_12 183 
#define  CUSTOM_13 182 
#define  CUSTOM_14 181 
#define  CUSTOM_15 180 
#define  CUSTOM_16 179 
#define  CUSTOM_17 178 
#define  CUSTOM_18 177 
#define  CUSTOM_19 176 
#define  CUSTOM_2 175 
#define  CUSTOM_3 174 
#define  CUSTOM_4 173 
#define  CUSTOM_5 172 
#define  CUSTOM_6 171 
#define  CUSTOM_7 170 
#define  CUSTOM_8 169 
#define  CUSTOM_9 168 
 TYPE_10__ CacheState ; 
#define  DELETE_ENTRY 167 
 int MENU_CANCEL ; 
 int MENU_CUSTOM_ACTION ; 
 void* MENU_CUSTOM_INPUT ; 
 int MENU_ENTRY_DELETE ; 
 int MENU_LOWER_MASK ; 
 int MENU_NEXT ; 
 void* MENU_OK ; 
 int MENU_PREVIOUS ; 
 int MENU_QUICK_SWITCH ; 
#define  MODE_NEXT 166 
#define  MODE_PREVIOUS 165 
#define  MOVE_CHAR_BACK 164 
#define  MOVE_CHAR_FORWARD 163 
#define  MOVE_END 162 
#define  MOVE_FRONT 161 
#define  MOVE_WORD_BACK 160 
#define  MOVE_WORD_FORWARD 159 
#define  PAGE_NEXT 158 
#define  PAGE_PREV 157 
#define  PASTE_PRIMARY 156 
#define  PASTE_SECONDARY 155 
#define  REMOVE_CHAR_BACK 154 
#define  REMOVE_CHAR_FORWARD 153 
#define  REMOVE_TO_EOL 152 
#define  REMOVE_TO_SOL 151 
#define  REMOVE_WORD_BACK 150 
#define  REMOVE_WORD_FORWARD 149 
#define  ROW_DOWN 148 
#define  ROW_FIRST 147 
#define  ROW_LAST 146 
#define  ROW_LEFT 145 
#define  ROW_RIGHT 144 
#define  ROW_SELECT 143 
#define  ROW_TAB 142 
#define  ROW_UP 141 
#define  SCREENSHOT 140 
#define  SELECT_ELEMENT_1 139 
#define  SELECT_ELEMENT_10 138 
#define  SELECT_ELEMENT_2 137 
#define  SELECT_ELEMENT_3 136 
#define  SELECT_ELEMENT_4 135 
#define  SELECT_ELEMENT_5 134 
#define  SELECT_ELEMENT_6 133 
#define  SELECT_ELEMENT_7 132 
#define  SELECT_ELEMENT_8 131 
#define  SELECT_ELEMENT_9 130 
#define  TOGGLE_CASE_SENSITIVITY 129 
#define  TOGGLE_SORT 128 
 void* TRUE ; 
 void* UINT32_MAX ; 
 int /*<<< orphan*/  XCB_ATOM_PRIMARY ; 
 int /*<<< orphan*/  XCB_CURRENT_TIME ; 
 TYPE_9__ config ; 
 int /*<<< orphan*/  get_matching_state () ; 
 unsigned int listview_get_selected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_left (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_page_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_page_prev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_right (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_toggle_ellipsizing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * netatoms ; 
 int /*<<< orphan*/  rofi_capture_screenshot () ; 
 TYPE_2__* rofi_view_get_active () ; 
 int /*<<< orphan*/  rofi_view_nav_first (TYPE_2__*) ; 
 int /*<<< orphan*/  rofi_view_nav_last (TYPE_2__*) ; 
 int /*<<< orphan*/  rofi_view_nav_row_select (TYPE_2__*) ; 
 int /*<<< orphan*/  rofi_view_nav_row_tab (TYPE_2__*) ; 
 int textbox_keybinding (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  textbox_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb ; 
 int /*<<< orphan*/  xcb_convert_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_view_trigger_global_action ( KeyBindingAction action )
{
    RofiViewState *state = rofi_view_get_active ();
    switch ( action )
    {
    // Handling of paste
    case PASTE_PRIMARY:
        xcb_convert_selection ( xcb->connection, CacheState.main_window, XCB_ATOM_PRIMARY,
                                xcb->ewmh.UTF8_STRING, xcb->ewmh.UTF8_STRING, XCB_CURRENT_TIME );
        xcb_flush ( xcb->connection );
        break;
    case PASTE_SECONDARY:
        xcb_convert_selection ( xcb->connection, CacheState.main_window, netatoms[CLIPBOARD],
                                xcb->ewmh.UTF8_STRING, xcb->ewmh.UTF8_STRING, XCB_CURRENT_TIME );
        xcb_flush ( xcb->connection );
        break;
    case SCREENSHOT:
        rofi_capture_screenshot ( );
        break;
    case CHANGE_ELLIPSIZE:
        if ( state->list_view ) {
            listview_toggle_ellipsizing ( state->list_view );
        }
        break;
    case TOGGLE_SORT:
        if ( state->case_indicator != NULL ) {
            config.sort     = !config.sort;
            state->refilter = TRUE;
            textbox_text ( state->case_indicator, get_matching_state () );
        }
        break;
    case MODE_PREVIOUS:
        state->retv              = MENU_PREVIOUS;
        ( state->selected_line ) = 0;
        state->quit              = TRUE;
        break;
    // Menu navigation.
    case MODE_NEXT:
        state->retv              = MENU_NEXT;
        ( state->selected_line ) = 0;
        state->quit              = TRUE;
        break;
    // Toggle case sensitivity.
    case TOGGLE_CASE_SENSITIVITY:
        if ( state->case_indicator != NULL ) {
            config.case_sensitive    = !config.case_sensitive;
            ( state->selected_line ) = 0;
            state->refilter          = TRUE;
            textbox_text ( state->case_indicator, get_matching_state () );
        }
        break;
    // Special delete entry command.
    case DELETE_ENTRY:
    {
        unsigned int selected = listview_get_selected ( state->list_view );
        if ( selected < state->filtered_lines ) {
            ( state->selected_line ) = state->line_map[selected];
            state->retv              = MENU_ENTRY_DELETE;
            state->quit              = TRUE;
        }
        break;
    }
    case SELECT_ELEMENT_1:
    case SELECT_ELEMENT_2:
    case SELECT_ELEMENT_3:
    case SELECT_ELEMENT_4:
    case SELECT_ELEMENT_5:
    case SELECT_ELEMENT_6:
    case SELECT_ELEMENT_7:
    case SELECT_ELEMENT_8:
    case SELECT_ELEMENT_9:
    case SELECT_ELEMENT_10:
    {
        unsigned int index = action - SELECT_ELEMENT_1;
        if ( index < state->filtered_lines ) {
            state->selected_line = state->line_map[index];
            state->retv          = MENU_OK;
            state->quit          = TRUE;
        }
        break;
    }
    case CUSTOM_1:
    case CUSTOM_2:
    case CUSTOM_3:
    case CUSTOM_4:
    case CUSTOM_5:
    case CUSTOM_6:
    case CUSTOM_7:
    case CUSTOM_8:
    case CUSTOM_9:
    case CUSTOM_10:
    case CUSTOM_11:
    case CUSTOM_12:
    case CUSTOM_13:
    case CUSTOM_14:
    case CUSTOM_15:
    case CUSTOM_16:
    case CUSTOM_17:
    case CUSTOM_18:
    case CUSTOM_19:
    {
        state->selected_line = UINT32_MAX;
        unsigned int selected = listview_get_selected ( state->list_view );
        if ( selected < state->filtered_lines ) {
            ( state->selected_line ) = state->line_map[selected];
        }
        state->retv = MENU_QUICK_SWITCH | ( ( action - CUSTOM_1 ) & MENU_LOWER_MASK );
        state->quit = TRUE;
        break;
    }
    // If you add a binding here, make sure to add it to rofi_view_keyboard_navigation too
    case CANCEL:
        state->retv = MENU_CANCEL;
        state->quit = TRUE;
        break;
    case ROW_UP:
        listview_nav_up ( state->list_view );
        break;
    case ROW_TAB:
        rofi_view_nav_row_tab ( state );
        break;
    case ROW_DOWN:
        listview_nav_down ( state->list_view );
        break;
    case ROW_LEFT:
        listview_nav_left ( state->list_view );
        break;
    case ROW_RIGHT:
        listview_nav_right ( state->list_view );
        break;
    case PAGE_PREV:
        listview_nav_page_prev ( state->list_view );
        break;
    case PAGE_NEXT:
        listview_nav_page_next ( state->list_view );
        break;
    case ROW_FIRST:
        rofi_view_nav_first ( state );
        break;
    case ROW_LAST:
        rofi_view_nav_last ( state );
        break;
    case ROW_SELECT:
        rofi_view_nav_row_select ( state );
        break;
    // If you add a binding here, make sure to add it to textbox_keybinding too
    case MOVE_CHAR_BACK:
    {
        if ( textbox_keybinding ( state->text, action ) == 0 ) {
            listview_nav_left ( state->list_view );
        }
        break;
    }
    case MOVE_CHAR_FORWARD:
    {
        if ( textbox_keybinding ( state->text, action ) == 0 ) {
            listview_nav_right ( state->list_view );
        }
        break;
    }
    case CLEAR_LINE:
    case MOVE_FRONT:
    case MOVE_END:
    case REMOVE_TO_EOL:
    case REMOVE_TO_SOL:
    case REMOVE_WORD_BACK:
    case REMOVE_WORD_FORWARD:
    case REMOVE_CHAR_FORWARD:
    case MOVE_WORD_BACK:
    case MOVE_WORD_FORWARD:
    case REMOVE_CHAR_BACK:
    {
        int rc = textbox_keybinding ( state->text, action );
        if ( rc == 1 ) {
            // Entry changed.
            state->refilter = TRUE;
        }
        else if ( rc == 2 ) {
            // Movement.
        }
        break;
    }
    case ACCEPT_ALT:
    {
        unsigned int selected = listview_get_selected ( state->list_view );
        state->selected_line = UINT32_MAX;
        if ( selected < state->filtered_lines ) {
            ( state->selected_line ) = state->line_map[selected];
            state->retv              = MENU_OK;
        }
        else {
            // Nothing entered and nothing selected.
            state->retv = MENU_CUSTOM_INPUT;
        }
        state->retv |= MENU_CUSTOM_ACTION;
        state->quit  = TRUE;
        break;
    }
    case ACCEPT_CUSTOM:
    {
        state->selected_line = UINT32_MAX;
        state->retv          = MENU_CUSTOM_INPUT;
        state->quit          = TRUE;
        break;
    }
    case ACCEPT_ENTRY:
    {
        // If a valid item is selected, return that..
        unsigned int selected = listview_get_selected ( state->list_view );
        state->selected_line = UINT32_MAX;
        if ( selected < state->filtered_lines ) {
            ( state->selected_line ) = state->line_map[selected];
            state->retv              = MENU_OK;
        }
        else {
            // Nothing entered and nothing selected.
            state->retv = MENU_CUSTOM_INPUT;
        }

        state->quit = TRUE;
        break;
    }
    }
}