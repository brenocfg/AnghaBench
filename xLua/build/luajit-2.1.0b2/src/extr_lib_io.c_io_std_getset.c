#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
struct TYPE_9__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_10__ {int /*<<< orphan*/ * gcroot; } ;

/* Variables and functions */
 TYPE_7__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  IOSTDF_UD (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  gcV (scalar_t__) ; 
 int /*<<< orphan*/  io_file_open (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  io_tofile (TYPE_1__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setudataV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnil (scalar_t__) ; 
 scalar_t__ tvisudata (scalar_t__) ; 

__attribute__((used)) static int io_std_getset(lua_State *L, ptrdiff_t id, const char *mode)
{
  if (L->base < L->top && !tvisnil(L->base)) {
    if (tvisudata(L->base)) {
      io_tofile(L);
      L->top = L->base+1;
    } else {
      io_file_open(L, mode);
    }
    /* NOBARRIER: The standard I/O handles are GC roots. */
    setgcref(G(L)->gcroot[id], gcV(L->top-1));
  } else {
    setudataV(L, L->top++, IOSTDF_UD(L, id));
  }
  return 1;
}