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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  Entry; } ;
typedef  TYPE_1__* PUMA_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 

__attribute__((used)) static VOID FreeUmaDescriptor(PUMA_DESCRIPTOR UmaDesc)
{
    RemoveEntryList(&UmaDesc->Entry);
    RtlFreeHeap(RtlGetProcessHeap(), 0, UmaDesc);
}