#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_selection_notify_event_t ;
struct TYPE_12__ {int /*<<< orphan*/  event_y; int /*<<< orphan*/  event_x; } ;
typedef  TYPE_1__ xcb_motion_notify_event_t ;
struct TYPE_13__ {int* keys; } ;
typedef  TYPE_2__ xcb_keymap_notify_event_t ;
struct TYPE_14__ {int /*<<< orphan*/  detail; int /*<<< orphan*/  time; } ;
typedef  TYPE_3__ xcb_key_release_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  detail; int /*<<< orphan*/  state; int /*<<< orphan*/  time; } ;
typedef  TYPE_4__ xcb_key_press_event_t ;
struct TYPE_16__ {int response_type; } ;
typedef  TYPE_5__ xcb_generic_event_t ;
typedef  int /*<<< orphan*/  xcb_configure_notify_event_t ;
struct TYPE_17__ {int /*<<< orphan*/  event; int /*<<< orphan*/  time; int /*<<< orphan*/  detail; } ;
typedef  TYPE_6__ xcb_button_release_event_t ;
struct TYPE_18__ {int /*<<< orphan*/  detail; int /*<<< orphan*/  time; int /*<<< orphan*/  event_y; int /*<<< orphan*/  event_x; } ;
typedef  TYPE_7__ xcb_button_press_event_t ;
typedef  int gint8 ;
typedef  int gint32 ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_19__ {int /*<<< orphan*/  bindings_seat; int /*<<< orphan*/  last_timestamp; int /*<<< orphan*/  mouse_seen; } ;
struct TYPE_11__ {int /*<<< orphan*/  click_to_exit; } ;
typedef  int /*<<< orphan*/  RofiViewState ;
typedef  int /*<<< orphan*/  NkBindingsScrollAxis ;
typedef  int /*<<< orphan*/  NkBindingsMouseButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NK_BINDINGS_BUTTON_STATE_PRESS ; 
 int /*<<< orphan*/  NK_BINDINGS_BUTTON_STATE_RELEASE ; 
 int /*<<< orphan*/  NK_BINDINGS_KEY_STATE_PRESS ; 
 int /*<<< orphan*/  NK_BINDINGS_KEY_STATE_PRESSED ; 
 int /*<<< orphan*/  NK_BINDINGS_KEY_STATE_RELEASE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XCB_BUTTON_PRESS 136 
#define  XCB_BUTTON_RELEASE 135 
#define  XCB_CONFIGURE_NOTIFY 134 
#define  XCB_EXPOSE 133 
#define  XCB_KEYMAP_NOTIFY 132 
#define  XCB_KEY_PRESS 131 
#define  XCB_KEY_RELEASE 130 
#define  XCB_MOTION_NOTIFY 129 
#define  XCB_SELECTION_NOTIFY 128 
 TYPE_10__ config ; 
 int /*<<< orphan*/  nk_bindings_seat_handle_button (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_bindings_seat_handle_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nk_bindings_seat_handle_key_with_modmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_bindings_seat_handle_scroll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rofi_view_frame_callback () ; 
 int /*<<< orphan*/ * rofi_view_get_active () ; 
 int /*<<< orphan*/  rofi_view_handle_mouse_motion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_handle_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_maybe_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_paste (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_temp_click_to_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_temp_configure_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x11_button_to_nk_bindings_button (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x11_button_to_nk_bindings_scroll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_8__* xcb ; 

__attribute__((used)) static void main_loop_x11_event_handler_view ( xcb_generic_event_t *event )
{
    RofiViewState *state = rofi_view_get_active ();
    if ( state == NULL ) {
        return;
    }

    switch ( event->response_type & ~0x80 )
    {
    case XCB_EXPOSE:
        rofi_view_frame_callback ();
        break;
    case XCB_CONFIGURE_NOTIFY:
    {
        xcb_configure_notify_event_t *xce = (xcb_configure_notify_event_t *) event;
        rofi_view_temp_configure_notify ( state, xce );
        break;
    }
    case XCB_MOTION_NOTIFY:
    {
        if ( config.click_to_exit == TRUE ) {
            xcb->mouse_seen = TRUE;
        }
        xcb_motion_notify_event_t *xme = (xcb_motion_notify_event_t *) event;
        rofi_view_handle_mouse_motion ( state, xme->event_x, xme->event_y );
        break;
    }
    case XCB_BUTTON_PRESS:
    {
        xcb_button_press_event_t *bpe = (xcb_button_press_event_t *) event;
        NkBindingsMouseButton    button;
        NkBindingsScrollAxis     axis;
        gint32                   steps;

        xcb->last_timestamp = bpe->time;
        rofi_view_handle_mouse_motion ( state, bpe->event_x, bpe->event_y );
        if ( x11_button_to_nk_bindings_button ( bpe->detail, &button ) ) {
            nk_bindings_seat_handle_button ( xcb->bindings_seat, NULL, button, NK_BINDINGS_BUTTON_STATE_PRESS, bpe->time );
        }
        else if ( x11_button_to_nk_bindings_scroll ( bpe->detail, &axis, &steps ) ) {
            nk_bindings_seat_handle_scroll ( xcb->bindings_seat, NULL, axis, steps );
        }
        break;
    }
    case XCB_BUTTON_RELEASE:
    {
        xcb_button_release_event_t *bre = (xcb_button_release_event_t *) event;
        NkBindingsMouseButton      button;

        xcb->last_timestamp = bre->time;
        if ( x11_button_to_nk_bindings_button ( bre->detail, &button ) ) {
            nk_bindings_seat_handle_button ( xcb->bindings_seat, NULL, button, NK_BINDINGS_BUTTON_STATE_RELEASE, bre->time );
        }
        if ( config.click_to_exit == TRUE ) {
            if ( !xcb->mouse_seen ) {
                rofi_view_temp_click_to_exit ( state, bre->event );
            }
            xcb->mouse_seen = FALSE;
        }
        break;
    }
    // Paste event.
    case XCB_SELECTION_NOTIFY:
        rofi_view_paste ( state, (xcb_selection_notify_event_t *) event );
        break;
    case XCB_KEYMAP_NOTIFY:
    {
        xcb_keymap_notify_event_t *kne = (xcb_keymap_notify_event_t *) event;
        for ( gint32 by = 0; by < 31; ++by ) {
            for ( gint8 bi = 0; bi < 7; ++bi ) {
                if ( kne->keys[by] & ( 1 << bi ) ) {
                    // X11 keycodes starts at 8
                    nk_bindings_seat_handle_key ( xcb->bindings_seat, NULL, ( 8 * by + bi ) + 8, NK_BINDINGS_KEY_STATE_PRESSED );
                }
            }
        }
        break;
    }
    case XCB_KEY_PRESS:
    {
        xcb_key_press_event_t *xkpe = (xcb_key_press_event_t *) event;
        gchar                 *text;

        xcb->last_timestamp = xkpe->time;
        text                = nk_bindings_seat_handle_key_with_modmask ( xcb->bindings_seat, NULL, xkpe->state, xkpe->detail, NK_BINDINGS_KEY_STATE_PRESS );
        if ( text != NULL ) {
            rofi_view_handle_text ( state, text );
        }
        break;
    }
    case XCB_KEY_RELEASE:
    {
        xcb_key_release_event_t *xkre = (xcb_key_release_event_t *) event;
        xcb->last_timestamp = xkre->time;
        nk_bindings_seat_handle_key ( xcb->bindings_seat, NULL, xkre->detail, NK_BINDINGS_KEY_STATE_RELEASE );
        break;
    }
    default:
        break;
    }
    rofi_view_maybe_update ( state );
}