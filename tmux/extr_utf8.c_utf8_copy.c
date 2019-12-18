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
typedef  int u_int ;
struct utf8_data {int size; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct utf8_data*,struct utf8_data const*,int) ; 

void
utf8_copy(struct utf8_data *to, const struct utf8_data *from)
{
	u_int	i;

	memcpy(to, from, sizeof *to);

	for (i = to->size; i < sizeof to->data; i++)
		to->data[i] = '\0';
}