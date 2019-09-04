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
typedef  int /*<<< orphan*/  status ;
struct TYPE_3__ {int /*<<< orphan*/  ssl; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ connection ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  RETRY ; 
#define  SSL_ERROR_WANT_READ 129 
#define  SSL_ERROR_WANT_WRITE 128 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

status ssl_read(connection *c, size_t *n) {
    int r;
    if ((r = SSL_read(c->ssl, c->buf, sizeof(c->buf))) <= 0) {
        switch (SSL_get_error(c->ssl, r)) {
            case SSL_ERROR_WANT_READ:  return RETRY;
            case SSL_ERROR_WANT_WRITE: return RETRY;
            default:                   return ERROR;
        }
    }
    *n = (size_t) r;
    return OK;
}