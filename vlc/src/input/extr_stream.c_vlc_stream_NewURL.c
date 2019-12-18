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
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * stream_AccessNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * stream_FilterAutoNew (int /*<<< orphan*/ *) ; 

stream_t *(vlc_stream_NewURL)(vlc_object_t *p_parent, const char *psz_url)
{
    if( !psz_url )
        return NULL;

    stream_t *s = stream_AccessNew( p_parent, NULL, NULL, false, psz_url );
    if( s == NULL )
        msg_Err( p_parent, "no suitable access module for `%s'", psz_url );
    else
        s = stream_FilterAutoNew(s);
    return s;
}