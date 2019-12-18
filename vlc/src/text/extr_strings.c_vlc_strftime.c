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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 size_t strftime (char*,size_t,char const*,struct tm*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

char *vlc_strftime( const char *tformat )
{
    time_t curtime;
    struct tm loctime;

    if (strcmp (tformat, "") == 0)
        return strdup (""); /* corner case w.r.t. strftime() return value */

    /* Get the current time.  */
    time( &curtime );

    /* Convert it to local time representation.  */
    localtime_r( &curtime, &loctime );
    for (size_t buflen = strlen (tformat) + 32;; buflen += 32)
    {
        char *str = malloc (buflen);
        if (str == NULL)
            return NULL;

        size_t len = strftime (str, buflen, tformat, &loctime);
        if (len > 0)
        {
            char *ret = realloc (str, len + 1);
            return ret ? ret : str; /* <- this cannot fail */
        }
        free (str);
    }
    vlc_assert_unreachable ();
}