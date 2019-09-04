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
struct TYPE_4__ {int /*<<< orphan*/ * palette_map; int /*<<< orphan*/  bDecompress; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT DecompressEnd(CodecInfo *pi)
{
  TRACE("(%p)\n",pi);

  /* pre-condition */
  assert(pi != NULL);

  pi->bDecompress = FALSE;

  if (pi->palette_map != NULL) {
    LocalFree(pi->palette_map);
    pi->palette_map = NULL;
  }

  return ICERR_OK;
}