#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_3__ {int /*<<< orphan*/  super; int /*<<< orphan*/  field; int /*<<< orphan*/  std; } ;
struct TYPE_4__ {TYPE_1__ idx; } ;
typedef  TYPE_2__ avi_chunk_indx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AVI_ChunkFree_indx( avi_chunk_t *p_chk )
{
    avi_chunk_indx_t *p_indx = (avi_chunk_indx_t*)p_chk;

    FREENULL( p_indx->idx.std );
    FREENULL( p_indx->idx.field );
    FREENULL( p_indx->idx.super );
}