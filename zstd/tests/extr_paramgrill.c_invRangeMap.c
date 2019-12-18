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
typedef  size_t varInds_t ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NUM_PARAMS 136 
 int TLEN_RANGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  clog_ind 135 
#define  fadt_ind 134 
#define  hlog_ind 133 
 int /*<<< orphan*/ * maxtable ; 
 scalar_t__* mintable ; 
#define  mml_ind 132 
#define  slog_ind 131 
#define  strt_ind 130 
#define  tlen_ind 129 
 scalar_t__* tlen_table ; 
#define  wlog_ind 128 

__attribute__((used)) static int invRangeMap(varInds_t param, U32 value)
{
    value = MIN(MAX(mintable[param], value), maxtable[param]);
    switch(param) {
        case wlog_ind:
        case clog_ind:
        case hlog_ind:
        case slog_ind:
        case mml_ind:
        case strt_ind:
            return (int)(value - mintable[param]);
        case tlen_ind: /* bin search */
        {
            int lo = 0;
            int hi = TLEN_RANGE;
            while(lo < hi) {
                int mid = (lo + hi) / 2;
                if(tlen_table[mid] < value) {
                    lo = mid + 1;
                } if(tlen_table[mid] == value) {
                    return mid;
                } else {
                    hi = mid;
                }
            }
            return lo;
        }
        case fadt_ind:
            return (int)value + 1;
        case NUM_PARAMS:
        default:;
    }
    DISPLAY("Error, not a valid param\n ");
    assert(0);
    return -2;
}