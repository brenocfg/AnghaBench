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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int const*) ; 

__attribute__((used)) static
void AddIdentityCLUT16(cmsPipeline* lut)
{
    const cmsUInt16Number Table[] = {

        0,    0,    0,
        0,    0,    0xffff,

        0,    0xffff,    0,
        0,    0xffff,    0xffff,

        0xffff,    0,    0,
        0xffff,    0,    0xffff,

        0xffff,    0xffff,    0,
        0xffff,    0xffff,    0xffff
    };


    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, cmsStageAllocCLut16bit(DbgThread(), 2, 3, 3, Table));
}