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
typedef  int /*<<< orphan*/  opj_thread_t ;
typedef  int /*<<< orphan*/  opj_thread_fn ;

/* Variables and functions */

opj_thread_t* opj_thread_create(opj_thread_fn thread_fn, void* user_data)
{
    (void) thread_fn;
    (void) user_data;
    return NULL;
}