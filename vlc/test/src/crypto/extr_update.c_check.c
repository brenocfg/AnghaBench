#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  digest_algo; int /*<<< orphan*/ * issuer_longid; int /*<<< orphan*/  const* hash_verification; } ;
typedef  TYPE_1__ signature_packet_t ;
struct TYPE_10__ {char* psz_username; int* longid; int /*<<< orphan*/  key; TYPE_1__ sig; } ;
typedef  TYPE_2__ public_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*,int,int,int,int,int,int,int,int) ; 
 char* gcry_md_algo_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_from_public_key (TYPE_2__*) ; 
 int /*<<< orphan*/ * hash_from_text (char const*,TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verify_signature (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check(public_key_t *key, public_key_t *key2, const char *data,
    signature_packet_t *sig, const uint8_t *key_longid, const uint8_t *key_longid2)
{
    uint8_t *hash;
    const char *type;

    if (data) {
        hash = hash_from_text(data, sig);
        type = "text";
    } else {
        hash = hash_from_public_key(key);
        type = "public key";
    }

    assert(hash);

    // TODO : binary file
    assert(!memcmp(hash, sig->hash_verification, 2));

    if (memcmp(sig->issuer_longid, key_longid, 8)) {
        assert(key2 && key_longid2);
        check(key, NULL, NULL, &key->sig, key_longid, NULL);
        key = key2;
    }

    assert(!verify_signature(sig, &key->key, hash));

    fprintf(stderr, "Good %s %s signature from %s (%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X)\n",
            type, gcry_md_algo_name(sig->digest_algo), key->psz_username,
            key->longid[0], key->longid[1], key->longid[2], key->longid[3],
            key->longid[4], key->longid[5], key->longid[6], key->longid[7]
            );
}