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
struct TYPE_3__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ connection ;

/* Variables and functions */
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  SSL_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ ) ; 

status ssl_close(connection *c) {
    SSL_shutdown(c->ssl);
    SSL_clear(c->ssl);
    return OK;
}