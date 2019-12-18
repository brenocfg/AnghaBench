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
struct lexbuf {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ fz_css_selector ;

/* Variables and functions */
 scalar_t__ accept (struct lexbuf*,char) ; 
 void* parse_selector (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_selector *parse_selector_list(struct lexbuf *buf)
{
	fz_css_selector *head, *tail;

	head = tail = parse_selector(buf);
	while (accept(buf, ','))
	{
		white(buf);
		tail = tail->next = parse_selector(buf);
	}
	return head;
}