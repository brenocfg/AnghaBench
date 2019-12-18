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
struct TYPE_7__ {int /*<<< orphan*/  e; int /*<<< orphan*/  p; int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ SBuf ;
typedef  scalar_t__ MSize ;

/* Variables and functions */
 scalar_t__ LJ_MIN_SBUF ; 
 scalar_t__ lj_mem_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sbufB (TYPE_1__*) ; 
 int /*<<< orphan*/  sbufL (TYPE_1__*) ; 
 scalar_t__ sbuflen (TYPE_1__*) ; 
 scalar_t__ sbufsz (TYPE_1__*) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void buf_grow(SBuf *sb, MSize sz)
{
  MSize osz = sbufsz(sb), len = sbuflen(sb), nsz = osz;
  char *b;
  if (nsz < LJ_MIN_SBUF) nsz = LJ_MIN_SBUF;
  while (nsz < sz) nsz += nsz;
  b = (char *)lj_mem_realloc(sbufL(sb), sbufB(sb), osz, nsz);
  setmref(sb->b, b);
  setmref(sb->p, b + len);
  setmref(sb->e, b + nsz);
}