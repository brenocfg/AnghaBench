#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_codec ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_DECRYPT ; 
 int /*<<< orphan*/  CIPHER_READ_CTX ; 
 int /*<<< orphan*/  SQLITERK_DAMAGED ; 
 int SQLITERK_OK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 scalar_t__ sqlcipher_codec_ctx_get_data (int /*<<< orphan*/ *) ; 
 int sqlcipher_codec_ctx_get_pagesize (int /*<<< orphan*/ *) ; 
 int sqlcipher_codec_key_derive (int /*<<< orphan*/ *) ; 
 int sqlcipher_page_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  sqlite3_errstr (int) ; 
 int /*<<< orphan*/  sqliterkOSError (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int sqliterkCryptoDecode(sqliterk_codec *codec, int pgno, void *data)
{
    int rc;
    int offset = 0;
    unsigned char *pdata = (unsigned char *) data;

    int page_sz = sqlcipher_codec_ctx_get_pagesize(codec);
    unsigned char *buffer =
        (unsigned char *) sqlcipher_codec_ctx_get_data(codec);

    rc = sqlcipher_codec_key_derive(codec);
    if (rc != SQLITE_OK)
        return rc;

    if (pgno == 1) {
        offset = 16; // FILE_HEADER_SZ
        memcpy(buffer, "SQLite format 3", 16);
    }
    rc = sqlcipher_page_cipher(codec, CIPHER_READ_CTX, pgno, CIPHER_DECRYPT,
                               page_sz - offset, pdata + offset,
                               buffer + offset);
    if (rc != SQLITE_OK)
        goto bail;
    memcpy(pdata, buffer, page_sz);

    return SQLITERK_OK;

bail:
    sqliterkOSError(SQLITERK_DAMAGED, "Failed to decode page %d: %s", pgno,
                    sqlite3_errstr(rc));
    return rc;
}