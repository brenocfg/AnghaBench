#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int needsp; int /*<<< orphan*/  cts; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_1__ GCstr ;
typedef  TYPE_2__ CType ;
typedef  TYPE_3__ CTRepr ;
typedef  int /*<<< orphan*/  CTInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ctype_prepc (TYPE_3__*,char) ; 
 int /*<<< orphan*/  ctype_prepnum (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_prepqual (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_prepstr (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_typeid (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* gco2str (scalar_t__) ; 
 scalar_t__ gcref (int /*<<< orphan*/ ) ; 
 char const* strdata (TYPE_1__*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void ctype_preptype(CTRepr *ctr, CType *ct, CTInfo qual, const char *t)
{
  if (gcref(ct->name)) {
    GCstr *str = gco2str(gcref(ct->name));
    ctype_prepstr(ctr, strdata(str), str->len);
  } else {
    if (ctr->needsp) ctype_prepc(ctr, ' ');
    ctype_prepnum(ctr, ctype_typeid(ctr->cts, ct));
    ctr->needsp = 1;
  }
  ctype_prepstr(ctr, t, (MSize)strlen(t));
  ctype_prepqual(ctr, qual);
}