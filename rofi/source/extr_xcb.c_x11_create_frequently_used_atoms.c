#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  atom; } ;
typedef  TYPE_1__ xcb_intern_atom_reply_t ;
typedef  int /*<<< orphan*/  xcb_intern_atom_cookie_t ;
struct TYPE_6__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int NUM_NETATOMS ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * netatom_names ; 
 int /*<<< orphan*/ * netatoms ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb ; 
 int /*<<< orphan*/  xcb_intern_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_intern_atom_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x11_create_frequently_used_atoms ( void )
{
    // X atom values
    for ( int i = 0; i < NUM_NETATOMS; i++ ) {
        xcb_intern_atom_cookie_t cc = xcb_intern_atom ( xcb->connection, 0, strlen ( netatom_names[i] ), netatom_names[i] );
        xcb_intern_atom_reply_t  *r = xcb_intern_atom_reply ( xcb->connection, cc, NULL );
        if ( r ) {
            netatoms[i] = r->atom;
            free ( r );
        }
    }
}