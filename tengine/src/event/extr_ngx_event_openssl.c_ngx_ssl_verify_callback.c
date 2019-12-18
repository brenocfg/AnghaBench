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
typedef  int /*<<< orphan*/  ngx_ssl_conn_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  SSL_get_ex_data_X509_STORE_CTX_idx () ; 
 char* X509_NAME_oneline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,char*,char*) ; 
 TYPE_1__* ngx_ssl_get_connection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_ssl_verify_callback(int ok, X509_STORE_CTX *x509_store)
{
#if (NGX_DEBUG)
    char              *subject, *issuer;
    int                err, depth;
    X509              *cert;
    X509_NAME         *sname, *iname;
    ngx_connection_t  *c;
    ngx_ssl_conn_t    *ssl_conn;

    ssl_conn = X509_STORE_CTX_get_ex_data(x509_store,
                                          SSL_get_ex_data_X509_STORE_CTX_idx());

    c = ngx_ssl_get_connection(ssl_conn);

    cert = X509_STORE_CTX_get_current_cert(x509_store);
    err = X509_STORE_CTX_get_error(x509_store);
    depth = X509_STORE_CTX_get_error_depth(x509_store);

    sname = X509_get_subject_name(cert);
    subject = sname ? X509_NAME_oneline(sname, NULL, 0) : "(none)";

    iname = X509_get_issuer_name(cert);
    issuer = iname ? X509_NAME_oneline(iname, NULL, 0) : "(none)";

    ngx_log_debug5(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "verify:%d, error:%d, depth:%d, "
                   "subject:\"%s\", issuer:\"%s\"",
                   ok, err, depth, subject, issuer);

    if (sname) {
        OPENSSL_free(subject);
    }

    if (iname) {
        OPENSSL_free(issuer);
    }
#endif

    return 1;
}