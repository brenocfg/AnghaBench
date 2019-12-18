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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int EBADMSG ; 
 int OBJECT_COMPRESSED_LZ4 ; 
 int OBJECT_COMPRESSED_XZ ; 
 int decompress_startswith_lz4 (void const*,int /*<<< orphan*/ ,void**,size_t*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int decompress_startswith_xz (void const*,int /*<<< orphan*/ ,void**,size_t*,void const*,size_t,int /*<<< orphan*/ ) ; 

int decompress_startswith(int compression,
                          const void *src, uint64_t src_size,
                          void **buffer, size_t *buffer_size,
                          const void *prefix, size_t prefix_len,
                          uint8_t extra) {
        if (compression == OBJECT_COMPRESSED_XZ)
                return decompress_startswith_xz(src, src_size,
                                                buffer, buffer_size,
                                                prefix, prefix_len,
                                                extra);
        else if (compression == OBJECT_COMPRESSED_LZ4)
                return decompress_startswith_lz4(src, src_size,
                                                 buffer, buffer_size,
                                                 prefix, prefix_len,
                                                 extra);
        else
                return -EBADMSG;
}