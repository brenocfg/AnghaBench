#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fp; int /*<<< orphan*/  zstrm; int /*<<< orphan*/  flags; int /*<<< orphan*/  rc4_template; int /*<<< orphan*/  (* log ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  TYPE_1__ mm_recover_ctx ;
typedef  int /*<<< orphan*/  (* mm_logfunc ) (int /*<<< orphan*/ ,char*) ;

/* Variables and functions */
 int /*<<< orphan*/  LOGI (char*,char const*) ; 
 int /*<<< orphan*/  LOG_AND_FAIL (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMBAK_FLAG_NO_CIPHER ; 
 int /*<<< orphan*/  MMBAK_LOG_ERROR ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,unsigned char const*) ; 
 int /*<<< orphan*/  dummy_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_header (TYPE_1__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

mm_recover_ctx *mm_recover_init(const char *in_path,
                                const unsigned char *key,
                                int key_len,
                                mm_logfunc logfunc)
{
    if (!logfunc)
        logfunc = dummy_log;

    mm_recover_ctx *ctx = (mm_recover_ctx *) malloc(sizeof(mm_recover_ctx));
    if (!ctx) {
        logfunc(MMBAK_LOG_ERROR, "Memory allocation failed.");
        return NULL;
    }
    memset(ctx, 0, sizeof(mm_recover_ctx));
    ctx->log = logfunc;

    if (key && key_len > 0)
        RC4_set_key(&ctx->rc4_template, key_len, key);
    else
        ctx->flags |= MMBAK_FLAG_NO_CIPHER;

    ctx->fp = fopen(in_path, "rb");
    if (!ctx->fp)
        LOG_AND_FAIL("Cannot open file '%s' for reading: %s", in_path,
                     strerror(errno));

    // read header from dump file.
    if (read_header(ctx) != 0)
        goto bail;

    LOGI("Database recover context initialized. [input: %s]", in_path);
    return ctx;

bail:
    if (ctx) {
        inflateEnd(&ctx->zstrm);
        if (ctx->fp)
            fclose(ctx->fp);
        free(ctx);
    }
    return NULL;
}