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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_3__ {int log_error; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */
 int ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_peek_error () ; 
 int /*<<< orphan*/  NGX_ECONNREFUSED ; 
 int /*<<< orphan*/  NGX_ECONNRESET ; 
 int /*<<< orphan*/  NGX_EHOSTDOWN ; 
 int /*<<< orphan*/  NGX_EHOSTUNREACH ; 
 int /*<<< orphan*/  NGX_ENETDOWN ; 
 int /*<<< orphan*/  NGX_ENETUNREACH ; 
 int /*<<< orphan*/  NGX_ENOTCONN ; 
 int /*<<< orphan*/  NGX_EPIPE ; 
#define  NGX_ERROR_ERR 130 
#define  NGX_ERROR_IGNORE_ECONNRESET 129 
#define  NGX_ERROR_INFO 128 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_R_BAD_CHANGE_CIPHER_SPEC ; 
 int SSL_R_BLOCK_CIPHER_PAD_IS_WRONG ; 
 int SSL_R_CALLBACK_FAILED ; 
 int SSL_R_CERT_CB_ERROR ; 
 int SSL_R_CLIENTHELLO_TLSEXT ; 
 int SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC ; 
 int SSL_R_DIGEST_CHECK_FAILED ; 
 int SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST ; 
 int SSL_R_EXCESSIVE_MESSAGE_SIZE ; 
 int SSL_R_HTTPS_PROXY_REQUEST ; 
 int SSL_R_HTTP_REQUEST ; 
 int SSL_R_INAPPROPRIATE_FALLBACK ; 
 int SSL_R_LENGTH_MISMATCH ; 
 int SSL_R_NO_CIPHERS_PASSED ; 
 int SSL_R_NO_CIPHERS_SPECIFIED ; 
 int SSL_R_NO_COMMON_SIGNATURE_ALGORITHMS ; 
 int SSL_R_NO_COMPRESSION_SPECIFIED ; 
 int SSL_R_NO_SHARED_CIPHER ; 
 int SSL_R_NO_SHARED_GROUP ; 
 int SSL_R_NO_SUITABLE_KEY_SHARE ; 
 int SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM ; 
 int SSL_R_PARSE_TLSEXT ; 
 int SSL_R_RECORD_LENGTH_MISMATCH ; 
 int SSL_R_RENEGOTIATE_EXT_TOO_LONG ; 
 int SSL_R_RENEGOTIATION_ENCODING_ERR ; 
 int SSL_R_RENEGOTIATION_MISMATCH ; 
 int SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING ; 
 int SSL_R_SSLV3_ALERT_BAD_CERTIFICATE ; 
 int SSL_R_SSLV3_ALERT_BAD_RECORD_MAC ; 
 int SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED ; 
 int SSL_R_SSLV3_ALERT_CERTIFICATE_REVOKED ; 
 int SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN ; 
 int SSL_R_SSLV3_ALERT_DECOMPRESSION_FAILURE ; 
 int SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE ; 
 int SSL_R_SSLV3_ALERT_ILLEGAL_PARAMETER ; 
 int SSL_R_SSLV3_ALERT_NO_CERTIFICATE ; 
 int SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE ; 
 int SSL_R_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE ; 
 int SSL_R_TLSV1_ALERT_ACCESS_DENIED ; 
 int SSL_R_TLSV1_ALERT_DECODE_ERROR ; 
 int SSL_R_TLSV1_ALERT_DECRYPTION_FAILED ; 
 int SSL_R_TLSV1_ALERT_DECRYPT_ERROR ; 
 int SSL_R_TLSV1_ALERT_EXPORT_RESTRICTION ; 
 int SSL_R_TLSV1_ALERT_INSUFFICIENT_SECURITY ; 
 int SSL_R_TLSV1_ALERT_INTERNAL_ERROR ; 
 int SSL_R_TLSV1_ALERT_NO_RENEGOTIATION ; 
 int SSL_R_TLSV1_ALERT_PROTOCOL_VERSION ; 
 int SSL_R_TLSV1_ALERT_RECORD_OVERFLOW ; 
 int SSL_R_TLSV1_ALERT_UNKNOWN_CA ; 
 int SSL_R_TLSV1_ALERT_USER_CANCELLED ; 
 int SSL_R_UNEXPECTED_MESSAGE ; 
 int SSL_R_UNEXPECTED_RECORD ; 
 int SSL_R_UNKNOWN_ALERT_TYPE ; 
 int SSL_R_UNKNOWN_PROTOCOL ; 
 int SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED ; 
 int SSL_R_UNSUPPORTED_PROTOCOL ; 
 int SSL_R_VERSION_TOO_LOW ; 
 int SSL_R_WRONG_VERSION_NUMBER ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_ssl_connection_error(ngx_connection_t *c, int sslerr, ngx_err_t err,
    char *text)
{
    int         n;
    ngx_uint_t  level;

    level = NGX_LOG_CRIT;

    if (sslerr == SSL_ERROR_SYSCALL) {

        if (err == NGX_ECONNRESET
            || err == NGX_EPIPE
            || err == NGX_ENOTCONN
            || err == NGX_ETIMEDOUT
            || err == NGX_ECONNREFUSED
            || err == NGX_ENETDOWN
            || err == NGX_ENETUNREACH
            || err == NGX_EHOSTDOWN
            || err == NGX_EHOSTUNREACH)
        {
            switch (c->log_error) {

            case NGX_ERROR_IGNORE_ECONNRESET:
            case NGX_ERROR_INFO:
                level = NGX_LOG_INFO;
                break;

            case NGX_ERROR_ERR:
                level = NGX_LOG_ERR;
                break;

            default:
                break;
            }
        }

    } else if (sslerr == SSL_ERROR_SSL) {

        n = ERR_GET_REASON(ERR_peek_error());

            /* handshake failures */
        if (n == SSL_R_BAD_CHANGE_CIPHER_SPEC                        /*  103 */
#ifdef SSL_R_NO_SUITABLE_KEY_SHARE
            || n == SSL_R_NO_SUITABLE_KEY_SHARE                      /*  101 */
#endif
#ifdef SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM
            || n == SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM            /*  118 */
#endif
            || n == SSL_R_BLOCK_CIPHER_PAD_IS_WRONG                  /*  129 */
            || n == SSL_R_DIGEST_CHECK_FAILED                        /*  149 */
            || n == SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST              /*  151 */
            || n == SSL_R_EXCESSIVE_MESSAGE_SIZE                     /*  152 */
            || n == SSL_R_HTTPS_PROXY_REQUEST                        /*  155 */
            || n == SSL_R_HTTP_REQUEST                               /*  156 */
            || n == SSL_R_LENGTH_MISMATCH                            /*  159 */
#ifdef SSL_R_NO_CIPHERS_PASSED
            || n == SSL_R_NO_CIPHERS_PASSED                          /*  182 */
#endif
            || n == SSL_R_NO_CIPHERS_SPECIFIED                       /*  183 */
            || n == SSL_R_NO_COMPRESSION_SPECIFIED                   /*  187 */
            || n == SSL_R_NO_SHARED_CIPHER                           /*  193 */
            || n == SSL_R_RECORD_LENGTH_MISMATCH                     /*  213 */
#ifdef SSL_R_CLIENTHELLO_TLSEXT
            || n == SSL_R_CLIENTHELLO_TLSEXT                         /*  226 */
#endif
#ifdef SSL_R_PARSE_TLSEXT
            || n == SSL_R_PARSE_TLSEXT                               /*  227 */
#endif
#ifdef SSL_R_CALLBACK_FAILED
            || n == SSL_R_CALLBACK_FAILED                            /*  234 */
#endif
            || n == SSL_R_UNEXPECTED_MESSAGE                         /*  244 */
            || n == SSL_R_UNEXPECTED_RECORD                          /*  245 */
            || n == SSL_R_UNKNOWN_ALERT_TYPE                         /*  246 */
            || n == SSL_R_UNKNOWN_PROTOCOL                           /*  252 */
#ifdef SSL_R_NO_COMMON_SIGNATURE_ALGORITHMS
            || n == SSL_R_NO_COMMON_SIGNATURE_ALGORITHMS             /*  253 */
#endif
            || n == SSL_R_UNSUPPORTED_PROTOCOL                       /*  258 */
#ifdef SSL_R_NO_SHARED_GROUP
            || n == SSL_R_NO_SHARED_GROUP                            /*  266 */
#endif
            || n == SSL_R_WRONG_VERSION_NUMBER                       /*  267 */
            || n == SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC        /*  281 */
#ifdef SSL_R_RENEGOTIATE_EXT_TOO_LONG
            || n == SSL_R_RENEGOTIATE_EXT_TOO_LONG                   /*  335 */
            || n == SSL_R_RENEGOTIATION_ENCODING_ERR                 /*  336 */
            || n == SSL_R_RENEGOTIATION_MISMATCH                     /*  337 */
#endif
#ifdef SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED
            || n == SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED       /*  338 */
#endif
#ifdef SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING
            || n == SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING           /*  345 */
#endif
#ifdef SSL_R_INAPPROPRIATE_FALLBACK
            || n == SSL_R_INAPPROPRIATE_FALLBACK                     /*  373 */
#endif
#ifdef SSL_R_CERT_CB_ERROR
            || n == SSL_R_CERT_CB_ERROR                              /*  377 */
#endif
#ifdef SSL_R_VERSION_TOO_LOW
            || n == SSL_R_VERSION_TOO_LOW                            /*  396 */
#endif
            || n == 1000 /* SSL_R_SSLV3_ALERT_CLOSE_NOTIFY */
#ifdef SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE
            || n == SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE             /* 1010 */
            || n == SSL_R_SSLV3_ALERT_BAD_RECORD_MAC                 /* 1020 */
            || n == SSL_R_TLSV1_ALERT_DECRYPTION_FAILED              /* 1021 */
            || n == SSL_R_TLSV1_ALERT_RECORD_OVERFLOW                /* 1022 */
            || n == SSL_R_SSLV3_ALERT_DECOMPRESSION_FAILURE          /* 1030 */
            || n == SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE              /* 1040 */
            || n == SSL_R_SSLV3_ALERT_NO_CERTIFICATE                 /* 1041 */
            || n == SSL_R_SSLV3_ALERT_BAD_CERTIFICATE                /* 1042 */
            || n == SSL_R_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE        /* 1043 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_REVOKED            /* 1044 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED            /* 1045 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN            /* 1046 */
            || n == SSL_R_SSLV3_ALERT_ILLEGAL_PARAMETER              /* 1047 */
            || n == SSL_R_TLSV1_ALERT_UNKNOWN_CA                     /* 1048 */
            || n == SSL_R_TLSV1_ALERT_ACCESS_DENIED                  /* 1049 */
            || n == SSL_R_TLSV1_ALERT_DECODE_ERROR                   /* 1050 */
            || n == SSL_R_TLSV1_ALERT_DECRYPT_ERROR                  /* 1051 */
            || n == SSL_R_TLSV1_ALERT_EXPORT_RESTRICTION             /* 1060 */
            || n == SSL_R_TLSV1_ALERT_PROTOCOL_VERSION               /* 1070 */
            || n == SSL_R_TLSV1_ALERT_INSUFFICIENT_SECURITY          /* 1071 */
            || n == SSL_R_TLSV1_ALERT_INTERNAL_ERROR                 /* 1080 */
            || n == SSL_R_TLSV1_ALERT_USER_CANCELLED                 /* 1090 */
            || n == SSL_R_TLSV1_ALERT_NO_RENEGOTIATION               /* 1100 */
#endif
            )
        {
            switch (c->log_error) {

            case NGX_ERROR_IGNORE_ECONNRESET:
            case NGX_ERROR_INFO:
                level = NGX_LOG_INFO;
                break;

            case NGX_ERROR_ERR:
                level = NGX_LOG_ERR;
                break;

            default:
                break;
            }
        }
    }

    ngx_ssl_error(level, c->log, err, text);
}