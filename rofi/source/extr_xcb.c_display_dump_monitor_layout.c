#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int monitor_id; char* name; int x; int y; int w; int h; scalar_t__ mw; scalar_t__ mh; scalar_t__ primary; struct TYPE_3__* next; } ;
typedef  TYPE_1__ workarea ;
struct TYPE_4__ {TYPE_1__* monitors; } ;

/* Variables and functions */
 char* color_bold ; 
 char* color_reset ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_2__* xcb ; 

void display_dump_monitor_layout ( void )
{
    int is_term = isatty ( fileno ( stdout ) );
    printf ( "Monitor layout:\n" );
    for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
        printf ( "%s              ID%s: %d", ( is_term ) ? color_bold : "", is_term ? color_reset : "", iter->monitor_id );
        if ( iter->primary ) {
            printf ( " (primary)" );
        }
        printf ( "\n" );
        printf ( "%s            name%s: %s\n", ( is_term ) ? color_bold : "", is_term ? color_reset : "", iter->name );
        printf ( "%s        position%s: %d,%d\n", ( is_term ) ? color_bold : "", is_term ? color_reset : "", iter->x, iter->y );
        printf ( "%s            size%s: %d,%d\n", ( is_term ) ? color_bold : "", is_term ? color_reset : "", iter->w, iter->h );
        if ( iter->mw > 0 && iter->mh > 0 ) {
            printf ( "%s            size%s: %dmm,%dmm  dpi: %.0f,%.0f\n",
                     ( is_term ) ? color_bold : "",
                     is_term ? color_reset : "",
                     iter->mw,
                     iter->mh,
                     iter->w * 25.4 / (double) iter->mw,
                     iter->h * 25.4 / (double) iter->mh
                     );
        }
        printf ( "\n" );
    }
}