#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_column; } ;
struct TYPE_5__ {TYPE_1__ cursor; } ;
typedef  TYPE_2__ eia608_t ;

/* Variables and functions */
 int EIA608_SCREEN_COLUMNS ; 

__attribute__((used)) static void Eia608Cursor( eia608_t *h, int dx )
{
    h->cursor.i_column += dx;
    if( h->cursor.i_column < 0 )
        h->cursor.i_column = 0;
    else if( h->cursor.i_column > EIA608_SCREEN_COLUMNS-1 )
        h->cursor.i_column = EIA608_SCREEN_COLUMNS-1;
}