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

/* Variables and functions */
#define  CURLE_COULDNT_CONNECT 139 
#define  CURLE_COULDNT_RESOLVE_HOST 138 
#define  CURLE_COULDNT_RESOLVE_PROXY 137 
#define  CURLE_GOT_NOTHING 136 
#define  CURLE_OPERATION_TIMEDOUT 135 
 int CURLE_PEER_FAILED_VERIFICATION ; 
#define  CURLE_RECV_ERROR 134 
#define  CURLE_SEND_ERROR 133 
#define  CURLE_SEND_FAIL_REWIND 132 
 int CURLE_SSL_CACERT ; 
#define  CURLE_SSL_CACERT_BADFILE 131 
#define  CURLE_SSL_CERTPROBLEM 130 
#define  CURLE_SSL_CONNECT_ERROR 129 
#define  CURLE_SSL_ISSUER_ERROR 128 
 int HTTP_TASK_ERR_CONNECT ; 
 int HTTP_TASK_ERR_NET ; 
 int HTTP_TASK_ERR_RESOLVE_HOST ; 
 int HTTP_TASK_ERR_RESOLVE_PROXY ; 
 int HTTP_TASK_ERR_SSL ; 
 int HTTP_TASK_ERR_TX ; 
 int HTTP_TASK_ERR_TX_TIMEOUT ; 
 int HTTP_TASK_ERR_UNHANDLED_REDIRECT ; 

__attribute__((used)) static int
curl_error_to_http_task_error (int curl_error)
{
    if (curl_error == CURLE_SSL_CACERT ||
        curl_error == CURLE_PEER_FAILED_VERIFICATION)
        return HTTP_TASK_ERR_SSL;

    switch (curl_error) {
    case CURLE_COULDNT_RESOLVE_PROXY:
        return HTTP_TASK_ERR_RESOLVE_PROXY;
    case CURLE_COULDNT_RESOLVE_HOST:
        return HTTP_TASK_ERR_RESOLVE_HOST;
    case CURLE_COULDNT_CONNECT:
        return HTTP_TASK_ERR_CONNECT;
    case CURLE_OPERATION_TIMEDOUT:
        return HTTP_TASK_ERR_TX_TIMEOUT;
    case CURLE_SSL_CONNECT_ERROR:
    case CURLE_SSL_CERTPROBLEM:
    case CURLE_SSL_CACERT_BADFILE:
    case CURLE_SSL_ISSUER_ERROR:
        return HTTP_TASK_ERR_SSL;
    case CURLE_GOT_NOTHING:
    case CURLE_SEND_ERROR:
    case CURLE_RECV_ERROR:
        return HTTP_TASK_ERR_TX;
    case CURLE_SEND_FAIL_REWIND:
        return HTTP_TASK_ERR_UNHANDLED_REDIRECT;
    default:
        return HTTP_TASK_ERR_NET;
    }
}