#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct table {scalar_t__ num_rows; scalar_t__ data; } ;
struct record_computersystemproduct {int /*<<< orphan*/  version; int /*<<< orphan*/  vendor; int /*<<< orphan*/  uuid; int /*<<< orphan*/ * skunumber; int /*<<< orphan*/  name; int /*<<< orphan*/  identifyingnumber; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  compsysproduct_identifyingnumberW ; 
 int /*<<< orphan*/  compsysproduct_nameW ; 
 int /*<<< orphan*/  compsysproduct_vendorW ; 
 int /*<<< orphan*/  compsysproduct_versionW ; 
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int /*<<< orphan*/  get_compsysproduct_uuid () ; 
 int /*<<< orphan*/  match_row (struct table*,scalar_t__,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 

__attribute__((used)) static enum fill_status fill_compsysproduct( struct table *table, const struct expr *cond )
{
    struct record_computersystemproduct *rec;
    enum fill_status status = FILL_STATUS_UNFILTERED;
    UINT row = 0;

    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    rec = (struct record_computersystemproduct *)table->data;
    rec->identifyingnumber = compsysproduct_identifyingnumberW;
    rec->name              = compsysproduct_nameW;
    rec->skunumber         = NULL;
    rec->uuid              = get_compsysproduct_uuid();
    rec->vendor            = compsysproduct_vendorW;
    rec->version           = compsysproduct_versionW;
    if (!match_row( table, row, cond, &status )) free_row_values( table, row );
    else row++;

    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}