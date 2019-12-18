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
struct TYPE_3__ {int entry_flags; void* lp_ele; int /*<<< orphan*/  lp; int /*<<< orphan*/  value_buf; int /*<<< orphan*/  field_buf; void* master_fields_ptr; } ;
typedef  TYPE_1__ streamIterator ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int STREAM_ITEM_FLAG_SAMEFIELDS ; 
 unsigned char* lpGet (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* lpNext (int /*<<< orphan*/ ,void*) ; 

void streamIteratorGetField(streamIterator *si, unsigned char **fieldptr, unsigned char **valueptr, int64_t *fieldlen, int64_t *valuelen) {
    if (si->entry_flags & STREAM_ITEM_FLAG_SAMEFIELDS) {
        *fieldptr = lpGet(si->master_fields_ptr,fieldlen,si->field_buf);
        si->master_fields_ptr = lpNext(si->lp,si->master_fields_ptr);
    } else {
        *fieldptr = lpGet(si->lp_ele,fieldlen,si->field_buf);
        si->lp_ele = lpNext(si->lp,si->lp_ele);
    }
    *valueptr = lpGet(si->lp_ele,valuelen,si->value_buf);
    si->lp_ele = lpNext(si->lp,si->lp_ele);
}