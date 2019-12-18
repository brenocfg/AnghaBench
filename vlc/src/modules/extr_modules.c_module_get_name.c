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
struct TYPE_4__ {char const* psz_longname; char const* psz_shortname; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 char const* module_get_object (TYPE_1__ const*) ; 

const char *module_get_name( const module_t *m, bool long_name )
{
    if( long_name && ( m->psz_longname != NULL) )
        return m->psz_longname;

    if (m->psz_shortname != NULL)
        return m->psz_shortname;
    return module_get_object (m);
}