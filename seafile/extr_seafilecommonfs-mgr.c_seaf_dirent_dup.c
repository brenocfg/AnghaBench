#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* modifier; void* name; } ;
typedef  TYPE_1__ SeafDirent ;

/* Variables and functions */
 TYPE_1__* g_memdup (TYPE_1__*,int) ; 
 void* g_strdup (void*) ; 

SeafDirent *
seaf_dirent_dup (SeafDirent *dent)
{
    SeafDirent *new_dent;

    new_dent = g_memdup (dent, sizeof(SeafDirent));
    new_dent->name = g_strdup(dent->name);
    new_dent->modifier = g_strdup(dent->modifier);

    return new_dent;
}