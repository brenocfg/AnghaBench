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
struct decoder_owner {int dummy; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int ModuleThread_PlayVideo (struct decoder_owner*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ModuleThread_UpdateStatVideo (struct decoder_owner*,int) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ModuleThread_QueueVideo( decoder_t *p_dec, picture_t *p_pic )
{
    assert( p_pic );
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    int success = ModuleThread_PlayVideo( p_owner, p_pic );

    ModuleThread_UpdateStatVideo( p_owner, success != VLC_SUCCESS );
}