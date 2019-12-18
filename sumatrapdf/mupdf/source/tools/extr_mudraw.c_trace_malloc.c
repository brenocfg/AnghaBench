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
struct TYPE_4__ {scalar_t__ current; size_t total; scalar_t__ peak; } ;
typedef  TYPE_1__ trace_info ;
struct TYPE_5__ {size_t size; } ;
typedef  TYPE_2__ trace_header ;

/* Variables and functions */
 TYPE_2__* malloc (size_t) ; 

__attribute__((used)) static void *
trace_malloc(void *arg, size_t size)
{
	trace_info *info = (trace_info *) arg;
	trace_header *p;
	if (size == 0)
		return NULL;
	p = malloc(size + sizeof(trace_header));
	if (p == NULL)
		return NULL;
	p[0].size = size;
	info->current += size;
	info->total += size;
	if (info->current > info->peak)
		info->peak = info->current;
	return (void *)&p[1];
}