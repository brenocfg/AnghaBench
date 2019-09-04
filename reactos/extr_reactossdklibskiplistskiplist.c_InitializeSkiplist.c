#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Next; } ;
struct TYPE_5__ {TYPE_1__ Head; scalar_t__ NodeCount; scalar_t__ MaximumLevel; int /*<<< orphan*/  FreeRoutine; int /*<<< orphan*/  CompareRoutine; int /*<<< orphan*/  AllocateRoutine; } ;
typedef  int /*<<< orphan*/  PSKIPLIST_FREE_ROUTINE ;
typedef  int /*<<< orphan*/  PSKIPLIST_COMPARE_ROUTINE ;
typedef  int /*<<< orphan*/  PSKIPLIST_ALLOCATE_ROUTINE ;
typedef  TYPE_2__* PSKIPLIST ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ ,int) ; 

void
InitializeSkiplist(PSKIPLIST Skiplist, PSKIPLIST_ALLOCATE_ROUTINE AllocateRoutine, PSKIPLIST_COMPARE_ROUTINE CompareRoutine, PSKIPLIST_FREE_ROUTINE FreeRoutine)
{
    // Store the routines.
    Skiplist->AllocateRoutine = AllocateRoutine;
    Skiplist->CompareRoutine = CompareRoutine;
    Skiplist->FreeRoutine = FreeRoutine;

    // Initialize the members and pointers.
    // The Distance array is only used when a node is non-NULL, so it doesn't need initialization.
    Skiplist->MaximumLevel = 0;
    Skiplist->NodeCount = 0;
    ZeroMemory(Skiplist->Head.Next, sizeof(Skiplist->Head.Next));
}