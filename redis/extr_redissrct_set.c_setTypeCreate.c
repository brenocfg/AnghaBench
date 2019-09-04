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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/ * createIntsetObject () ; 
 int /*<<< orphan*/ * createSetObject () ; 
 scalar_t__ isSdsRepresentableAsLongLong (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

robj *setTypeCreate(sds value) {
    if (isSdsRepresentableAsLongLong(value,NULL) == C_OK)
        return createIntsetObject();
    return createSetObject();
}