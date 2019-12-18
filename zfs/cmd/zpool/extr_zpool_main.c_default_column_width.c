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
struct TYPE_3__ {scalar_t__ cb_literal; } ;
typedef  TYPE_1__ iostat_cbdata_t ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
#define  IOS_DEFAULT 132 
#define  IOS_LATENCY 131 
#define  IOS_L_HISTO 130 
#define  IOS_QUEUES 129 
#define  IOS_RQ_HISTO 128 

__attribute__((used)) static unsigned int
default_column_width(iostat_cbdata_t *cb, enum iostat_type type)
{
	unsigned long column_width = 5; /* Normal niceprint */
	static unsigned long widths[] = {
		/*
		 * Choose some sane default column sizes for printing the
		 * raw numbers.
		 */
		[IOS_DEFAULT] = 15, /* 1PB capacity */
		[IOS_LATENCY] = 10, /* 1B ns = 10sec */
		[IOS_QUEUES] = 6,   /* 1M queue entries */
		[IOS_L_HISTO] = 10, /* 1B ns = 10sec */
		[IOS_RQ_HISTO] = 6, /* 1M queue entries */
	};

	if (cb->cb_literal)
		column_width = widths[type];

	return (column_width);
}