#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ (* init ) (TYPE_2__*) ;} ;
typedef  size_t ConnectionType ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 size_t _CONNECTION_MAX ; 
 int /*<<< orphan*/ * conn_names ; 
 int /*<<< orphan*/ ** conn_ops ; 
 TYPE_2__* connection_internal_create (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

Connection *
ts_connection_create(ConnectionType type)
{
	Connection *conn;

	if (type == _CONNECTION_MAX)
		elog(ERROR, "invalid connection type");

	if (NULL == conn_ops[type])
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("%s connections are not supported", conn_names[type]),
				 errhint("Enable %s support when compiling the extension.", conn_names[type])));

	conn = connection_internal_create(type, conn_ops[type]);

	Assert(NULL != conn);

	if (NULL != conn->ops->init)
		if (conn->ops->init(conn) < 0)
			ereport(ERROR,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("%s connection could not be initialized", conn_names[type])));

	return conn;
}