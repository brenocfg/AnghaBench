#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type_id; } ;
typedef  TYPE_1__ WithClauseDefinition ;
struct TYPE_9__ {int /*<<< orphan*/  defname; int /*<<< orphan*/  defnamespace; int /*<<< orphan*/ * arg; } ;
struct TYPE_8__ {int /*<<< orphan*/  typname; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_type ;
typedef  TYPE_3__ DefElem ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BOOLOID ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidInputFunctionCall (scalar_t__,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 char* defGetString (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  getTypeInputInfo (scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static Datum
parse_arg(WithClauseDefinition arg, DefElem *def)
{
	char *value;
	Datum val;
	Oid in_fn;
	Oid typIOParam;

	if (!OidIsValid(arg.type_id))
		elog(ERROR, "argument \"%s.%s\" not implemented", def->defnamespace, def->defname);

	if (def->arg != NULL)
		value = defGetString(def);
	else if (arg.type_id == BOOLOID)
		/* for booleans, postgres defines the option timescale.foo to be the same as
		 * timescaledb.foo='true' so if no value is found set it to "true" here */
		value = "true";
	else
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("parameter \"%s.%s\" must have a value", def->defnamespace, def->defname)));

	getTypeInputInfo(arg.type_id, &in_fn, &typIOParam);

	Assert(OidIsValid(in_fn));

	PG_TRY();
	{
		val = OidInputFunctionCall(in_fn, value, typIOParam, -1);
	}
	PG_CATCH();
	{
		Form_pg_type typetup;
		HeapTuple tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(arg.type_id));
		if (!HeapTupleIsValid(tup))
			elog(ERROR,
				 "cache lookup failed for type of %s.%s '%u'",
				 def->defnamespace,
				 def->defname,
				 arg.type_id);

		typetup = (Form_pg_type) GETSTRUCT(tup);

		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid value for %s.%s '%s'", def->defnamespace, def->defname, value),
				 errhint("%s.%s must be a valid %s",
						 def->defnamespace,
						 def->defname,
						 NameStr(typetup->typname))));
	}
	PG_END_TRY();
	return val;
}