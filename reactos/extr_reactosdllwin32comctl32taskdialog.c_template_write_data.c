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
 int /*<<< orphan*/  memcpy (char*,void const*,unsigned int) ; 

__attribute__((used)) static void template_write_data(char **ptr, const void *src, unsigned int size)
{
    memcpy(*ptr, src, size);
    *ptr += size;
}