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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  info; scalar_t__ sib; } ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_REDIR ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctype_isxattrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gco2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 char const* strdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *clib_extsym(CTState *cts, CType *ct, GCstr *name)
{
  if (ct->sib) {
    CType *ctf = ctype_get(cts, ct->sib);
    if (ctype_isxattrib(ctf->info, CTA_REDIR))
      return strdata(gco2str(gcref(ctf->name)));
  }
  return strdata(name);
}