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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  psz_servbuf ;

/* Variables and functions */
 int NI_NUMERICSERV ; 
 int atoi (char*) ; 
 int getnameinfo (struct sockaddr const*,int,char*,int,char*,int,int) ; 

int vlc_getnameinfo( const struct sockaddr *sa, int salen,
                     char *host, int hostlen, int *portnum, int flags )
{
    char psz_servbuf[6], *psz_serv;
    int i_servlen, i_val;

    flags |= NI_NUMERICSERV;
    if( portnum != NULL )
    {
        psz_serv = psz_servbuf;
        i_servlen = sizeof( psz_servbuf );
    }
    else
    {
        psz_serv = NULL;
        i_servlen = 0;
    }

    i_val = getnameinfo(sa, salen, host, hostlen, psz_serv, i_servlen, flags);

    if( portnum != NULL )
        *portnum = atoi( psz_serv );

    return i_val;
}