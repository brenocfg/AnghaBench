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
typedef  scalar_t__ int32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {scalar_t__ atttypid; scalar_t__ atttypmod; scalar_t__ attcollation; int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_6__ {int natts; } ;
typedef  scalar_t__ Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (scalar_t__) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ts_make_inh_translation_list(Relation oldrelation, Relation newrelation, Index newvarno,
							 List **translated_vars)
{
	List *vars = NIL;
	TupleDesc old_tupdesc = RelationGetDescr(oldrelation);
	TupleDesc new_tupdesc = RelationGetDescr(newrelation);
	int oldnatts = old_tupdesc->natts;
	int newnatts = new_tupdesc->natts;
	int old_attno;

	for (old_attno = 0; old_attno < oldnatts; old_attno++)
	{
		Form_pg_attribute att;
		char *attname;
		Oid atttypid;
		int32 atttypmod;
		Oid attcollation;
		int new_attno;

		att = TupleDescAttr(old_tupdesc, old_attno);
		if (att->attisdropped)
		{
			/* Just put NULL into this list entry */
			vars = lappend(vars, NULL);
			continue;
		}
		attname = NameStr(att->attname);
		atttypid = att->atttypid;
		atttypmod = att->atttypmod;
		attcollation = att->attcollation;

		/*
		 * When we are generating the "translation list" for the parent table
		 * of an inheritance set, no need to search for matches.
		 */
		if (oldrelation == newrelation)
		{
			vars = lappend(vars,
						   makeVar(newvarno,
								   (AttrNumber)(old_attno + 1),
								   atttypid,
								   atttypmod,
								   attcollation,
								   0));
			continue;
		}

		/*
		 * Otherwise we have to search for the matching column by name.
		 * There's no guarantee it'll have the same column position, because
		 * of cases like ALTER TABLE ADD COLUMN and multiple inheritance.
		 * However, in simple cases it will be the same column number, so try
		 * that before we go groveling through all the columns.
		 *
		 * Note: the test for (att = ...) != NULL cannot fail, it's just a
		 * notational device to include the assignment into the if-clause.
		 */
		if (old_attno < newnatts && (att = TupleDescAttr(new_tupdesc, old_attno)) != NULL &&
			!att->attisdropped && strcmp(attname, NameStr(att->attname)) == 0)
			new_attno = old_attno;
		else
		{
			for (new_attno = 0; new_attno < newnatts; new_attno++)
			{
				att = TupleDescAttr(new_tupdesc, new_attno);
				if (!att->attisdropped && strcmp(attname, NameStr(att->attname)) == 0)
					break;
			}
			if (new_attno >= newnatts)
				elog(ERROR,
					 "could not find inherited attribute \"%s\" of relation \"%s\"",
					 attname,
					 RelationGetRelationName(newrelation));
		}

		/* Found it, check type and collation match */
		if (atttypid != att->atttypid || atttypmod != att->atttypmod)
			elog(ERROR,
				 "attribute \"%s\" of relation \"%s\" does not match parent's type",
				 attname,
				 RelationGetRelationName(newrelation));
		if (attcollation != att->attcollation)
			elog(ERROR,
				 "attribute \"%s\" of relation \"%s\" does not match parent's collation",
				 attname,
				 RelationGetRelationName(newrelation));

		vars = lappend(vars,
					   makeVar(newvarno,
							   (AttrNumber)(new_attno + 1),
							   atttypid,
							   atttypmod,
							   attcollation,
							   0));
	}

	*translated_vars = vars;
}