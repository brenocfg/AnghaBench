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
 int /*<<< orphan*/  CONTROL_CHANNEL_TAG ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID ControlChannelFree(
    PVOID Object)
/*
 * FUNCTION: Frees an address file object
 * ARGUMENTS:
 *     Object = Pointer to address file object to free
 */
{
    ExFreePoolWithTag(Object, CONTROL_CHANNEL_TAG);
}