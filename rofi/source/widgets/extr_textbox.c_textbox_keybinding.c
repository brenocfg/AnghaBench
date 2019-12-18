#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int flags; } ;
typedef  TYPE_1__ textbox ;
typedef  int KeyBindingAction ;

/* Variables and functions */
#define  CLEAR_LINE 140 
#define  MOVE_CHAR_BACK 139 
#define  MOVE_CHAR_FORWARD 138 
#define  MOVE_END 137 
#define  MOVE_FRONT 136 
#define  MOVE_WORD_BACK 135 
#define  MOVE_WORD_FORWARD 134 
#define  REMOVE_CHAR_BACK 133 
#define  REMOVE_CHAR_FORWARD 132 
#define  REMOVE_TO_EOL 131 
#define  REMOVE_TO_SOL 130 
#define  REMOVE_WORD_BACK 129 
#define  REMOVE_WORD_FORWARD 128 
 int TB_EDITABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_return_val_if_reached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_cursor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_cursor_bkspc (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_bkspc_word (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_dec (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_dec_word (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_del (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_del_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_del_sol (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_del_word (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_end (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_inc (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_cursor_inc_word (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_text (TYPE_1__*,char*) ; 

int textbox_keybinding ( textbox *tb, KeyBindingAction action )
{
    if ( tb == NULL ) {
        return 0;
    }
    if ( !( tb->flags & TB_EDITABLE ) ) {
        return 0;
    }

    switch ( action )
    {
    // Left or Ctrl-b
    case MOVE_CHAR_BACK:
        return ( textbox_cursor_dec ( tb ) == TRUE ) ? 2 : 0;
    // Right or Ctrl-F
    case MOVE_CHAR_FORWARD:
        return ( textbox_cursor_inc ( tb ) == TRUE ) ? 2 : 0;
    // Ctrl-U: Kill from the beginning to the end of the line.
    case CLEAR_LINE:
        textbox_text ( tb, "" );
        return 1;
    // Ctrl-A
    case MOVE_FRONT:
        textbox_cursor ( tb, 0 );
        return 2;
    // Ctrl-E
    case MOVE_END:
        textbox_cursor_end ( tb );
        return 2;
    // Ctrl-Alt-h
    case REMOVE_WORD_BACK:
        textbox_cursor_bkspc_word ( tb );
        return 1;
    // Ctrl-Alt-d
    case REMOVE_WORD_FORWARD:
        textbox_cursor_del_word ( tb );
        return 1;
    case REMOVE_TO_EOL:
        textbox_cursor_del_eol ( tb );
        return 1;
    case REMOVE_TO_SOL:
        textbox_cursor_del_sol ( tb );
        return 1;
    // Delete or Ctrl-D
    case REMOVE_CHAR_FORWARD:
        textbox_cursor_del ( tb );
        return 1;
    // Alt-B, Ctrl-Left
    case MOVE_WORD_BACK:
        textbox_cursor_dec_word ( tb );
        return 2;
    // Alt-F, Ctrl-Right
    case MOVE_WORD_FORWARD:
        textbox_cursor_inc_word ( tb );
        return 2;
    // BackSpace, Shift-BackSpace, Ctrl-h
    case REMOVE_CHAR_BACK:
        textbox_cursor_bkspc ( tb );
        return 1;
    default:
        g_return_val_if_reached ( 0 );
    }
}