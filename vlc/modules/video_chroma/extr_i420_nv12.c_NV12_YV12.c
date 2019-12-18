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
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV12_I420 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_SwapUV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void NV12_YV12( filter_t *p_filter, picture_t *p_src,
                                           picture_t *p_dst )
{
    NV12_I420( p_filter, p_src, p_dst );
    picture_SwapUV( p_dst );
}