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
struct TYPE_3__ {char* schemaname; int if_not_exists; int /*<<< orphan*/  schemaElts; int /*<<< orphan*/ * authrole; } ;
typedef  TYPE_1__ CreateSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSchemaCommand (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  NIL ; 

__attribute__((used)) static void
hypertable_create_schema(const char *schema_name)
{
	CreateSchemaStmt stmt = {
		.schemaname = (char *) schema_name,
		.authrole = NULL,
		.schemaElts = NIL,
		.if_not_exists = true,
	};

	CreateSchemaCommand(&stmt,
						"(generated CREATE SCHEMA command)"
#if !PG96
						,
						-1,
						-1
#endif
	);
}