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
struct ctab_constant {int dummy; } ;
struct TYPE_2__ {size_t Constants; } ;
struct ID3DXConstantTableImpl {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 struct ctab_constant* get_constant_by_name (struct ID3DXConstantTableImpl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_from_constant (struct ctab_constant*) ; 
 struct ctab_constant* is_valid_sub_constant (struct ctab_constant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ctab_constant *get_valid_constant(struct ID3DXConstantTableImpl *table, D3DXHANDLE handle)
{
    struct ctab_constant *c;
    UINT i;

    if (!handle) return NULL;

    for (i = 0; i < table->desc.Constants; ++i)
    {
        if (handle_from_constant(&table->constants[i]) == handle)
            return &table->constants[i];

        c = is_valid_sub_constant(&table->constants[i], handle);
        if (c) return c;
    }

    return get_constant_by_name(table, NULL, handle);
}