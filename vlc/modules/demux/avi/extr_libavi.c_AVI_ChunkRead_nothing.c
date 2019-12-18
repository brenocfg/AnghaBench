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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  avi_chunk_t ;

/* Variables and functions */
 int AVI_NextChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AVI_ChunkRead_nothing( stream_t *s, avi_chunk_t *p_chk )
{
    return AVI_NextChunk( s, p_chk );
}