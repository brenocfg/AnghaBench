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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct string {int /*<<< orphan*/ * data; } ;
struct server_pool {int dist_type; int /*<<< orphan*/  server; int /*<<< orphan*/  ncontinuum; int /*<<< orphan*/  continuum; struct string hash_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DIST_KETAMA 130 
#define  DIST_MODULA 129 
#define  DIST_RANDOM 128 
 int /*<<< orphan*/  NOT_REACHED () ; 
 int array_n (int /*<<< orphan*/ *) ; 
 int ketama_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int modula_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nc_strchr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int random_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int server_pool_hash (struct server_pool*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  string_empty (struct string*) ; 

uint32_t
server_pool_idx(struct server_pool *pool, uint8_t *key, uint32_t keylen)
{
    uint32_t hash, idx;

    ASSERT(array_n(&pool->server) != 0);
    ASSERT(key != NULL);

    /*
     * If hash_tag: is configured for this server pool, we use the part of
     * the key within the hash tag as an input to the distributor. Otherwise
     * we use the full key
     */
    if (!string_empty(&pool->hash_tag)) {
        struct string *tag = &pool->hash_tag;
        uint8_t *tag_start, *tag_end;

        tag_start = nc_strchr(key, key + keylen, tag->data[0]);
        if (tag_start != NULL) {
            tag_end = nc_strchr(tag_start + 1, key + keylen, tag->data[1]);
            if ((tag_end != NULL) && (tag_end - tag_start > 1)) {
                key = tag_start + 1;
                keylen = (uint32_t)(tag_end - key);
            }
        }
    }

    switch (pool->dist_type) {
    case DIST_KETAMA:
        hash = server_pool_hash(pool, key, keylen);
        idx = ketama_dispatch(pool->continuum, pool->ncontinuum, hash);
        break;

    case DIST_MODULA:
        hash = server_pool_hash(pool, key, keylen);
        idx = modula_dispatch(pool->continuum, pool->ncontinuum, hash);
        break;

    case DIST_RANDOM:
        idx = random_dispatch(pool->continuum, pool->ncontinuum, 0);
        break;

    default:
        NOT_REACHED();
        return 0;
    }
    ASSERT(idx < array_n(&pool->server));
    return idx;
}