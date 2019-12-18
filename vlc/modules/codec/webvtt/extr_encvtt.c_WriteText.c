#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,size_t,char const*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void WriteText( const char *psz, bo_t *box, char *c_last )
{
    /* We need to break any double newline sequence
     * in or over segments */
    while(*psz)
    {
        const char *p = strchr( psz, '\n' );
        if( p )
        {
            bo_add_mem( box, p - psz, psz );
            if( *c_last == '\n' )
                bo_add_8( box, '!' ); /* Add space */
            bo_add_8( box, '\n' );
            *c_last = '\n';
            psz = p + 1;
        }
        else
        {
            size_t len = strlen(psz);
            bo_add_mem( box, len, psz );
            *c_last = (len > 0) ? psz[len - 1] : '\0';
            break;
        }
    }
}