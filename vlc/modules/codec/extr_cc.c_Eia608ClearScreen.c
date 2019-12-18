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
 int EIA608_SCREEN_ROWS ; 
 int /*<<< orphan*/  Eia608ClearScreenRow (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void Eia608ClearScreen( eia608_t *h, int i_screen )
{
    for( int i = 0; i < EIA608_SCREEN_ROWS; i++ )
        Eia608ClearScreenRow( h, i_screen, i );
}