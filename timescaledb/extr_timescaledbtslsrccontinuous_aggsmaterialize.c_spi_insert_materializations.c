#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ TimeRange ;
struct TYPE_11__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * schema; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ SchemaAndName ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * Name ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPI_execute_with_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

__attribute__((used)) static void
spi_insert_materializations(SchemaAndName partial_view, SchemaAndName materialization_table,
							Name time_column_name, TimeRange materialization_range)
{
	int res;
	StringInfo command = makeStringInfo();
	Oid out_fn;
	bool type_is_varlena;
	char *materialization_start;
	char *materialization_end;

	getTypeOutputInfo(materialization_range.type, &out_fn, &type_is_varlena);

	materialization_start = OidOutputFunctionCall(out_fn, materialization_range.start);
	materialization_end = OidOutputFunctionCall(out_fn, materialization_range.end);

	appendStringInfo(command,
					 "INSERT INTO %s.%s SELECT * FROM %s.%s AS I "
					 "WHERE I.%s >= %s AND I.%s < %s;",
					 quote_identifier(NameStr(*materialization_table.schema)),
					 quote_identifier(NameStr(*materialization_table.name)),
					 quote_identifier(NameStr(*partial_view.schema)),
					 quote_identifier(NameStr(*partial_view.name)),
					 quote_identifier(NameStr(*time_column_name)),
					 quote_literal_cstr(materialization_start),
					 quote_identifier(NameStr(*time_column_name)),
					 quote_literal_cstr(materialization_end));

	res = SPI_execute_with_args(command->data,
								0 /*=nargs*/,
								NULL /*=argtypes*/,
								NULL /*=Values*/,
								NULL /*=Nulls*/,
								false /*=read_only*/,
								0 /*count*/
	);
	if (res < 0)
		elog(ERROR, "could materialize values into the materialization table");
}