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
struct buffy {struct buffy* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffy_del (struct buffy*) ; 

__attribute__((used)) static void buffy_del_chain(struct buffy* buf)
{
	while(buf)
	{
		struct buffy* next = buf->next;
		buffy_del(buf);
		buf = next;
	}
}