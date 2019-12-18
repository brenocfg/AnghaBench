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

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 size_t strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 int /*<<< orphan*/  var_OptionParse (int /*<<< orphan*/ *,char*,int) ; 

int (var_LocationParse)(vlc_object_t *obj, const char *mrl, const char *pref)
{
    int ret = VLC_SUCCESS;
    size_t preflen = strlen (pref) + 1;

    assert(mrl != NULL);
    while (*mrl != '\0')
    {
        mrl += strspn (mrl, ":;"); /* skip leading colon(s) */

        size_t len = strcspn (mrl, ":;");
        char *buf = malloc (preflen + len);

        if (likely(buf != NULL))
        {
            /* NOTE: this does not support the "no-<varname>" bool syntax. */
            /* DO NOT use asprintf() here; it won't work! Think again. */
            snprintf (buf, preflen + len, "%s%s", pref, mrl);
            var_OptionParse (obj, buf, false);
            free (buf);
        }
        else
            ret = VLC_ENOMEM;
        mrl += len;
    }

    return ret;
}