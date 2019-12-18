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
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    /* TODO: send the ending boundary ("\r\n--"BOUNDARY"--\r\n"),
     * but is the access_output still useable?? */
    msg_Dbg( p_this, "Multipart jpeg muxer closed" );
}