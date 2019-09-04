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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  setUnsignedBitfield (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void setSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits, int64_t value) {
    uint64_t uv = value; /* Casting will add UINT64_MAX + 1 if v is negative. */
    setUnsignedBitfield(p,offset,bits,uv);
}