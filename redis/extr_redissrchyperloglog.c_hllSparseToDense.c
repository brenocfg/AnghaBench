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
typedef  int /*<<< orphan*/  uint8_t ;
struct hllhdr {scalar_t__ encoding; int /*<<< orphan*/  registers; } ;
typedef  scalar_t__ sds ;
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ HLL_DENSE ; 
 int /*<<< orphan*/  HLL_DENSE_SET_REGISTER (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HLL_DENSE_SIZE ; 
 int /*<<< orphan*/  HLL_HDR_SIZE ; 
 int HLL_REGISTERS ; 
 scalar_t__ HLL_SPARSE_IS_XZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ HLL_SPARSE_IS_ZERO (int /*<<< orphan*/ *) ; 
 int HLL_SPARSE_VAL_LEN (int /*<<< orphan*/ *) ; 
 int HLL_SPARSE_VAL_VALUE (int /*<<< orphan*/ *) ; 
 int HLL_SPARSE_XZERO_LEN (int /*<<< orphan*/ *) ; 
 int HLL_SPARSE_ZERO_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int sdslen (scalar_t__) ; 
 scalar_t__ sdsnewlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hllSparseToDense(robj *o) {
    sds sparse = o->ptr, dense;
    struct hllhdr *hdr, *oldhdr = (struct hllhdr*)sparse;
    int idx = 0, runlen, regval;
    uint8_t *p = (uint8_t*)sparse, *end = p+sdslen(sparse);

    /* If the representation is already the right one return ASAP. */
    hdr = (struct hllhdr*) sparse;
    if (hdr->encoding == HLL_DENSE) return C_OK;

    /* Create a string of the right size filled with zero bytes.
     * Note that the cached cardinality is set to 0 as a side effect
     * that is exactly the cardinality of an empty HLL. */
    dense = sdsnewlen(NULL,HLL_DENSE_SIZE);
    hdr = (struct hllhdr*) dense;
    *hdr = *oldhdr; /* This will copy the magic and cached cardinality. */
    hdr->encoding = HLL_DENSE;

    /* Now read the sparse representation and set non-zero registers
     * accordingly. */
    p += HLL_HDR_SIZE;
    while(p < end) {
        if (HLL_SPARSE_IS_ZERO(p)) {
            runlen = HLL_SPARSE_ZERO_LEN(p);
            idx += runlen;
            p++;
        } else if (HLL_SPARSE_IS_XZERO(p)) {
            runlen = HLL_SPARSE_XZERO_LEN(p);
            idx += runlen;
            p += 2;
        } else {
            runlen = HLL_SPARSE_VAL_LEN(p);
            regval = HLL_SPARSE_VAL_VALUE(p);
            if ((runlen + idx) > HLL_REGISTERS) break; /* Overflow. */
            while(runlen--) {
                HLL_DENSE_SET_REGISTER(hdr->registers,idx,regval);
                idx++;
            }
            p++;
        }
    }

    /* If the sparse representation was valid, we expect to find idx
     * set to HLL_REGISTERS. */
    if (idx != HLL_REGISTERS) {
        sdsfree(dense);
        return C_ERR;
    }

    /* Free the old representation and set the new one. */
    sdsfree(o->ptr);
    o->ptr = dense;
    return C_OK;
}