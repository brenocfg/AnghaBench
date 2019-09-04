#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ publisher_id; } ;
struct TYPE_6__ {scalar_t__ publisher_id; } ;
struct TYPE_8__ {TYPE_2__ svd; TYPE_1__ pvd; } ;
typedef  TYPE_3__ iso9660_t ;
typedef  int /*<<< orphan*/  cdio_utf8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_MAX_PUBLISHER_ID ; 
 int get_member_id (TYPE_3__*,int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 

bool iso9660_ifs_get_publisher_id(iso9660_t *p_iso,
                                  /*out*/ cdio_utf8_t **p_psz_publisher_id)
{
  return get_member_id(p_iso, p_psz_publisher_id,
                       (char*)p_iso->pvd.publisher_id,
                       (char*)p_iso->svd.publisher_id,
                       ISO_MAX_PUBLISHER_ID);
}