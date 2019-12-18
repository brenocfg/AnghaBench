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
struct TYPE_3__ {char* psz_path; char* psz_option; int /*<<< orphan*/  psz_host; } ;
typedef  TYPE_1__ vlc_url_t ;

/* Variables and functions */
 int asprintf (char**,char*,int /*<<< orphan*/ ,char*,char*,char const*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
vlc_smb2_get_url(vlc_url_t *url, const char *file)
{
    /* smb2://<psz_host><psz_path><file>?<psz_option> */
    char *buf;
    if (asprintf(&buf, "smb://%s%s%s%s%s%s", url->psz_host,
                 url->psz_path != NULL ? url->psz_path : "",
                 url->psz_path != NULL && url->psz_path[0] != '\0' &&
                 url->psz_path[strlen(url->psz_path) - 1] != '/' ? "/" : "",
                 file,
                 url->psz_option != NULL ? "?" : "",
                 url->psz_option != NULL ? url->psz_option : "") == -1)
        return NULL;
    else
        return buf;
}