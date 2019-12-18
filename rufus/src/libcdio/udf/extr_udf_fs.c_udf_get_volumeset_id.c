#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pvd_lba; } ;
typedef  TYPE_1__ udf_t ;
struct TYPE_6__ {int /*<<< orphan*/  volset_id; } ;
typedef  TYPE_2__ udf_pvd_t ;

/* Variables and functions */
 scalar_t__ DRIVER_OP_SUCCESS ; 
 int UDF_BLOCKSIZE ; 
 unsigned int UDF_VOLSET_ID_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ udf_read_sectors (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

int
udf_get_volumeset_id(udf_t *p_udf, /*out*/ uint8_t *volsetid,
		     unsigned int i_volsetid)
{
  uint8_t data[UDF_BLOCKSIZE];
  const udf_pvd_t *p_pvd = (udf_pvd_t *) &data;

  /* get primary volume descriptor */
  if ( DRIVER_OP_SUCCESS != udf_read_sectors(p_udf, &data, p_udf->pvd_lba, 1) )
    return 0;

  if (i_volsetid > UDF_VOLSET_ID_SIZE) {
    i_volsetid = UDF_VOLSET_ID_SIZE;
  }

  memcpy(volsetid, p_pvd->volset_id, i_volsetid);

  return UDF_VOLSET_ID_SIZE;
}