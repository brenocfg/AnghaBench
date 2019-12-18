#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_screen; } ;
typedef  TYPE_1__ eia608_t ;

/* Variables and functions */
 int /*<<< orphan*/  Eia608ClearScreen (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void Eia608EraseScreen( eia608_t *h, bool b_displayed )
{
    Eia608ClearScreen( h, b_displayed ? h->i_screen : (1-h->i_screen) );
}