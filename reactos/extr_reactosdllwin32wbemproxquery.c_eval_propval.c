#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct table {TYPE_1__* columns; } ;
struct property {int /*<<< orphan*/  name; } ;
typedef  size_t UINT ;
struct TYPE_2__ {size_t type; } ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 size_t CIM_TYPE_MASK ; 
 scalar_t__ S_OK ; 
 scalar_t__ get_column_index (struct table const*,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ get_value (struct table const*,size_t,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT eval_propval( const struct table *table, UINT row, const struct property *propval,
                             LONGLONG *val, UINT *type )

{
    HRESULT hr;
    UINT column;

    hr = get_column_index( table, propval->name, &column );
    if (hr != S_OK)
        return hr;

    *type = table->columns[column].type & CIM_TYPE_MASK;
    return get_value( table, row, column, val );
}