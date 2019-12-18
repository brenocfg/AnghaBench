#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_str; int /*<<< orphan*/  p_type; } ;
typedef  TYPE_1__ avi_chunk_STRING_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AVI_ChunkFree_strz( avi_chunk_t *p_chk )
{
    avi_chunk_STRING_t *p_strz = (avi_chunk_STRING_t*)p_chk;
    FREENULL( p_strz->p_type );
    FREENULL( p_strz->p_str );
}