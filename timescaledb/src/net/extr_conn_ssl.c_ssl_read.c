#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ SSLConnection ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int SSL_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ssl_set_error (TYPE_1__*,int) ; 

__attribute__((used)) static ssize_t
ssl_read(Connection *conn, char *buf, size_t buflen)
{
	SSLConnection *sslconn = (SSLConnection *) conn;

	int ret = SSL_read(sslconn->ssl, buf, buflen);

	if (ret < 0)
		ssl_set_error(sslconn, ret);

	return ret;
}