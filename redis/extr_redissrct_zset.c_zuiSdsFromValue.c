#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ele; int /*<<< orphan*/  flags; int /*<<< orphan*/  ell; int /*<<< orphan*/  elen; int /*<<< orphan*/ * estr; } ;
typedef  TYPE_1__ zsetopval ;
typedef  int /*<<< orphan*/ * sds ;

/* Variables and functions */
 int /*<<< orphan*/  OPVAL_DIRTY_SDS ; 
 int /*<<< orphan*/ * sdsfromlonglong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdsnewlen (char*,int /*<<< orphan*/ ) ; 

sds zuiSdsFromValue(zsetopval *val) {
    if (val->ele == NULL) {
        if (val->estr != NULL) {
            val->ele = sdsnewlen((char*)val->estr,val->elen);
        } else {
            val->ele = sdsfromlonglong(val->ell);
        }
        val->flags |= OPVAL_DIRTY_SDS;
    }
    return val->ele;
}