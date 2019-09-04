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
typedef  scalar_t__ ULONG_PTR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ KiTrap02 ; 
 scalar_t__ KiTrap03Handler ; 
 scalar_t__ KiTrap08 ; 
 scalar_t__ KiTrap09 ; 

__attribute__((used)) static BOOLEAN
KdbpInNmiOrDoubleFaultHandler(
    ULONG_PTR Address)
{
    return (Address > (ULONG_PTR)KiTrap02 && Address < (ULONG_PTR)KiTrap03Handler) ||
           (Address > (ULONG_PTR)KiTrap08 && Address < (ULONG_PTR)KiTrap09);
}