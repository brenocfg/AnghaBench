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
typedef  int /*<<< orphan*/  APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/ * COM_CurrentApt () ; 
 int /*<<< orphan*/  apartment_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apartment_find_mta () ; 

APARTMENT *apartment_get_current_or_mta(void)
{
    APARTMENT *apt = COM_CurrentApt();
    if (apt)
    {
        apartment_addref(apt);
        return apt;
    }
    return apartment_find_mta();
}