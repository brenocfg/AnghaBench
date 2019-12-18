#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct server_pool {TYPE_1__ redis_auth; int /*<<< orphan*/  require_auth; } ;
struct msg {int /*<<< orphan*/  keys; scalar_t__ owner; } ;
struct keypos {int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; } ;
struct conn {int authenticated; scalar_t__ owner; int /*<<< orphan*/  proxy; scalar_t__ client; } ;
typedef  int /*<<< orphan*/  rstatus_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct keypos* array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msg_append (struct msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ rsp_invalid_password ; 
 TYPE_3__ rsp_no_password ; 
 TYPE_2__ rsp_ok ; 

__attribute__((used)) static rstatus_t
redis_handle_auth_req(struct msg *req, struct msg *rsp)
{
    struct conn *conn = (struct conn *)rsp->owner;
    struct server_pool *pool;
    struct keypos *kpos;
    uint8_t *key;
    uint32_t keylen;
    bool valid;

    ASSERT(conn->client && !conn->proxy);

    pool = (struct server_pool *)conn->owner;

    if (!pool->require_auth) {
        /*
         * AUTH command from the client in absence of a redis_auth:
         * directive should be treated as an error
         */
        return msg_append(rsp, rsp_no_password.data, rsp_no_password.len);
    }

    kpos = array_get(req->keys, 0);
    key = kpos->start;
    keylen = (uint32_t)(kpos->end - kpos->start);
    valid = (keylen == pool->redis_auth.len) &&
            (memcmp(pool->redis_auth.data, key, keylen) == 0) ? true : false;
    if (valid) {
        conn->authenticated = 1;
        return msg_append(rsp, rsp_ok.data, rsp_ok.len);
    }

    /*
     * Password in the AUTH command doesn't match the one configured in
     * redis_auth: directive
     *
     * We mark the connection has unauthenticated until the client
     * reauthenticates with the correct password
     */
    conn->authenticated = 0;
    return msg_append(rsp, rsp_invalid_password.data, rsp_invalid_password.len);
}