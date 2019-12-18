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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int MP4_ReadBoxContainerChildrenIndexed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int MP4_ReadBoxContainerRestricted( stream_t *p_stream, MP4_Box_t *p_container,
                                    const uint32_t stoplist[], const uint32_t excludelist[] )
{
    return MP4_ReadBoxContainerChildrenIndexed( p_stream, p_container,
                                                stoplist, excludelist, false );
}