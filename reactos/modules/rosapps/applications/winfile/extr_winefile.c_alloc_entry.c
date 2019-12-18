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
struct TYPE_4__ {scalar_t__ hicon; int /*<<< orphan*/ * folder; int /*<<< orphan*/ * pidl; } ;
typedef  TYPE_1__ Entry ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Entry* alloc_entry(void)
{
	Entry* entry = HeapAlloc(GetProcessHeap(), 0, sizeof(Entry));

	entry->pidl = NULL;
	entry->folder = NULL;
	entry->hicon = 0;

	return entry;
}