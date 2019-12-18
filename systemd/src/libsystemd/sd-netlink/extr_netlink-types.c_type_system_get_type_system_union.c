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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  NLTypeSystemUnion ;
typedef  int /*<<< orphan*/  NLTypeSystem ;
typedef  int /*<<< orphan*/  NLType ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  type_get_type_system_union (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 
 int type_system_get_type (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

int type_system_get_type_system_union(const NLTypeSystem *type_system, const NLTypeSystemUnion **ret, uint16_t type) {
        const NLType *nl_type;
        int r;

        assert(ret);

        r = type_system_get_type(type_system, &nl_type, type);
        if (r < 0)
                return r;

        type_get_type_system_union(nl_type, ret);
        return 0;
}