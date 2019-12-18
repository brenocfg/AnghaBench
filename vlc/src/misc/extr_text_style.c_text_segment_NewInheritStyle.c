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
struct TYPE_5__ {int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  text_segment_Delete (TYPE_1__*) ; 
 TYPE_1__* text_segment_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_style_Duplicate (int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (int) ; 

text_segment_t *text_segment_NewInheritStyle( const text_style_t* p_style )
{
    if ( !p_style )
        return NULL; //FIXME: Allow this, even if it is an alias to text_segment_New( NULL ) ?
    text_segment_t* p_segment = text_segment_New( NULL );
    if ( unlikely( !p_segment ) )
        return NULL;
    p_segment->style = text_style_Duplicate( p_style );
    if ( unlikely( !p_segment->style ) )
    {
        text_segment_Delete( p_segment );
        return NULL;
    }
    return p_segment;
}