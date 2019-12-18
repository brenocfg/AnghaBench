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
typedef  int /*<<< orphan*/  Jbig2Allocator ;

/* Variables and functions */
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *
jbig2_default_realloc(Jbig2Allocator *allocator, void *p, size_t size)
{
    return realloc(p, size);
}