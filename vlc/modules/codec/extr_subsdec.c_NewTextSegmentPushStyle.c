#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text_style_t ;
struct TYPE_5__ {struct TYPE_5__* p_next; int /*<<< orphan*/ * style; } ;
typedef  TYPE_1__ text_segment_t ;
typedef  int /*<<< orphan*/  style_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DuplicateAndPushStyle (int /*<<< orphan*/ **) ; 
 TYPE_1__* text_segment_New (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static text_segment_t* NewTextSegmentPushStyle( text_segment_t* p_segment, style_stack_t** pp_stack )
{
    text_segment_t* p_new = text_segment_New( NULL );
    if ( unlikely( p_new == NULL ) )
        return NULL;
    text_style_t* p_style = DuplicateAndPushStyle( pp_stack );
    p_new->style = p_style;
    p_segment->p_next = p_new;
    return p_new;
}