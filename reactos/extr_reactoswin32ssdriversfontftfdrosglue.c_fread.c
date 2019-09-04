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
 int /*<<< orphan*/  DPRINT1 (char*) ; 

size_t
fread(void *Buffer, size_t Size, size_t Count, FILE *Stream)
{
    DPRINT1("Doubleplus ungood: freetype shouldn't fread!\n");
    return 0;
}