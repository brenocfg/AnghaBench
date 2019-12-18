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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  index_record ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GetDWLE (int**) ; 
 int GetQWLE (int**) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UINT64_C (int) ; 
 int fread (int**,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ReadIndexRecord( FILE *p_file, bool b_ts, int64_t i_frame,
                            uint64_t *pi_offset, uint16_t *pi_file_num )
{
    uint8_t index_record[8];
    if( fseek( p_file, sizeof(index_record) * i_frame, SEEK_SET ) != 0 )
        return false;
    if( fread( &index_record, sizeof(index_record), 1, p_file ) < 1 )
        return false;

    /* VDR usually (only?) runs on little endian machines, but VLC has a
     * broader audience. See recording.* in VDR source for data layout. */
    if( b_ts )
    {
        uint64_t i_index_entry = GetQWLE( &index_record );
        *pi_offset = i_index_entry & UINT64_C(0xFFFFFFFFFF);
        *pi_file_num = i_index_entry >> 48;
    }
    else
    {
        *pi_offset = GetDWLE( &index_record );
        *pi_file_num = index_record[5];
    }

    return true;
}