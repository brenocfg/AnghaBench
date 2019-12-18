#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* b; } ;
typedef  TYPE_1__ bo_t ;
struct TYPE_11__ {scalar_t__ i_buffer; int /*<<< orphan*/ * p_buffer; } ;

/* Variables and functions */
 TYPE_2__* block_Realloc (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bo_free (TYPE_1__*) ; 
 size_t bo_size (TYPE_1__*) ; 
 int /*<<< orphan*/  box_fix (TYPE_1__*,size_t) ; 
 scalar_t__ likely (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void box_gather (bo_t *box, bo_t *box2)
{
    if(box2 && box2->b && box && box->b)
    {
        box_fix(box2, bo_size( box2 ));
        size_t i_offset = bo_size( box );
        box->b = block_Realloc(box->b, 0, box->b->i_buffer + box2->b->i_buffer);
        if(likely(box->b))
            memcpy(&box->b->p_buffer[i_offset], box2->b->p_buffer, box2->b->i_buffer);
    }
    bo_free(box2);
}