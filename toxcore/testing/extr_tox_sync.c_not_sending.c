#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ file; } ;

/* Variables and functions */
 size_t NUM_FILE_SENDERS ; 
 TYPE_1__* file_senders ; 

int not_sending()
{
    uint32_t i;

    for (i = 0; i < NUM_FILE_SENDERS; ++i)
        if (file_senders[i].file != 0)
            return 0;

    return 1;
}