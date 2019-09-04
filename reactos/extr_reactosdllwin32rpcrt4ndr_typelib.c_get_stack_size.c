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
typedef  int /*<<< orphan*/  TYPEDESC ;
typedef  int /*<<< orphan*/  ITypeInfo ;

/* Variables and functions */

__attribute__((used)) static unsigned short get_stack_size(ITypeInfo *typeinfo, TYPEDESC *desc)
{
#if defined(__i386__) || defined(__arm__)
    if (desc->vt == VT_CARRAY)
        return sizeof(void *);
    return (type_memsize(typeinfo, desc) + 3) & ~3;
#else
    return sizeof(void *);
#endif
}