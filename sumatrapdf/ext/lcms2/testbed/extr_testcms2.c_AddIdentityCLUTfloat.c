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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  double cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocCLutFloat (int /*<<< orphan*/ ,int,int,int,double const*) ; 

__attribute__((used)) static
void AddIdentityCLUTfloat(cmsPipeline* lut)
{
    const cmsFloat32Number  Table[] = {

        0,    0,    0,
        0,    0,    1.0,

        0,    1.0,    0,
        0,    1.0,    1.0,

        1.0,    0,    0,
        1.0,    0,    1.0,

        1.0,    1.0,    0,
        1.0,    1.0,    1.0
    };

    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, cmsStageAllocCLutFloat(DbgThread(), 2, 3, 3, Table));
}