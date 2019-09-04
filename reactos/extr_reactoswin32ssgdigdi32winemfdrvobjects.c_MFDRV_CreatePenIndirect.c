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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int rdSize; int /*<<< orphan*/  rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  int /*<<< orphan*/  LOGPEN16 ;
typedef  int /*<<< orphan*/  HPEN ;

/* Variables and functions */
 int /*<<< orphan*/  META_CREATEPENINDIRECT ; 
 int /*<<< orphan*/  MFDRV_AddHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static UINT16 MFDRV_CreatePenIndirect(PHYSDEV dev, HPEN hPen, LOGPEN16 *logpen)
{
    char buffer[sizeof(METARECORD) - 2 + sizeof(*logpen)];
    METARECORD *mr = (METARECORD *)&buffer;

    mr->rdSize = (sizeof(METARECORD) + sizeof(*logpen) - 2) / 2;
    mr->rdFunction = META_CREATEPENINDIRECT;
    memcpy(&(mr->rdParm), logpen, sizeof(*logpen));
    if (!(MFDRV_WriteRecord( dev, mr, mr->rdSize * 2)))
        return 0;
    return MFDRV_AddHandle( dev, hPen );
}