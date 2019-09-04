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
struct TYPE_4__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ iso9660_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_stdio_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

bool
iso9660_close (iso9660_t *p_iso)
{
  if (NULL != p_iso) {
    cdio_stdio_destroy(p_iso->stream);
    p_iso->stream = NULL;
    free(p_iso);
  }
  return true;
}