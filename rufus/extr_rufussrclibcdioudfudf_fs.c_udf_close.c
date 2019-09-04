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
struct TYPE_4__ {int /*<<< orphan*/  cdio; int /*<<< orphan*/  stream; scalar_t__ b_stream; } ;
typedef  TYPE_1__ udf_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_stdio_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_and_null (TYPE_1__*) ; 

bool
udf_close (udf_t *p_udf)
{
  if (!p_udf) return true;
  if (p_udf->b_stream) {
    cdio_stdio_destroy(p_udf->stream);
  } else {
    cdio_destroy(p_udf->cdio);
  }

  /* Get rid of root directory if allocated. */

  free_and_null(p_udf);
  return true;
}