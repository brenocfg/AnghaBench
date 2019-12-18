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
 int BLUE ; 
 int GREEN ; 
 int RED ; 
 int WHITE ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int getBallColor( vlc_object_t *p_this, char const *psz_newval )
{
    int ret;
    if( !strcmp( psz_newval, "red" ) )
        ret = RED;
    else if( !strcmp( psz_newval, "blue" ) )
        ret = BLUE;
    else if( !strcmp( psz_newval, "green" ) )
        ret = GREEN;
    else if( !strcmp( psz_newval, "white" ) )
        ret = WHITE;
    else
    {
        msg_Err( p_this, "no valid ball color provided (%s)", psz_newval );
        ret = RED;
    }
    return ret;
}