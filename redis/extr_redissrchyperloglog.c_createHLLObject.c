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
typedef  int /*<<< orphan*/  uint8_t ;
struct hllhdr {int /*<<< orphan*/  encoding; int /*<<< orphan*/  magic; } ;
typedef  scalar_t__ sds ;
struct TYPE_4__ {struct hllhdr* ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int HLL_HDR_SIZE ; 
 int HLL_REGISTERS ; 
 int /*<<< orphan*/  HLL_SPARSE ; 
 int HLL_SPARSE_XZERO_MAX_LEN ; 
 int /*<<< orphan*/  HLL_SPARSE_XZERO_SET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 TYPE_1__* createObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sdsnewlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serverAssert (int) ; 

robj *createHLLObject(void) {
    robj *o;
    struct hllhdr *hdr;
    sds s;
    uint8_t *p;
    int sparselen = HLL_HDR_SIZE +
                    (((HLL_REGISTERS+(HLL_SPARSE_XZERO_MAX_LEN-1)) /
                     HLL_SPARSE_XZERO_MAX_LEN)*2);
    int aux;

    /* Populate the sparse representation with as many XZERO opcodes as
     * needed to represent all the registers. */
    aux = HLL_REGISTERS;
    s = sdsnewlen(NULL,sparselen);
    p = (uint8_t*)s + HLL_HDR_SIZE;
    while(aux) {
        int xzero = HLL_SPARSE_XZERO_MAX_LEN;
        if (xzero > aux) xzero = aux;
        HLL_SPARSE_XZERO_SET(p,xzero);
        p += 2;
        aux -= xzero;
    }
    serverAssert((p-(uint8_t*)s) == sparselen);

    /* Create the actual object. */
    o = createObject(OBJ_STRING,s);
    hdr = o->ptr;
    memcpy(hdr->magic,"HYLL",4);
    hdr->encoding = HLL_SPARSE;
    return o;
}