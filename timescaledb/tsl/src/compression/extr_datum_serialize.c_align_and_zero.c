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
typedef  int Size ;

/* Variables and functions */
 scalar_t__ att_align_nominal (char*,char) ; 
 int /*<<< orphan*/  check_allowed_data_len (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline char *
align_and_zero(char *ptr, char type_align, Size *max_size)
{
	char *new_pos = (char *) att_align_nominal(ptr, type_align);
	if (new_pos != ptr)
	{
		Size padding = new_pos - ptr;
		check_allowed_data_len(padding, *max_size);
		memset(ptr, 0, padding);
		*max_size = *max_size - padding;
	}
	return new_pos;
}