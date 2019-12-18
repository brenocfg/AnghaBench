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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct utf8_data {int member_1; int member_2; int member_3; int /*<<< orphan*/ * data; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct utf8_data*,struct utf8_data const*,int) ; 

void
utf8_set(struct utf8_data *ud, u_char ch)
{
	static const struct utf8_data empty = { { 0 }, 1, 1, 1 };

	memcpy(ud, &empty, sizeof *ud);
	*ud->data = ch;
}