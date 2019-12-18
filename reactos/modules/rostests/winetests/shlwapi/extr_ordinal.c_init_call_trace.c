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
struct TYPE_3__ {int alloc; int /*<<< orphan*/  calls; scalar_t__ count; } ;
typedef  TYPE_1__ call_trace_t ;
typedef  int /*<<< orphan*/  call_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_call_trace(call_trace_t *ctrace)
{
    ctrace->alloc = 10;
    ctrace->count = 0;
    ctrace->calls = HeapAlloc(GetProcessHeap(), 0, sizeof(call_entry_t) * ctrace->alloc);
}