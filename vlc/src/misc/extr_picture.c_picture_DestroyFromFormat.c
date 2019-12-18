#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ picture_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void picture_DestroyFromFormat(picture_t *pic)
{
    picture_buffer_t *res = pic->p_sys;

    if (res != NULL)
        picture_Deallocate(res->fd, res->base, res->size);
}