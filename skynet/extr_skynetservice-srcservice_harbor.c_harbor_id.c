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
struct slave {int fd; } ;
struct harbor {struct slave* s; } ;

/* Variables and functions */
 int REMOTE_MAX ; 

__attribute__((used)) static int
harbor_id(struct harbor *h, int fd) {
	int i;
	for (i=1;i<REMOTE_MAX;i++) {
		struct slave *s = &h->s[i];
		if (s->fd == fd) {
			return i;
		}
	}
	return 0;
}