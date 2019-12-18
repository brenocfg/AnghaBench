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
 int EPROTONOSUPPORT ; 
 int decompress_stream_lz4 (int,int,int /*<<< orphan*/ ) ; 
 int decompress_stream_xz (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ endswith (char const*,char*) ; 

int decompress_stream(const char *filename, int fdf, int fdt, uint64_t max_bytes) {

        if (endswith(filename, ".lz4"))
                return decompress_stream_lz4(fdf, fdt, max_bytes);
        else if (endswith(filename, ".xz"))
                return decompress_stream_xz(fdf, fdt, max_bytes);
        else
                return -EPROTONOSUPPORT;
}