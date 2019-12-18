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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmalloc (int /*<<< orphan*/ ) ; 

void script_addr_copy(struct addrinfo *src, struct addrinfo *dst) {
    *dst = *src;
    dst->ai_addr = zmalloc(src->ai_addrlen);
    memcpy(dst->ai_addr, src->ai_addr, src->ai_addrlen);
}