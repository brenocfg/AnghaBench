#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ magic; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ MSIOBJECTHDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 scalar_t__ MSIHANDLE_MAGIC ; 

void msiobj_addref( MSIOBJECTHDR *info )
{
    if( !info )
        return;

    if( info->magic != MSIHANDLE_MAGIC )
    {
        ERR("Invalid handle!\n");
        return;
    }

    InterlockedIncrement(&info->refcount);
}