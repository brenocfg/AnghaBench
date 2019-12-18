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
typedef  size_t ConnectionType ;
typedef  int /*<<< orphan*/  ConnOps ;

/* Variables and functions */
 size_t _CONNECTION_MAX ; 
 int /*<<< orphan*/ ** conn_ops ; 

int
ts_connection_register(ConnectionType type, ConnOps *ops)
{
	if (type == _CONNECTION_MAX)
		return -1;

	conn_ops[type] = ops;

	return 0;
}