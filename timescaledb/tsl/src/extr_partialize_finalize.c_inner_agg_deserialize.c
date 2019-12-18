#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_7__ {int* argnull; int isnull; void** arg; } ;
struct TYPE_6__ {scalar_t__ fn_strict; } ;
struct TYPE_8__ {TYPE_2__ internal_deserialfn_fcinfo; int /*<<< orphan*/  typIOParam; TYPE_2__ deserialfn_fcinfo; TYPE_1__ deserialfn; int /*<<< orphan*/  deserialfnoid; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_2__ FunctionCallInfoData ;
typedef  TYPE_3__ FACombineFnMeta ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 void* Int32GetDatum (int) ; 
 void* ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_VOID () ; 
 void* PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 

__attribute__((used)) static Datum
inner_agg_deserialize(FACombineFnMeta *combine_meta, bytea *serialized_partial,
					  bool serialized_isnull, bool *deserialized_isnull)
{
	Datum deserialized = (Datum) 0;
	FunctionCallInfoData *deser_fcinfo = &combine_meta->deserialfn_fcinfo;
	*deserialized_isnull = true;
	if (OidIsValid(combine_meta->deserialfnoid))
	{
		if (serialized_isnull && combine_meta->deserialfn.fn_strict)
		{
			PG_RETURN_VOID();
			/*don't call the deser function */
		}
		deser_fcinfo->arg[0] = PointerGetDatum(serialized_partial);
		deser_fcinfo->argnull[0] = serialized_isnull;
		combine_meta->deserialfn_fcinfo.isnull = false;
		deserialized = FunctionCallInvoke(deser_fcinfo);
		*deserialized_isnull = deser_fcinfo->isnull;
	}
	else if (!serialized_isnull)
	{
		int32 typmod = -1;
		StringInfo string = makeStringInfo();

		appendBinaryStringInfo(string,
							   VARDATA_ANY(serialized_partial),
							   VARSIZE_ANY_EXHDR(serialized_partial));
		combine_meta->internal_deserialfn_fcinfo.arg[0] = PointerGetDatum(string);
		combine_meta->internal_deserialfn_fcinfo.arg[1] =
			ObjectIdGetDatum(combine_meta->typIOParam);
		combine_meta->internal_deserialfn_fcinfo.arg[2] = Int32GetDatum(typmod);
		combine_meta->internal_deserialfn_fcinfo.argnull[0] = false;
		combine_meta->internal_deserialfn_fcinfo.argnull[1] = false;
		combine_meta->internal_deserialfn_fcinfo.argnull[2] = false;
		combine_meta->internal_deserialfn_fcinfo.isnull = false;

		deserialized = FunctionCallInvoke(&combine_meta->internal_deserialfn_fcinfo);
		*deserialized_isnull = combine_meta->internal_deserialfn_fcinfo.isnull;
	}
	PG_RETURN_DATUM(deserialized);
}