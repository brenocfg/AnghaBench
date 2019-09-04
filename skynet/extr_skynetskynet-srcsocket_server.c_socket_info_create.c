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
struct socket_info {struct socket_info* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct socket_info*,int /*<<< orphan*/ ,int) ; 
 struct socket_info* skynet_malloc (int) ; 

struct socket_info *
socket_info_create(struct socket_info *last) {
	struct socket_info *si = skynet_malloc(sizeof(*si));
	memset(si, 0 , sizeof(*si));
	si->next = last;
	return si;
}