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
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void messages_callback_handler( void *p_opaque, const char *psz_message )
{
    decoder_t *p_dec = ( decoder_t * ) p_opaque;
    msg_Dbg( p_dec, "%s", psz_message );
}