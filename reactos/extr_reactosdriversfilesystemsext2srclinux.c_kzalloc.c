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

/* Variables and functions */
 void* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void *kzalloc(int size, int flags)
{
    void *buffer = kmalloc(size, flags);
    if (buffer) {
        memset(buffer, 0, size);
    }
    return buffer;
}