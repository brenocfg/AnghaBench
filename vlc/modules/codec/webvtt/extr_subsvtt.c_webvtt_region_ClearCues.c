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
struct TYPE_3__ {int /*<<< orphan*/ * p_child; } ;
typedef  TYPE_1__ webvtt_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  webvtt_domnode_ChainDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void webvtt_region_ClearCues( webvtt_region_t *p_region )
{
    webvtt_domnode_ChainDelete( p_region->p_child );
    p_region->p_child = NULL;
}