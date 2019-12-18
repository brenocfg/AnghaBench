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
typedef  int /*<<< orphan*/  bo_t ;
typedef  int /*<<< orphan*/  avi_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_BOX_ENTER_LIST (char*) ; 
 int /*<<< orphan*/  AVI_BOX_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avi_HeaderAdd_strf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avi_HeaderAdd_strh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int avi_HeaderAdd_strl( bo_t *p_bo, avi_stream_t *p_stream )
{
    AVI_BOX_ENTER_LIST( "strl" );

    avi_HeaderAdd_strh( p_bo, p_stream );
    avi_HeaderAdd_strf( p_bo, p_stream );

    AVI_BOX_EXIT( 0 );
}