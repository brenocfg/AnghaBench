#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hllhdr {int encoding; int /*<<< orphan*/  registers; } ;
struct TYPE_4__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
#define  HLL_DENSE 129 
#define  HLL_SPARSE 128 
 int hllDenseAdd (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int hllSparseAdd (TYPE_1__*,unsigned char*,size_t) ; 

int hllAdd(robj *o, unsigned char *ele, size_t elesize) {
    struct hllhdr *hdr = o->ptr;
    switch(hdr->encoding) {
    case HLL_DENSE: return hllDenseAdd(hdr->registers,ele,elesize);
    case HLL_SPARSE: return hllSparseAdd(o,ele,elesize);
    default: return -1; /* Invalid representation. */
    }
}