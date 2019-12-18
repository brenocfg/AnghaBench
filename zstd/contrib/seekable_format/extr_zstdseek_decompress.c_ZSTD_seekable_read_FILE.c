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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ZSTD_seekable_read_FILE(void* opaque, void* buffer, size_t n)
{
    size_t const result = fread(buffer, 1, n, (FILE*)opaque);
    if (result != n) {
        return -1;
    }
    return 0;
}