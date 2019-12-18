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
 int LONG_SEEK (int /*<<< orphan*/ *,long long,int) ; 
 int fflush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ZSTD_seekable_seek_FILE(void* opaque, long long offset, int origin)
{
    int const ret = LONG_SEEK((FILE*)opaque, offset, origin);
    if (ret) return ret;
    return fflush((FILE*)opaque);
}