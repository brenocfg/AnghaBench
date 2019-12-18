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
typedef  int /*<<< orphan*/  psz_err_str ;

/* Variables and functions */
 scalar_t__ mdns_strerror (int,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static void
print_error( vlc_object_t *p_obj, const char *psz_what, int i_status )
{
    char psz_err_str[128];

    if( mdns_strerror( i_status, psz_err_str, sizeof(psz_err_str) ) == 0)
        msg_Err( p_obj, "mDNS %s error: %s", psz_what, psz_err_str);
    else
        msg_Err( p_obj, "mDNS %s error: unknown: %d", psz_what, i_status);
}