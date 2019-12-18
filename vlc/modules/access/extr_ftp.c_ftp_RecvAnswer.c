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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int ftp_RecvReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,void (*) (void*,char const*),void*) ; 

__attribute__((used)) static int ftp_RecvAnswer( vlc_object_t *obj, access_sys_t *sys,
                           int *restrict codep, char **restrict strp,
                           void (*cb)(void *, const char *), void *opaque )
{
    char *str;
    int val = ftp_RecvReply( obj, sys, &str, cb, opaque );
    if( (val / 100) == 1 )
    {   /* There can be zero or one preliminary reply per command */
        free( str );
        val = ftp_RecvReply( obj, sys, &str, cb, opaque );
    }

    if( val >= 0 )
    {
        if( codep != NULL )
            *codep = val;
        if( strp != NULL )
            *strp = str;
        else
            free( str );
        val /= 100;
    }
    else
    {
        if( codep != NULL )
            *codep = 500;
        if( strp != NULL )
            *strp = NULL;
    }
    return val;
}