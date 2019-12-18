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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ node ;
typedef  int /*<<< orphan*/  GraphicsState ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void log_state(GraphicsState data, node ** log)
{
    node * new_entry = HeapAlloc(GetProcessHeap(), 0, sizeof(node));

    new_entry->data = data;
    new_entry->next = *log;
    *log = new_entry;
}