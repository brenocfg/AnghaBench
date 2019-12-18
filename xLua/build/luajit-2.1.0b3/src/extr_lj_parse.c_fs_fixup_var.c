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
typedef  char uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  varinfo; int /*<<< orphan*/  uvinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbufB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fs_fixup_var(LexState *ls, GCproto *pt, uint8_t *p, size_t ofsvar)
{
  setmref(pt->uvinfo, p);
  setmref(pt->varinfo, (char *)p + ofsvar);
  memcpy(p, sbufB(&ls->sb), sbuflen(&ls->sb));  /* Copy from temp. buffer. */
}