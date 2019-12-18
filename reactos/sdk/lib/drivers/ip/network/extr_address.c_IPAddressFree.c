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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_ADDRESS_TAG ; 

VOID IPAddressFree(
    PVOID Object)
/*
 * FUNCTION: Frees an IP_ADDRESS object
 * ARGUMENTS:
 *     Object = Pointer to an IP address structure
 * RETURNS:
 *     Nothing
 */
{
    ExFreePoolWithTag(Object, IP_ADDRESS_TAG);
}