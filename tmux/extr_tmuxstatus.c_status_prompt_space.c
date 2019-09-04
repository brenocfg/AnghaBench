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
struct utf8_data {int size; int width; char* data; } ;

/* Variables and functions */

__attribute__((used)) static int
status_prompt_space(const struct utf8_data *ud)
{
	if (ud->size != 1 || ud->width != 1)
		return (0);
	return (*ud->data == ' ');
}