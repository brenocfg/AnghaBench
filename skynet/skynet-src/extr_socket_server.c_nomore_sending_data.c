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
struct socket {int sending; int /*<<< orphan*/ * dw_buffer; } ;

/* Variables and functions */
 scalar_t__ send_buffer_empty (struct socket*) ; 

__attribute__((used)) static inline int
nomore_sending_data(struct socket *s) {
	return send_buffer_empty(s) && s->dw_buffer == NULL && (s->sending & 0xffff) == 0;
}