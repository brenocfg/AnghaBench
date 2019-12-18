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
typedef  int /*<<< orphan*/  extension_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TRIGGERMENU ; 
 int PushCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int TriggerMenu( extension_t *p_ext, int i_id )
{
    return PushCommand( p_ext, CMD_TRIGGERMENU, i_id );
}