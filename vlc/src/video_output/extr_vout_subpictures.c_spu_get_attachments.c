#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p; } ;
typedef  TYPE_3__ spu_t ;
typedef  int /*<<< orphan*/  input_attachment_t ;
struct TYPE_6__ {TYPE_3__* sys; } ;
struct TYPE_9__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_7__ {scalar_t__ input; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int input_GetAttachments (scalar_t__,int /*<<< orphan*/ ***) ; 

__attribute__((used)) static int spu_get_attachments(filter_t *filter,
                               input_attachment_t ***attachment_ptr,
                               int *attachment_count)
{
    spu_t *spu = filter->owner.sys;

    if (spu->p->input)
    {
        int count = input_GetAttachments(spu->p->input, attachment_ptr);
        if (count <= 0)
            return VLC_EGENERIC;
        *attachment_count = count;
        return VLC_SUCCESS;
    }

    return VLC_EGENERIC;
}