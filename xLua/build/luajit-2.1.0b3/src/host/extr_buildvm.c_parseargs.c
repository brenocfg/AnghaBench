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
struct TYPE_3__ {scalar_t__ mode; char* outname; char** args; } ;
typedef  scalar_t__ BuildMode ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
 scalar_t__ parsemode (char*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void parseargs(BuildCtx *ctx, char **argv)
{
  const char *a;
  int i;
  ctx->mode = (BuildMode)-1;
  ctx->outname = "-";
  for (i = 1; (a = argv[i]) != NULL; i++) {
    if (a[0] != '-')
      break;
    switch (a[1]) {
    case '-':
      if (a[2]) goto err;
      i++;
      goto ok;
    case '\0':
      goto ok;
    case 'm':
      i++;
      if (a[2] || argv[i] == NULL) goto err;
      ctx->mode = parsemode(argv[i]);
      break;
    case 'o':
      i++;
      if (a[2] || argv[i] == NULL) goto err;
      ctx->outname = argv[i];
      break;
    default: err:
      usage();
      break;
    }
  }
ok:
  ctx->args = argv+i;
  if (ctx->mode == (BuildMode)-1) goto err;
}