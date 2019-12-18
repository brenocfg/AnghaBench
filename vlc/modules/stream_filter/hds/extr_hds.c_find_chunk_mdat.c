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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ U32_AT (int /*<<< orphan*/ *) ; 
 int U64_AT (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static uint32_t find_chunk_mdat( vlc_object_t* p_this,
                                 uint8_t* chunkdata, uint8_t* chunkdata_end,
                                 uint8_t** mdatptr )
{
    uint8_t* boxname = NULL;
    uint8_t* boxdata = NULL;
    uint64_t boxsize = 0;

    do {
        if( chunkdata_end < chunkdata ||
            chunkdata_end - chunkdata < 8 )
        {
            msg_Err( p_this, "Couldn't find mdat in box 1!" );
            *mdatptr = 0;
            return 0;
        }

        boxsize = (uint64_t)U32_AT( chunkdata );
        chunkdata += 4;

        boxname = chunkdata;
        chunkdata += 4;

        if( boxsize == 1 )
        {
            if( chunkdata_end - chunkdata >= 12 )
            {
                boxsize =  U64_AT(chunkdata);
                chunkdata += 8;
            }
            else
            {
                msg_Err( p_this, "Couldn't find mdat in box 2!");
                *mdatptr = 0;
                return 0;
            }
            boxdata = chunkdata;
            chunkdata += (boxsize - 16);
        }
        else
        {
            boxdata = chunkdata;
            chunkdata += (boxsize - 8);
        }
    } while ( 0 != memcmp( boxname, "mdat", 4 ) );

    *mdatptr = boxdata;

    return chunkdata_end - ((uint8_t*)boxdata);
}