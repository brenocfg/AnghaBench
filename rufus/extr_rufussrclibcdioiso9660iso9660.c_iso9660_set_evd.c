#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* version; int /*<<< orphan*/  id; void* type; } ;
typedef  TYPE_1__ iso_volume_descriptor_t ;
typedef  int /*<<< orphan*/  ied ;

/* Variables and functions */
 int /*<<< orphan*/  ISO9660_DCHARS ; 
 int ISO_BLOCKSIZE ; 
 int /*<<< orphan*/  ISO_STANDARD_ID ; 
 int /*<<< orphan*/  ISO_VD_END ; 
 int /*<<< orphan*/  ISO_VERSION ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  iso9660_strncpy_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* to_711 (int /*<<< orphan*/ ) ; 

void
iso9660_set_evd(void *pd)
{
  iso_volume_descriptor_t ied;

  cdio_assert (sizeof(iso_volume_descriptor_t) == ISO_BLOCKSIZE);

  cdio_assert (pd != NULL);

  memset(&ied, 0, sizeof(ied));

  ied.type = to_711(ISO_VD_END);
  iso9660_strncpy_pad (ied.id, ISO_STANDARD_ID, sizeof(ied.id),
                       ISO9660_DCHARS);
  ied.version = to_711(ISO_VERSION);

  memcpy(pd, &ied, sizeof(ied));
}