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

/* Variables and functions */
 int OBJECT_COMPRESSED_LZ4 ; 
 int OBJECT_COMPRESSED_XZ ; 
 int compress_blob_lz4 (void const*,int /*<<< orphan*/ ,void*,size_t,size_t*) ; 
 int compress_blob_xz (void const*,int /*<<< orphan*/ ,void*,size_t,size_t*) ; 

__attribute__((used)) static inline int compress_blob(const void *src, uint64_t src_size,
                                void *dst, size_t dst_alloc_size, size_t *dst_size) {
        int r;
#if HAVE_LZ4
        r = compress_blob_lz4(src, src_size, dst, dst_alloc_size, dst_size);
        if (r == 0)
                return OBJECT_COMPRESSED_LZ4;
#else
        r = compress_blob_xz(src, src_size, dst, dst_alloc_size, dst_size);
        if (r == 0)
                return OBJECT_COMPRESSED_XZ;
#endif
        return r;
}