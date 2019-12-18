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
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {int type; int encoding; int /*<<< orphan*/  bzip2; int /*<<< orphan*/  gzip; int /*<<< orphan*/  xz; } ;
typedef  int ImportCompressType ;
typedef  TYPE_1__ ImportCompress ;

/* Variables and functions */
 int BZ2_bzCompressInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  IMPORT_COMPRESS_BZIP2 131 
#define  IMPORT_COMPRESS_GZIP 130 
#define  IMPORT_COMPRESS_UNCOMPRESSED 129 
#define  IMPORT_COMPRESS_XZ 128 
 int /*<<< orphan*/  LZMA_CHECK_CRC64 ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_PRESET_DEFAULT ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int Z_OK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int deflateInit2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_easy_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int import_compress_init(ImportCompress *c, ImportCompressType t) {
        int r;

        assert(c);

        switch (t) {

        case IMPORT_COMPRESS_XZ: {
                lzma_ret xzr;

                xzr = lzma_easy_encoder(&c->xz, LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64);
                if (xzr != LZMA_OK)
                        return -EIO;

                c->type = IMPORT_COMPRESS_XZ;
                break;
        }

        case IMPORT_COMPRESS_GZIP:
                r = deflateInit2(&c->gzip, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY);
                if (r != Z_OK)
                        return -EIO;

                c->type = IMPORT_COMPRESS_GZIP;
                break;

#if HAVE_BZIP2
        case IMPORT_COMPRESS_BZIP2:
                r = BZ2_bzCompressInit(&c->bzip2, 9, 0, 0);
                if (r != BZ_OK)
                        return -EIO;

                c->type = IMPORT_COMPRESS_BZIP2;
                break;
#endif

        case IMPORT_COMPRESS_UNCOMPRESSED:
                c->type = IMPORT_COMPRESS_UNCOMPRESSED;
                break;

        default:
                return -EOPNOTSUPP;
        }

        c->encoding = true;
        return 0;
}