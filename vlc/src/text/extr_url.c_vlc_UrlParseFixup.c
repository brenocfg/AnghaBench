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
struct TYPE_4__ {int /*<<< orphan*/ * psz_path; int /*<<< orphan*/ * psz_pathbuffer; } ;
typedef  TYPE_1__ vlc_url_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int vlc_UrlParseInner (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vlc_uri_component_validate (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * vlc_uri_fixup_inner (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_uri_path_validate (int /*<<< orphan*/ *) ; 

int vlc_UrlParseFixup(vlc_url_t *url, const char *str)
{
    int ret = vlc_UrlParseInner(url, str);

    static const char pathextras[] = "/@:";

    if (url->psz_path != NULL
     && !vlc_uri_component_validate(url->psz_path, pathextras))
    {
        url->psz_pathbuffer = vlc_uri_fixup_inner(url->psz_path, pathextras);
        if (url->psz_pathbuffer == NULL)
        {
            url->psz_path = NULL;
            errno = ENOMEM;
            ret = -1;
        }
        else
        {
            url->psz_path = url->psz_pathbuffer;
            assert(vlc_uri_path_validate(url->psz_path));
        }
    }
    return ret;
}