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

/* Variables and functions */
 int /*<<< orphan*/  AVI_BOX_ENTER (char const*) ; 
 int /*<<< orphan*/  AVI_BOX_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avi_HeaderAdd_meta( bo_t *p_bo, const char psz_meta[4],
                               const char *psz_data )
{
    if ( psz_data == NULL ) return 1;
    const char *psz = psz_data;
    AVI_BOX_ENTER( psz_meta );
    while (*psz) bo_add_8( p_bo, *psz++ );
    bo_add_8( p_bo, 0 );
    AVI_BOX_EXIT( 0 );
}