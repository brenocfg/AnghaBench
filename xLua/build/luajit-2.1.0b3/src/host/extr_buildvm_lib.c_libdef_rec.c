#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
 scalar_t__ BUILD_recdef ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 scalar_t__ ffid ; 
 int find_rec (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* funcname ; 
 scalar_t__ recffid ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void libdef_rec(BuildCtx *ctx, char *p, int arg)
{
  UNUSED(arg);
  if (ctx->mode == BUILD_recdef) {
    char *q;
    uint32_t n;
    for (; recffid+1 < ffid; recffid++)
      fprintf(ctx->fp, ",\n0");
    recffid = ffid;
    if (*p == '.') p = funcname;
    q = strchr(p, ' ');
    if (q) *q++ = '\0';
    n = find_rec(p);
    if (q)
      fprintf(ctx->fp, ",\n0x%02x00+(%s)", n, q);
    else
      fprintf(ctx->fp, ",\n0x%02x00", n);
  }
}