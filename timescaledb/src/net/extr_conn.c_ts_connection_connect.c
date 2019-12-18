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
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* connect ) (TYPE_2__*,char const*,char const*,int) ;} ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char const*,char const*,int) ; 

int
ts_connection_connect(Connection *conn, const char *host, const char *servname, int port)
{
/* Windows defines 'connect()' as a macro, so we need to undef it here to use it in ops->connect */
#ifdef WIN32
#undef connect
#endif
	return conn->ops->connect(conn, host, servname, port);
}