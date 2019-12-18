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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int i_row; int i_column; } ;
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  font; int /*<<< orphan*/  color; TYPE_3__* screen; TYPE_1__ cursor; } ;
typedef  TYPE_2__ eia608_t ;
struct TYPE_9__ {int* row_used; int /*<<< orphan*/ ** fonts; int /*<<< orphan*/ ** colors; int /*<<< orphan*/ ** characters; } ;
typedef  TYPE_3__ eia608_screen ;

/* Variables and functions */
 scalar_t__ EIA608_MODE_TEXT ; 
 int /*<<< orphan*/  Eia608Cursor (TYPE_2__*,int) ; 
 size_t Eia608GetWritingScreenIndex (TYPE_2__*) ; 

__attribute__((used)) static void Eia608Write( eia608_t *h, const uint8_t c )
{
    const int i_row = h->cursor.i_row;
    const int i_column = h->cursor.i_column;
    eia608_screen *screen;

    if( h->mode == EIA608_MODE_TEXT )
        return;

    screen = &h->screen[Eia608GetWritingScreenIndex( h )];

    screen->characters[i_row][i_column] = c;
    screen->colors[i_row][i_column] = h->color;
    screen->fonts[i_row][i_column] = h->font;
    screen->row_used[i_row] = true;
    Eia608Cursor( h, 1 );
}