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
struct TYPE_3__ {int rdSize; int /*<<< orphan*/ * rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  int /*<<< orphan*/  INT16 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  META_SELECTOBJECT ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static BOOL MFDRV_SelectObject( PHYSDEV dev, INT16 index)
{
    METARECORD mr;

    mr.rdSize = sizeof mr / 2;
    mr.rdFunction = META_SELECTOBJECT;
    mr.rdParm[0] = index;

    return MFDRV_WriteRecord( dev, &mr, mr.rdSize*2 );
}