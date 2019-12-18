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
struct addrinfo {struct addrinfo* ai_canonname; struct addrinfo* ai_addr; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct addrinfo*) ; 

__attribute__((used)) static void resolve_freeaddrinfo(struct addrinfo *ai) {
        while (ai) {
                struct addrinfo *next = ai->ai_next;

                free(ai->ai_addr);
                free(ai->ai_canonname);
                free(ai);
                ai = next;
        }
}