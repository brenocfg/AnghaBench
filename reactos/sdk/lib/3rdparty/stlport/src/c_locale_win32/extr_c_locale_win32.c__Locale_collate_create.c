#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _Locale_lcid_t ;
struct TYPE_6__ {int id; } ;
struct TYPE_7__ {TYPE_1__ lc; int /*<<< orphan*/  cp; } ;
typedef  TYPE_2__ _Locale_collate_t ;

/* Variables and functions */
 int INVARIANT_LCID ; 
 int _STLP_LOC_NO_MEMORY ; 
 int _STLP_LOC_UNKNOWN_NAME ; 
 int __GetLCIDFromName (char const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

_Locale_collate_t* _Locale_collate_create(const char * name, _Locale_lcid_t* lc_hint, int *__err_code) {
  _Locale_collate_t *lcol = (_Locale_collate_t*)malloc(sizeof(_Locale_collate_t));
  if (!lcol) { *__err_code = _STLP_LOC_NO_MEMORY; return lcol; }
  memset(lcol, 0, sizeof(_Locale_collate_t));

  if (__GetLCIDFromName(name, &lcol->lc.id, lcol->cp, lc_hint) == -1)
  { free(lcol); *__err_code = _STLP_LOC_UNKNOWN_NAME; return NULL; }

#if defined (__BORLANDC__)
  if ( lcol->lc.id == INVARIANT_LCID && name[0] == 'C' && name[1] == 0 )
  { lcol->lc.id = 0x409; }
#endif

  return lcol;
}