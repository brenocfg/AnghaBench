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

/* Variables and functions */
 int /*<<< orphan*/  PSZ_NAME_OR_NULL ; 
 int /*<<< orphan*/  PSZ_SHARE_PATH_OR_NULL ; 
 int asprintf (char**,char*,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/  assert (char const*) ; 

__attribute__((used)) static char *smb_get_uri(
                       const char *psz_domain,
                       const char *psz_user, const char *psz_pwd,
                       const char *psz_server, const char *psz_share_path,
                       const char *psz_name)
{
    char *uri;

    assert(psz_server);
#define PSZ_SHARE_PATH_OR_NULL psz_share_path ? psz_share_path : ""
#define PSZ_NAME_OR_NULL psz_name ? "/" : "", psz_name ? psz_name : ""
    if( (psz_user
        ? asprintf( &uri, "smb://%s%s%s%s%s@%s%s%s%s",
                         psz_domain ? psz_domain : "", psz_domain ? ";" : "",
                         psz_user, psz_pwd ? ":" : "",
                         psz_pwd ? psz_pwd : "", psz_server,
                         PSZ_SHARE_PATH_OR_NULL, PSZ_NAME_OR_NULL )
        : asprintf( &uri, "smb://%s%s%s%s", psz_server,
                         PSZ_SHARE_PATH_OR_NULL, PSZ_NAME_OR_NULL )) == -1 )
        uri = NULL;
    return uri;
}