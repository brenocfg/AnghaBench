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
typedef  int uint32_t ;
struct socket {scalar_t__ protocol; int sending; } ;

/* Variables and functions */
 scalar_t__ ATOM_CAS (int*,int,int) ; 
 int ID_TAG16 (int) ; 
 scalar_t__ PROTOCOL_TCP ; 

__attribute__((used)) static inline void
inc_sending_ref(struct socket *s, int id) {
	if (s->protocol != PROTOCOL_TCP)
		return;
	for (;;) {
		uint32_t sending = s->sending;
		if ((sending >> 16) == ID_TAG16(id)) {
			if ((sending & 0xffff) == 0xffff) {
				// s->sending may overflow (rarely), so busy waiting here for socket thread dec it. see issue #794
				continue;
			}
			// inc sending only matching the same socket id
			if (ATOM_CAS(&s->sending, sending, sending + 1))
				return;
			// atom inc failed, retry
		} else {
			// socket id changed, just return
			return;
		}
	}
}