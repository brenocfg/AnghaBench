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
struct TYPE_2__ {scalar_t__ id; scalar_t__ magic; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_1__* cookies ; 
 unsigned int id_last ; 

DWORD enumerate_Cookie(DWORD magic, DWORD *index)
{
    unsigned int i;
    for (i = *index; i < id_last; i++)
        if (cookies[i].id != 0 && cookies[i].magic == magic)
        {
            *index = (i+1);
            return cookies[i].id;
        }
    return 0x0;
}