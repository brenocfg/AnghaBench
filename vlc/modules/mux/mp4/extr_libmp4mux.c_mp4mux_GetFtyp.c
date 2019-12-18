#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int i_size; int /*<<< orphan*/ * p_elems; } ;
struct TYPE_14__ {TYPE_1__ extra; int /*<<< orphan*/  i_minor; int /*<<< orphan*/  i_major; } ;
struct TYPE_15__ {TYPE_2__ brands; } ;
typedef  TYPE_3__ mp4mux_handle_t ;
struct TYPE_16__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_4__ bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_32be (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_fourcc (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bo_size (TYPE_4__*) ; 
 int /*<<< orphan*/  box_fix (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* box_new (char*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 

bo_t *mp4mux_GetFtyp(const mp4mux_handle_t *h)
{
    bo_t *box = box_new("ftyp");
    if(box)
    {
        bo_add_fourcc(box, &h->brands.i_major);
        bo_add_32be  (box, h->brands.i_minor);
        for(int i=0; i<h->brands.extra.i_size; i++)
            bo_add_fourcc(box, &h->brands.extra.p_elems[i]);
        if(!box->b)
        {
            free(box);
            return NULL;
        }
        box_fix(box, bo_size(box));
    }
    return box;
}