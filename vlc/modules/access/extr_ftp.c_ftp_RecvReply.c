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
 char* ftp_GetLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 unsigned int strtoul (char*,char**,int) ; 

__attribute__((used)) static int ftp_RecvReply( vlc_object_t *obj, access_sys_t *sys,
                          char **restrict strp,
                          void (*cb)(void *, const char *), void *opaque )
{
    char *resp = ftp_GetLine( obj, sys );
    if( resp == NULL )
        return -1;

    char *end;
    unsigned code = strtoul( resp, &end, 10 );
    if( (end - resp) != 3 || (*end != '-' && *end != ' ') )
    {
        msg_Err( obj, "malformatted response" );
        goto error;
    }
    msg_Dbg( obj, "received response: \"%s\"", resp );

    if( *end == '-' ) /* Multi-line response */
    {
        bool done;

        *end = ' ';
        do
        {
            char *line = ftp_GetLine( obj, sys );
            if( line == NULL )
                goto error;

            done = !strncmp( resp, line, 4 );
            if( !done )
                cb( opaque, line );
            free( line );
        }
        while( !done );
    }

    if( strp != NULL )
        *strp = resp;
    else
        free( resp );
    return code;
error:
    free( resp );
    return -1;
}