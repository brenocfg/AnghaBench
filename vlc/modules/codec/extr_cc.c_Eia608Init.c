#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int d1; int d2; } ;
struct TYPE_7__ {scalar_t__ i_row; scalar_t__ i_column; } ;
struct TYPE_9__ {int i_channel; scalar_t__ i_row_rollup; int /*<<< orphan*/  font; int /*<<< orphan*/  color; int /*<<< orphan*/  mode; TYPE_2__ last; TYPE_1__ cursor; scalar_t__ i_screen; } ;
typedef  TYPE_3__ eia608_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIA608_COLOR_DEFAULT ; 
 int /*<<< orphan*/  EIA608_FONT_REGULAR ; 
 int /*<<< orphan*/  EIA608_MODE_POPUP ; 
 scalar_t__ EIA608_SCREEN_ROWS ; 
 int /*<<< orphan*/  Eia608ClearScreen (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Eia608Init( eia608_t *h )
{
    memset( h, 0, sizeof(*h) );

    /* */
    h->i_channel = -1;

    h->i_screen = 0;
    Eia608ClearScreen( h, 0 );
    Eia608ClearScreen( h, 1 );

    /* Cursor for writing text */
    h->cursor.i_column = 0;
    h->cursor.i_row = 0;

    h->last.d1 = 0x00;
    h->last.d2 = 0x00;
    h->mode = EIA608_MODE_POPUP;
    h->color = EIA608_COLOR_DEFAULT;
    h->font = EIA608_FONT_REGULAR;
    h->i_row_rollup = EIA608_SCREEN_ROWS-1;
}