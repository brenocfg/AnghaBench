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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
is_headerline(uint8_t *data, size_t size)
{
	size_t i = 0;

	/* test of level 1 header */
	if (data[i] == '=') {
		for (i = 1; i < size && data[i] == '='; i++);
		while (i < size && data[i] == ' ') i++;
		return (i >= size || data[i] == '\n') ? 1 : 0; }

	/* test of level 2 header */
	if (data[i] == '-') {
		for (i = 1; i < size && data[i] == '-'; i++);
		while (i < size && data[i] == ' ') i++;
		return (i >= size || data[i] == '\n') ? 2 : 0; }

	return 0;
}