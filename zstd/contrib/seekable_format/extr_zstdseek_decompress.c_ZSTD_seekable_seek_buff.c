#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long pos; unsigned long long size; } ;
typedef  TYPE_1__ buffWrapper_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ZSTD_seekable_seek_buff(void* opaque, long long offset, int origin)
{
    buffWrapper_t* const buff = (buffWrapper_t*) opaque;
    unsigned long long newOffset;
    switch (origin) {
    case SEEK_SET:
        newOffset = offset;
        break;
    case SEEK_CUR:
        newOffset = (unsigned long long)buff->pos + offset;
        break;
    case SEEK_END:
        newOffset = (unsigned long long)buff->size + offset;
        break;
    default:
        assert(0);  /* not possible */
    }
    if (newOffset > buff->size) {
        return -1;
    }
    buff->pos = newOffset;
    return 0;
}