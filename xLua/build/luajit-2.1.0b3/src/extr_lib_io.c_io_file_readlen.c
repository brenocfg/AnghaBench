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
struct TYPE_9__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_10__ {int /*<<< orphan*/  strempty; } ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 TYPE_7__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  fread (char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* lj_buf_tmp (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_gc_check (TYPE_1__*) ; 
 int /*<<< orphan*/ * lj_str_new (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  setstrV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_file_readlen(lua_State *L, FILE *fp, MSize m)
{
  if (m) {
    char *buf = lj_buf_tmp(L, m);
    MSize n = (MSize)fread(buf, 1, m, fp);
    setstrV(L, L->top++, lj_str_new(L, buf, (size_t)n));
    lj_gc_check(L);
    return (n > 0 || m == 0);
  } else {
    int c = getc(fp);
    ungetc(c, fp);
    setstrV(L, L->top++, &G(L)->strempty);
    return (c != EOF);
  }
}