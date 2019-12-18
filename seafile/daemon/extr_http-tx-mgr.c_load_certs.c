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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ gsize ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  X509_STORE_add_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_base64_decode (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
load_certs (sqlite3_stmt *stmt, void *vdata)
{
    X509_STORE *store = vdata;
    X509 *saved = NULL;
    const char *pem_b64;
    char *pem = NULL;
    BIO *b = NULL;
    gboolean ret = TRUE;

    pem_b64 = (const char *)sqlite3_column_text (stmt, 0);

    gsize len;
    pem = (char *)g_base64_decode (pem_b64, &len);
    if (!pem) {
        seaf_warning ("Failed to decode base64.\n");
        goto out;
    }

    b = BIO_new (BIO_s_mem());
    if (!b) {
        seaf_warning ("Failed to alloc BIO\n");
        goto out;
    }

    if (BIO_write (b, pem, len) != len) {
        seaf_warning ("Failed to write pem to BIO\n");
        goto out;
    }

    saved = PEM_read_bio_X509 (b, NULL, 0, NULL);
    if (!saved) {
        seaf_warning ("Failed to read PEM from BIO\n");
        goto out;
    }

    X509_STORE_add_cert (store, saved);

out:
    g_free (pem);
    if (b)
        BIO_free (b);
    if (saved)
        X509_free (saved);

    return ret;
}