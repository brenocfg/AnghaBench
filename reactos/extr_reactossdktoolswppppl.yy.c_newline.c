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
struct TYPE_2__ {int char_number; int /*<<< orphan*/  line_number; } ;

/* Variables and functions */
 scalar_t__ ncontinuations ; 
 TYPE_1__ pp_status ; 
 int /*<<< orphan*/  put_buffer (char*,int) ; 

__attribute__((used)) static void newline(int dowrite)
{
	pp_status.line_number++;
	pp_status.char_number = 1;

	if(dowrite == -1)
		return;

	ncontinuations++;
	if(dowrite)
	{
		for(;ncontinuations; ncontinuations--)
			put_buffer("\n", 1);
	}
}