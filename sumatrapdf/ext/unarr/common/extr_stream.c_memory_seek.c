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
struct MemoryStream {size_t offset; size_t length; } ;
typedef  scalar_t__ off64_t ;

/* Variables and functions */
 int SEEK_CUR ; 
 int SEEK_END ; 

__attribute__((used)) static bool memory_seek(void *data, off64_t offset, int origin)
{
    struct MemoryStream *stm = data;
    if (origin == SEEK_CUR)
        offset += stm->offset;
    else if (origin == SEEK_END)
        offset += stm->length;
    if (offset < 0 || offset > (off64_t)stm->length || (size_t)offset > stm->length)
        return false;
    stm->offset = (size_t)offset;
    return true;
}