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
struct socket_object_interface {int dummy; } ;
struct socket_server {struct socket_object_interface soi; } ;

/* Variables and functions */

void 
socket_server_userobject(struct socket_server *ss, struct socket_object_interface *soi) {
	ss->soi = *soi;
}