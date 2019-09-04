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
struct socket_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_SERVER ; 
 struct socket_info* socket_server_info (int /*<<< orphan*/ ) ; 

struct socket_info *
skynet_socket_info() {
	return socket_server_info(SOCKET_SERVER);
}