#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int MSize ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LUAL_BUFFERSIZE ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 char* lj_buf_tmp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_gc_check (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_str_new (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void io_file_readall(lua_State *L, FILE *fp)
{
  MSize m, n;
  for (m = LUAL_BUFFERSIZE, n = 0; ; m += m) {
    char *buf = lj_buf_tmp(L, m);
    n += (MSize)fread(buf+n, 1, m-n, fp);
    if (n != m) {
      setstrV(L, L->top++, lj_str_new(L, buf, (size_t)n));
      lj_gc_check(L);
      return;
    }
  }
}