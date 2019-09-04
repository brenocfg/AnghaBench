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
typedef  size_t UINT ;
struct TYPE_2__ {scalar_t__ id; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  size_t DWORD ;

/* Variables and functions */
 TYPE_1__* cookies ; 
 size_t id_last ; 

LPVOID remove_Cookie(DWORD id)
{
    UINT index = id - 1;

    if (index >= id_last)
        return NULL;

    if (cookies[index].id == 0)
        return NULL;

    cookies[index].id = 0;
    return cookies[index].data;
}