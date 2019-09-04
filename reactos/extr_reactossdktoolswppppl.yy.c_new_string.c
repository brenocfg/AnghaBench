#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line_number; } ;

/* Variables and functions */
 TYPE_1__ pp_status ; 
 int /*<<< orphan*/  str_startline ; 
 scalar_t__ strbuf_idx ; 

__attribute__((used)) static void new_string(void)
{
#ifdef DEBUG
	if(strbuf_idx)
		ppy_warning("new_string: strbuf_idx != 0");
#endif
	strbuf_idx = 0;
	str_startline = pp_status.line_number;
}