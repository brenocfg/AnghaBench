#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Release (TYPE_1__*) ; 

__attribute__((used)) static void FilterDeletePictures( picture_t *picture )
{
    while( picture )
    {
        picture_t *next = picture->p_next;
        picture_Release( picture );
        picture = next;
    }
}