#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  eia608_t ;

/* Variables and functions */
 int /*<<< orphan*/  Eia608ClearScreenRowX (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Eia608ClearScreenRow( eia608_t *h, int i_screen, int i_row )
{
    Eia608ClearScreenRowX( h, i_screen, i_row, 0 );
}