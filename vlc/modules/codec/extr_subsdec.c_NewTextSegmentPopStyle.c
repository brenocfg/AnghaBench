#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text_style_t ;
struct TYPE_8__ {struct TYPE_8__* p_next; int /*<<< orphan*/ * style; } ;
typedef  TYPE_1__ text_segment_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_style; } ;
typedef  TYPE_2__ style_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  PopStyle (TYPE_2__**) ; 
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 TYPE_1__* text_segment_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * text_style_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * text_style_Duplicate (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static text_segment_t* NewTextSegmentPopStyle( text_segment_t* p_segment, style_stack_t** pp_stack )
{
    text_segment_t* p_new = text_segment_New( NULL );
    if ( unlikely( p_new == NULL ) )
        return NULL;
    // We shouldn't have an empty stack since this happens when closing a tag,
    // but better be safe than sorry if (/when) we encounter a broken subtitle file.
    PopStyle( pp_stack );
    text_style_t* p_dup = ( *pp_stack ) ? text_style_Duplicate( (*pp_stack)->p_style ) : text_style_Create( STYLE_NO_DEFAULTS );
    p_new->style = p_dup;
    p_segment->p_next = p_new;
    return p_new;
}