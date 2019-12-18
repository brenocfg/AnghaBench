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
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 unsigned int __MIN (int,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 unsigned int bs_read_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_read_ue (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hevc_parse_scaling_list_rbsp( bs_t *p_bs )
{
    if( bs_remain( p_bs ) < 16 )
        return false;

    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<6; j += (i == 3) ? 3 : 1 )
        {
            if( bs_read1( p_bs ) == 0 )
                bs_read_ue( p_bs );
            else
            {
                unsigned nextCoef = 8;
                unsigned coefNum = __MIN( 64, (1 << (4 + (i << 1))));
                if( i > 1 )
                {
                    nextCoef = bs_read_se( p_bs ) + 8;
                }
                for( unsigned k=0; k<coefNum; k++ )
                {
                    nextCoef = ( nextCoef + bs_read_se( p_bs ) + 256 ) % 256;
                }
            }
        }
    }

    return true;
}