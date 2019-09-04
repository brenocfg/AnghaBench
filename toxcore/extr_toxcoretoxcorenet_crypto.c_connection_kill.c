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
struct TYPE_3__ {int /*<<< orphan*/  connection_status_callback_id; int /*<<< orphan*/  connection_status_callback_object; int /*<<< orphan*/  (* connection_status_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_1__ Crypto_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_kill (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connection_kill(Net_Crypto *c, int crypt_connection_id)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return;

    if (conn->connection_status_callback) {
        conn->connection_status_callback(conn->connection_status_callback_object, conn->connection_status_callback_id, 0);
    }

    crypto_kill(c, crypt_connection_id);
}