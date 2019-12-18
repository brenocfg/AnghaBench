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
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  isalpha (char const) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 char* vlc_alloc (size_t,int) ; 

__attribute__((used)) static char* GetTag( const char** ppsz_subtitle, bool b_closing )
{
    const char* psz_subtitle = *ppsz_subtitle;
    if ( *psz_subtitle != '<' )
        return NULL;
    // Skip the '<'
    psz_subtitle++;
    if ( b_closing && *psz_subtitle == '/' )
        psz_subtitle++;
    // Skip potential spaces
    while ( *psz_subtitle == ' ' )
        psz_subtitle++;
    // Now we need to verify if what comes next is a valid tag:
    if ( !isalpha( *psz_subtitle ) )
        return NULL;
    size_t tag_size = 1;
    while ( isalnum( psz_subtitle[tag_size] ) || psz_subtitle[tag_size] == '_' )
        tag_size++;
    char* psz_tagname = vlc_alloc( tag_size + 1, sizeof( *psz_tagname ) );
    if ( unlikely( !psz_tagname ) )
        return NULL;
    strncpy( psz_tagname, psz_subtitle, tag_size );
    psz_tagname[tag_size] = 0;
    psz_subtitle += tag_size;
    *ppsz_subtitle = psz_subtitle;
    return psz_tagname;
}