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
struct TYPE_9__ {scalar_t__ detail; scalar_t__ state; } ;
typedef  TYPE_1__ xcb_key_press_event_t ;
struct TYPE_10__ {int response_type; } ;
typedef  TYPE_2__ xcb_generic_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ intf_thread_t ;
struct TYPE_12__ {int i_map; TYPE_5__* p_map; int /*<<< orphan*/ * p_connection; } ;
typedef  TYPE_4__ intf_sys_t ;
struct TYPE_13__ {scalar_t__* p_keys; scalar_t__ i_modifier; int /*<<< orphan*/  i_vlc; } ;
typedef  TYPE_5__ hotkey_mapping_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLIN ; 
 int XCB_KEY_PRESS ; 
 scalar_t__ XCB_NO_SYMBOL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 
 int xcb_get_file_descriptor (int /*<<< orphan*/ *) ; 
 TYPE_2__* xcb_poll_for_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *Thread( void *p_data )
{
    intf_thread_t *p_intf = p_data;
    intf_sys_t *p_sys = p_intf->p_sys;
    xcb_connection_t *p_connection = p_sys->p_connection;

    int canc = vlc_savecancel();

    /* */
    xcb_flush( p_connection );

    /* */
    int fd = xcb_get_file_descriptor( p_connection );
    for( ;; )
    {
        /* Wait for x11 event */
        vlc_restorecancel( canc );
        struct pollfd fds = { .fd = fd, .events = POLLIN, };
        if( poll( &fds, 1, -1 ) < 0 )
        {
            if( errno != EINTR )
                break;
            canc = vlc_savecancel();
            continue;
        }
        canc = vlc_savecancel();

        xcb_generic_event_t *p_event;
        while( ( p_event = xcb_poll_for_event( p_connection ) ) )
        {
            if( ( p_event->response_type & 0x7f ) != XCB_KEY_PRESS )
            {
                free( p_event );
                continue;
            }

            xcb_key_press_event_t *e = (xcb_key_press_event_t *)p_event;

            for( int i = 0; i < p_sys->i_map; i++ )
            {
                hotkey_mapping_t *p_map = &p_sys->p_map[i];

                for( int j = 0; p_map->p_keys[j] != XCB_NO_SYMBOL; j++ )
                    if( p_map->p_keys[j] == e->detail &&
                        p_map->i_modifier == e->state )
                    {
                        var_SetInteger( vlc_object_instance(p_intf),
                                        "global-key-pressed", p_map->i_vlc );
                        goto done;
                    }
            }
        done:
            free( p_event );
        }
    }

    return NULL;
}