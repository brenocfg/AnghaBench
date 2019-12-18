#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int mode; char* outname; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BuildCtx ;

/* Variables and functions */
#define  BUILD_bcdef 138 
#define  BUILD_coffasm 137 
#define  BUILD_elfasm 136 
#define  BUILD_ffdef 135 
#define  BUILD_folddef 134 
#define  BUILD_libdef 133 
#define  BUILD_machasm 132 
#define  BUILD_peobj 131 
#define  BUILD_raw 130 
#define  BUILD_recdef 129 
#define  BUILD_vmdef 128 
 int LJ_32 ; 
 int LJ_64 ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int build_code (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_asm (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_asm_debug (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_bcdef (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_fold (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_lib (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_peobj (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_raw (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_vmdef (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  parseargs (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
  BuildCtx ctx_;
  BuildCtx *ctx = &ctx_;
  int status, binmode;

  if (sizeof(void *) != 4*LJ_32+8*LJ_64) {
    fprintf(stderr,"Error: pointer size mismatch in cross-build.\n");
    fprintf(stderr,"Try: make HOST_CC=\"gcc -m32\" CROSS=...\n\n");
    return 1;
  }

  UNUSED(argc);
  parseargs(ctx, argv);

  if ((status = build_code(ctx))) {
    fprintf(stderr,"Error: DASM error %08x\n", status);
    return 1;
  }

  switch (ctx->mode) {
  case BUILD_peobj:
  case BUILD_raw:
    binmode = 1;
    break;
  default:
    binmode = 0;
    break;
  }

  if (ctx->outname[0] == '-' && ctx->outname[1] == '\0') {
    ctx->fp = stdout;
#if defined(_WIN32)
    if (binmode)
      _setmode(_fileno(stdout), _O_BINARY);  /* Yuck. */
#endif
  } else if (!(ctx->fp = fopen(ctx->outname, binmode ? "wb" : "w"))) {
    fprintf(stderr, "Error: cannot open output file '%s': %s\n",
	    ctx->outname, strerror(errno));
    exit(1);
  }

  switch (ctx->mode) {
  case BUILD_elfasm:
  case BUILD_coffasm:
  case BUILD_machasm:
    emit_asm(ctx);
    emit_asm_debug(ctx);
    break;
  case BUILD_peobj:
    emit_peobj(ctx);
    break;
  case BUILD_raw:
    emit_raw(ctx);
    break;
  case BUILD_bcdef:
    emit_bcdef(ctx);
    emit_lib(ctx);
    break;
  case BUILD_vmdef:
    emit_vmdef(ctx);
    emit_lib(ctx);
    fprintf(ctx->fp, "}\n\n");
    break;
  case BUILD_ffdef:
  case BUILD_libdef:
  case BUILD_recdef:
    emit_lib(ctx);
    break;
  case BUILD_folddef:
    emit_fold(ctx);
    break;
  default:
    break;
  }

  fflush(ctx->fp);
  if (ferror(ctx->fp)) {
    fprintf(stderr, "Error: cannot write to output file: %s\n",
	    strerror(errno));
    exit(1);
  }
  fclose(ctx->fp);

  return 0;
}