#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ZSTD_dParameter ;
struct TYPE_3__ {int lowerBound; int upperBound; int /*<<< orphan*/  error; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ZSTD_bounds ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 int ZSTD_WINDOWLOG_ABSOLUTEMIN ; 
 int ZSTD_WINDOWLOG_MAX ; 
#define  ZSTD_d_format 129 
#define  ZSTD_d_windowLogMax 128 
 scalar_t__ ZSTD_f_zstd1 ; 
 scalar_t__ ZSTD_f_zstd1_magicless ; 
 int /*<<< orphan*/  parameter_unsupported ; 

ZSTD_bounds ZSTD_dParam_getBounds(ZSTD_dParameter dParam)
{
    ZSTD_bounds bounds = { 0, 0, 0 };
    switch(dParam) {
        case ZSTD_d_windowLogMax:
            bounds.lowerBound = ZSTD_WINDOWLOG_ABSOLUTEMIN;
            bounds.upperBound = ZSTD_WINDOWLOG_MAX;
            return bounds;
        case ZSTD_d_format:
            bounds.lowerBound = (int)ZSTD_f_zstd1;
            bounds.upperBound = (int)ZSTD_f_zstd1_magicless;
            ZSTD_STATIC_ASSERT(ZSTD_f_zstd1 < ZSTD_f_zstd1_magicless);
            return bounds;
        default:;
    }
    bounds.error = ERROR(parameter_unsupported);
    return bounds;
}