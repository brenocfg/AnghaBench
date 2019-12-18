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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  Header ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int HEADER_CLUSTER_BITS (int /*<<< orphan*/  const*) ; 
 int QCOW2_COMPRESSED ; 
 int QCOW2_COPIED ; 
 int QCOW2_ZERO ; 
 int be64toh (int) ; 

__attribute__((used)) static int normalize_offset(
                const Header *header,
                uint64_t p,
                uint64_t *ret,
                bool *compressed,
                uint64_t *compressed_size) {

        uint64_t q;

        q = be64toh(p);

        if (q & QCOW2_COMPRESSED) {
                uint64_t sz, csize_shift, csize_mask;

                if (!compressed)
                        return -EOPNOTSUPP;

                csize_shift = 64 - 2 - (HEADER_CLUSTER_BITS(header) - 8);
                csize_mask = (1ULL << (HEADER_CLUSTER_BITS(header) - 8)) - 1;
                sz = (((q >> csize_shift) & csize_mask) + 1) * 512 - (q & 511);
                q &= ((1ULL << csize_shift) - 1);

                if (compressed_size)
                        *compressed_size = sz;

                *compressed = true;

        } else {
                if (compressed)  {
                        *compressed = false;
                        *compressed_size = 0;
                }

                if (q & QCOW2_ZERO) {
                        /* We make no distinction between zero blocks and holes */
                        *ret = 0;
                        return 0;
                }

                q &= ~QCOW2_COPIED;
        }

        *ret = q;
        return q > 0;  /* returns positive if not a hole */
}