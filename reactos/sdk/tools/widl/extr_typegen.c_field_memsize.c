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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 unsigned int ROUND_SIZE (unsigned int,unsigned int) ; 
 unsigned int type_memsize_and_alignment (int /*<<< orphan*/  const*,unsigned int*) ; 

__attribute__((used)) static unsigned int field_memsize(const type_t *type, unsigned int *offset)
{
    unsigned int align = 0;
    unsigned int size = type_memsize_and_alignment( type, &align );

    *offset = ROUND_SIZE( *offset, align );
    return size;
}