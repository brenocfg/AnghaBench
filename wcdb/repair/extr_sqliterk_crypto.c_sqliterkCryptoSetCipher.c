#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pagesize; int reservedBytes; int /*<<< orphan*/ * codec; } ;
typedef  TYPE_1__ sqliterk_pager ;
typedef  int /*<<< orphan*/  sqliterk_file ;
struct TYPE_6__ {int /*<<< orphan*/  kdf_iter; int /*<<< orphan*/  use_hmac; int /*<<< orphan*/  page_size; scalar_t__ kdf_salt; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ sqliterk_cipher_conf ;
typedef  int /*<<< orphan*/  codec_ctx ;

/* Variables and functions */
 int SQLITERK_CANTOPEN ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlcipher_activate () ; 
 int /*<<< orphan*/  sqlcipher_codec_ctx_free (int /*<<< orphan*/ **) ; 
 int sqlcipher_codec_ctx_get_pagesize (int /*<<< orphan*/ *) ; 
 int sqlcipher_codec_ctx_get_reservesize (int /*<<< orphan*/ *) ; 
 int sqlcipher_codec_ctx_init (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlcipher_codec_ctx_set_kdf_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlcipher_codec_ctx_set_kdf_salt (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int sqlcipher_codec_ctx_set_pagesize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlcipher_codec_ctx_set_use_hmac (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlcipher_deactivate () ; 
 int /*<<< orphan*/  sqlite3_errstr (int) ; 
 int /*<<< orphan*/  sqlite3_initialize () ; 
 int /*<<< orphan*/  sqliterkOSError (int,char*,...) ; 
 int sqliterkOSRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t*) ; 

int sqliterkCryptoSetCipher(sqliterk_pager *pager,
                            sqliterk_file *fd,
                            const sqliterk_cipher_conf *conf)
{
    codec_ctx *codec = NULL;
    int rc;

    if (conf) {
        // Check arguments.
        if (!conf->key || conf->key_len <= 0)
            return SQLITERK_MISUSE;

        // SQLite library must be initialized before calling sqlcipher_activate(),
        // or it will cause a deadlock.
        sqlite3_initialize();
        sqlcipher_activate();

        // XXX: fake BTree structure passed to sqlcipher_codec_ctx_init.
        // Member of such structure is assigned but never used by repair kit.
        int fake_db[8];

        // Initialize codec context.
        rc = sqlcipher_codec_ctx_init(&codec, fake_db, NULL, conf->key, conf->key_len);
        if (rc != SQLITE_OK)
            goto bail_sqlite_errstr;

        // Read and set KDF salt.
        unsigned char *salt;
        unsigned char salt_buf[16];
        if (conf->kdf_salt) {
            salt = (unsigned char *) conf->kdf_salt;
        } else {
            size_t salt_size = 16;
            rc = sqliterkOSRead(fd, 0, salt_buf, &salt_size);
            if (rc != SQLITERK_OK) {
                sqliterkOSError(rc, "Failed to load KDF salt from file.");
                goto bail;
            }
            salt = salt_buf;
        }
        sqlcipher_codec_ctx_set_kdf_salt(codec, salt, 16);

        // Set page size.
        if (conf->page_size > 0) {
            rc = sqlcipher_codec_ctx_set_pagesize(codec, conf->page_size);
            if (rc != SQLITE_OK)
                goto bail_sqlite_errstr;
        }

        // Set HMAC usage.
        if (conf->use_hmac >= 0) {
            rc = sqlcipher_codec_ctx_set_use_hmac(codec, conf->use_hmac);
            if (rc != SQLITE_OK)
                goto bail_sqlite_errstr;
        }

        // Set KDF Iteration.
        if (conf->kdf_iter > 0) {
            rc = sqlcipher_codec_ctx_set_kdf_iter(codec, conf->kdf_iter);
            if (rc != SQLITE_OK)
                goto bail;
        }

        // Update pager page size.
        int page_sz = sqlcipher_codec_ctx_get_pagesize(codec);
        int reserve_sz = sqlcipher_codec_ctx_get_reservesize(codec);

        pager->pagesize = page_sz;
        pager->reservedBytes = reserve_sz;
    }

    if (pager->codec) {
        sqlcipher_codec_ctx_free(&pager->codec);
        sqlcipher_deactivate();
    }

    pager->codec = codec;
    return SQLITERK_OK;

bail_sqlite_errstr:
    sqliterkOSError(SQLITERK_CANTOPEN,
                    "Failed to initialize cipher context: %s",
                    sqlite3_errstr(rc));
    rc = SQLITERK_CANTOPEN;
bail:
    if (codec)
        sqlcipher_codec_ctx_free(&codec);
    sqlcipher_deactivate();
    return rc;
}