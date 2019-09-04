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
struct TYPE_6__ {int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  type_id; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_7__ {int ctype; int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  GapFillLocfColumnState ;
typedef  int /*<<< orphan*/  GapFillInterpolateColumnState ;
typedef  int /*<<< orphan*/  GapFillGroupColumnState ;
typedef  int GapFillColumnType ;
typedef  TYPE_2__ GapFillColumnState ;

/* Variables and functions */
#define  DERIVED_COLUMN 131 
#define  GROUP_COLUMN 130 
#define  INTERPOLATE_COLUMN 129 
#define  LOCF_COLUMN 128 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc0 (size_t) ; 

__attribute__((used)) static GapFillColumnState *
gapfill_column_state_create(GapFillColumnType ctype, Oid typeid)
{
	TypeCacheEntry *tce = lookup_type_cache(typeid, 0);
	GapFillColumnState *column;
	size_t size;

	switch (ctype)
	{
		case GROUP_COLUMN:
		case DERIVED_COLUMN:
			size = sizeof(GapFillGroupColumnState);
			break;
		case LOCF_COLUMN:
			size = sizeof(GapFillLocfColumnState);
			break;
		case INTERPOLATE_COLUMN:
			size = sizeof(GapFillInterpolateColumnState);
			break;
		default:
			size = sizeof(GapFillColumnState);
			break;
	}

	column = palloc0(size);
	column->ctype = ctype;
	column->typid = tce->type_id;
	column->typbyval = tce->typbyval;
	column->typlen = tce->typlen;

	return column;
}