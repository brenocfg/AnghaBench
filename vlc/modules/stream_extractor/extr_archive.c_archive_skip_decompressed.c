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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_extractor_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int archive_skip_decompressed( stream_extractor_t* p_extractor, uint64_t i_skip )
{
    while( i_skip )
    {
        ssize_t i_read = Read( p_extractor, NULL, i_skip );

        if( i_read < 1 )
            return VLC_EGENERIC;

        i_skip -= i_read;
    }

    return VLC_SUCCESS;
}