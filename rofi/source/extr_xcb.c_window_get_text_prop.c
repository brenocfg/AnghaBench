#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
struct TYPE_8__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 size_t STRING ; 
 int /*<<< orphan*/  UINT_MAX ; 
 size_t UTF8_STRING ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* g_strdup (char*) ; 
 char* g_strndup (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* netatoms ; 
 char* rofi_latin_to_utf8_strdup (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* xcb ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_get_property_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property_value (TYPE_1__*) ; 
 scalar_t__ xcb_get_property_value_length (TYPE_1__*) ; 

char* window_get_text_prop ( xcb_window_t w, xcb_atom_t atom )
{
    xcb_get_property_cookie_t c  = xcb_get_property ( xcb->connection, 0, w, atom, XCB_GET_PROPERTY_TYPE_ANY, 0, UINT_MAX );
    xcb_get_property_reply_t  *r = xcb_get_property_reply ( xcb->connection, c, NULL );
    if ( r ) {
        if ( xcb_get_property_value_length ( r ) > 0 ) {
            char *str = NULL;
            if ( r->type == netatoms[UTF8_STRING] ) {
                str = g_strndup ( xcb_get_property_value ( r ), xcb_get_property_value_length ( r ) );
            }
            else if ( r->type == netatoms[STRING] ) {
                str = rofi_latin_to_utf8_strdup ( xcb_get_property_value ( r ), xcb_get_property_value_length ( r ) );
            }
            else {
                str = g_strdup ( "Invalid encoding." );
            }

            free ( r );
            return str;
        }
        free ( r );
    }
    return NULL;
}