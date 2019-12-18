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
struct TYPE_4__ {int /*<<< orphan*/ * iconv_u16be; int /*<<< orphan*/ * psz_lang; } ;
typedef  TYPE_1__ atsc_a65_handle_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int strlen (char const*) ; 

atsc_a65_handle_t *atsc_a65_handle_New( const char *psz_lang )
{
    atsc_a65_handle_t *p_handle = malloc( sizeof(*p_handle) );
    if( p_handle )
    {
        if( psz_lang && strlen(psz_lang) > 2 )
            p_handle->psz_lang = strdup( psz_lang );
        else
            p_handle->psz_lang = NULL;

        p_handle->iconv_u16be = NULL;
    }
    return p_handle;
}