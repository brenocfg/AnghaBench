#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  resource; } ;
typedef  TYPE_1__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ * input_resource_HoldDummyVout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_resource_HoldVout (int /*<<< orphan*/ ) ; 

vout_thread_t *
vlc_player_vout_Hold(vlc_player_t *player)
{
    vout_thread_t *vout = input_resource_HoldVout(player->resource);
    return vout ? vout : input_resource_HoldDummyVout(player->resource);
}