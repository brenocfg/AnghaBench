#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,char const*,size_t) ;} ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,size_t) ; 

ssize_t
ts_connection_write(Connection *conn, const char *buf, size_t writelen)
{
	return conn->ops->write(conn, buf, writelen);
}