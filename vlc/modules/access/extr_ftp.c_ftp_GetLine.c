#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 char* vlc_tls_GetLine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ftp_GetLine( vlc_object_t *obj, access_sys_t *sys )
{
    char *resp = vlc_tls_GetLine( sys->cmd );
    if( resp == NULL )
        msg_Err( obj, "response failure" );
    return resp;
}