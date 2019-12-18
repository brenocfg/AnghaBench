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
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sequence ; 
 scalar_t__ sequence_cnt ; 
 scalar_t__ sequence_size ; 

__attribute__((used)) static void flush_sequence(void)
{
    heap_free(sequence);
    sequence = NULL;
    sequence_cnt = sequence_size = 0;
}