#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {scalar_t__ status; int /*<<< orphan*/  shared_key; int /*<<< orphan*/  sessionsecret_key; int /*<<< orphan*/  peersessionpublic_key; int /*<<< orphan*/  recv_nonce; int /*<<< orphan*/  dht_public_key; } ;
struct TYPE_14__ {int (* new_connection_callback ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  new_connection_callback_object; } ;
struct TYPE_13__ {int /*<<< orphan*/ * cookie; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  peersessionpublic_key; int /*<<< orphan*/  recv_nonce; int /*<<< orphan*/  public_key; int /*<<< orphan*/  cookie_length; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ New_Connection ;
typedef  TYPE_2__ Net_Crypto ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_3__ Crypto_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  COOKIE_LENGTH ; 
 scalar_t__ CRYPTO_CONN_COOKIE_REQUESTING ; 
 scalar_t__ CRYPTO_CONN_HANDSHAKE_SENT ; 
 scalar_t__ CRYPTO_CONN_NOT_CONFIRMED ; 
 int /*<<< orphan*/  connection_kill (TYPE_2__*,int) ; 
 scalar_t__ create_send_handshake (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_box_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_connection_add_source (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypt_precompute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_3__* get_crypto_connection (TYPE_2__*,int) ; 
 int getcryptconnection_id (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ handle_crypto_handshake (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int handle_new_connection_handshake(Net_Crypto *c, IP_Port source, const uint8_t *data, uint16_t length)
{
    New_Connection n_c;
    n_c.cookie = malloc(COOKIE_LENGTH);

    if (n_c.cookie == NULL)
        return -1;

    n_c.source = source;
    n_c.cookie_length = COOKIE_LENGTH;

    if (handle_crypto_handshake(c, n_c.recv_nonce, n_c.peersessionpublic_key, n_c.public_key, n_c.dht_public_key,
                                n_c.cookie, data, length, 0) != 0) {
        free(n_c.cookie);
        return -1;
    }

    int crypt_connection_id = getcryptconnection_id(c, n_c.public_key);

    if (crypt_connection_id != -1) {
        Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

        if (public_key_cmp(n_c.dht_public_key, conn->dht_public_key) != 0) {
            connection_kill(c, crypt_connection_id);
        } else {
            int ret = -1;

            if (conn && (conn->status == CRYPTO_CONN_COOKIE_REQUESTING || conn->status == CRYPTO_CONN_HANDSHAKE_SENT)) {
                memcpy(conn->recv_nonce, n_c.recv_nonce, crypto_box_NONCEBYTES);
                memcpy(conn->peersessionpublic_key, n_c.peersessionpublic_key, crypto_box_PUBLICKEYBYTES);
                encrypt_precompute(conn->peersessionpublic_key, conn->sessionsecret_key, conn->shared_key);

                crypto_connection_add_source(c, crypt_connection_id, source);

                if (create_send_handshake(c, crypt_connection_id, n_c.cookie, n_c.dht_public_key) == 0) {
                    conn->status = CRYPTO_CONN_NOT_CONFIRMED;
                    ret = 0;
                }
            }

            free(n_c.cookie);
            return ret;
        }
    }

    int ret = c->new_connection_callback(c->new_connection_callback_object, &n_c);
    free(n_c.cookie);
    return ret;
}