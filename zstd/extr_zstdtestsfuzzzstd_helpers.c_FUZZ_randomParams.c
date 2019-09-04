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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_randomCParams (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUZZ_randomFParams (int /*<<< orphan*/ *) ; 

ZSTD_parameters FUZZ_randomParams(size_t srcSize, uint32_t *state)
{
    ZSTD_parameters params;
    params.cParams = FUZZ_randomCParams(srcSize, state);
    params.fParams = FUZZ_randomFParams(state);
    return params;
}