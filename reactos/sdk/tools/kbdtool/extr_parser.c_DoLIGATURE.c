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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  SkipLines () ; 
 int /*<<< orphan*/  printf (char*) ; 

ULONG
DoLIGATURE(PVOID LigatureData)
{
    printf("LIGATURE support is not yet implemented. Please bug Arch to fix it\n");
    return SkipLines();
}