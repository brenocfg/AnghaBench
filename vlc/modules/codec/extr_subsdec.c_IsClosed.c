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
 char* strcasestr (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool IsClosed( const char* psz_subtitle, const char* psz_tagname )
{
    const char* psz_tagpos = strcasestr( psz_subtitle, psz_tagname );
    if ( !psz_tagpos )
        return false;
    // Search for '</' and '>' immediatly before & after (minding the potential spaces)
    const char* psz_endtag = psz_tagpos + strlen( psz_tagname );
    while ( *psz_endtag == ' ' )
        psz_endtag++;
    if ( *psz_endtag != '>' )
        return false;
    // Skip back before the tag itself
    psz_tagpos--;
    while ( *psz_tagpos == ' ' && psz_tagpos > psz_subtitle )
        psz_tagpos--;
    if ( *psz_tagpos-- != '/' )
        return false;
    if ( *psz_tagpos != '<' )
        return false;
    return true;
}