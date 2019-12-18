#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ p_pic; } ;
typedef  TYPE_1__ logo_t ;
struct TYPE_6__ {unsigned int i_count; TYPE_1__* p_logo; } ;
typedef  TYPE_2__ logo_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 

__attribute__((used)) static void LogoListUnload( logo_list_t *p_list )
{
    for( unsigned i = 0; i < p_list->i_count; i++ )
    {
        logo_t *p_logo = &p_list->p_logo[i];

        if( p_logo->p_pic )
            picture_Release( p_logo->p_pic );
    }
    free( p_list->p_logo );
}