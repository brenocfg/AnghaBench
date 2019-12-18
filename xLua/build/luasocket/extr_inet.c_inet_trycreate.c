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
typedef  int /*<<< orphan*/  p_socket ;

/* Variables and functions */
 int /*<<< orphan*/  socket_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 char const* socket_strerror (int /*<<< orphan*/ ) ; 

const char *inet_trycreate(p_socket ps, int family, int type) {
    return socket_strerror(socket_create(ps, family, type, 0));
}