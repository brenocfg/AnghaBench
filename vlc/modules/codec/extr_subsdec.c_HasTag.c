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
struct TYPE_5__ {struct TYPE_5__* psz_tagname; struct TYPE_5__* p_next; } ;
typedef  TYPE_1__ tag_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,TYPE_1__*) ; 

__attribute__((used)) static bool HasTag( tag_stack_t **pp_stack, const char* psz_tagname )
{
    tag_stack_t *p_prev = NULL;
    for ( tag_stack_t* p_current = *pp_stack; p_current; p_current = p_current->p_next )
    {
        if ( !strcasecmp( psz_tagname, p_current->psz_tagname ) )
        {
            if ( p_current == *pp_stack )
            {
                *pp_stack = p_current->p_next;
            }
            else
            {
                p_prev->p_next = p_current->p_next;
            }
            free( p_current->psz_tagname );
            free( p_current );
            return true;
        }
        p_prev = p_current;
    }
    return false;
}