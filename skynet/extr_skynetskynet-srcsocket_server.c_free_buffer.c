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
struct socket_server {int dummy; } ;
struct send_object {int /*<<< orphan*/  (* free_func ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  send_object_init (struct socket_server*,struct send_object*,void*,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
free_buffer(struct socket_server *ss, const void * buffer, int sz) {
	struct send_object so;
	send_object_init(ss, &so, (void *)buffer, sz);
	so.free_func((void *)buffer);
}