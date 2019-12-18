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
struct TYPE_3__ {int* typelib_namehash_segment; int /*<<< orphan*/ ** typelib_segment_data; } ;
typedef  TYPE_1__ msft_typelib_t ;

/* Variables and functions */
 size_t MSFT_SEG_NAME ; 
 int /*<<< orphan*/  strncasecmp (char*,void*,char) ; 

__attribute__((used)) static int ctl2_find_name(
	msft_typelib_t *typelib,   /* [I] The typelib to operate against. */
	char *name)                /* [I] The encoded name to find. */
{
    int offset;
    int *namestruct;

    offset = typelib->typelib_namehash_segment[name[2] & 0x7f];
    while (offset != -1) {
	namestruct = (int *)&typelib->typelib_segment_data[MSFT_SEG_NAME][offset];

	if (!((namestruct[2] ^ *((int *)name)) & 0xffff00ff)) {
	    /* hash codes and lengths match, final test */
	    if (!strncasecmp(name+4, (void *)(namestruct+3), name[0])) break;
	}

	/* move to next item in hash bucket */
	offset = namestruct[1];
    }

    return offset;
}