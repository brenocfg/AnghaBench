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
typedef  int DWORD ;

/* Variables and functions */
 int htonl (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

__attribute__((used)) static const char *ntoa( DWORD ip )
{
    static char buffer[40];

    ip = htonl(ip);
    sprintf( buffer, "%u.%u.%u.%u", (ip >> 24) & 0xff, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff );
    return buffer;
}