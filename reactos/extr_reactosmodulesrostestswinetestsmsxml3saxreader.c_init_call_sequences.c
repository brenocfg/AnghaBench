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
struct call_sequence {int dummy; } ;

/* Variables and functions */
 struct call_sequence* heap_alloc_zero (int) ; 

__attribute__((used)) static void init_call_sequences(struct call_sequence **seq, int n)
{
    int i;

    for (i = 0; i < n; i++)
        seq[i] = heap_alloc_zero(sizeof(struct call_sequence));
}