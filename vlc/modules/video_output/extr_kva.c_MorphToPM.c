#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pib_ultype; } ;
typedef  TYPE_1__* PPIB ;

/* Variables and functions */
 int /*<<< orphan*/  DosGetInfoBlocks (int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static void MorphToPM( void )
{
    PPIB pib;

    DosGetInfoBlocks(NULL, &pib);

    /* Change flag from VIO to PM */
    if (pib->pib_ultype == 2)
        pib->pib_ultype = 3;
}