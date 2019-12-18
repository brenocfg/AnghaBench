#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_column; int /*<<< orphan*/  i_row; } ;
struct TYPE_7__ {scalar_t__ mode; TYPE_1__ cursor; } ;
typedef  TYPE_2__ eia608_t ;

/* Variables and functions */
 scalar_t__ EIA608_MODE_TEXT ; 
 int /*<<< orphan*/  Eia608ClearScreenRowX (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Eia608GetWritingScreenIndex (TYPE_2__*) ; 

__attribute__((used)) static void Eia608EraseToEndOfRow( eia608_t *h )
{
    if( h->mode == EIA608_MODE_TEXT )
        return;

    Eia608ClearScreenRowX( h, Eia608GetWritingScreenIndex( h ), h->cursor.i_row, h->cursor.i_column );
}