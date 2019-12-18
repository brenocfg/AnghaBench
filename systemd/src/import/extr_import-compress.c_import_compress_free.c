#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bzip2; scalar_t__ encoding; int /*<<< orphan*/  gzip; int /*<<< orphan*/  xz; } ;
typedef  TYPE_1__ ImportCompress ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzCompressEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BZ2_bzDecompressEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ IMPORT_COMPRESS_BZIP2 ; 
 scalar_t__ IMPORT_COMPRESS_GZIP ; 
 scalar_t__ IMPORT_COMPRESS_UNKNOWN ; 
 scalar_t__ IMPORT_COMPRESS_XZ ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_end (int /*<<< orphan*/ *) ; 

void import_compress_free(ImportCompress *c) {
        assert(c);

        if (c->type == IMPORT_COMPRESS_XZ)
                lzma_end(&c->xz);
        else if (c->type == IMPORT_COMPRESS_GZIP) {
                if (c->encoding)
                        deflateEnd(&c->gzip);
                else
                        inflateEnd(&c->gzip);
#if HAVE_BZIP2
        } else if (c->type == IMPORT_COMPRESS_BZIP2) {
                if (c->encoding)
                        BZ2_bzCompressEnd(&c->bzip2);
                else
                        BZ2_bzDecompressEnd(&c->bzip2);
#endif
        }

        c->type = IMPORT_COMPRESS_UNKNOWN;
}