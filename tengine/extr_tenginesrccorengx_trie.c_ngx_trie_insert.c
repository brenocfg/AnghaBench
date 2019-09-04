#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; TYPE_2__* root; } ;
typedef  TYPE_1__ ngx_trie_t ;
struct TYPE_10__ {size_t key; int greedy; struct TYPE_10__** next; } ;
typedef  TYPE_2__ ngx_trie_node_t ;
struct TYPE_11__ {size_t len; size_t* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  size_t ngx_int_t ;

/* Variables and functions */
 int NGX_TRIE_CONTINUE ; 
 size_t NGX_TRIE_KIND ; 
 int NGX_TRIE_REVERSE ; 
 TYPE_2__** ngx_pcalloc (int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* ngx_trie_node_create (int /*<<< orphan*/ ) ; 

ngx_trie_node_t *
ngx_trie_insert(ngx_trie_t *trie, ngx_str_t *str, ngx_uint_t mode)
{
    size_t           i;
    ngx_int_t        pos, step, index;
    ngx_trie_node_t *p, *root;

    root = trie->root;
    i = 0;

    if (mode & NGX_TRIE_REVERSE) {
        pos = str->len;
        step = -1;
    } else {
        pos = -1;
        step = 1;
    }

    p = root;

    while (i < str->len) {
        pos = pos + step;
        index = str->data[pos];

        if (index < 0 || index >= NGX_TRIE_KIND) {
            continue;
        }

        if (p->next == NULL) {
            p->next = ngx_pcalloc(trie->pool,
                                  NGX_TRIE_KIND * sizeof(ngx_trie_node_t *));

            if (p->next == NULL) {
                return NULL;
            }
        }

        if (p->next[index] == NULL) {
            p->next[index] = ngx_trie_node_create(trie->pool);
            if (p->next[index] == NULL) {
                return NULL;
            }
        }

        p = p->next[index];
        i++;
    }

    p->key = str->len;
    if (mode & NGX_TRIE_CONTINUE) {
        p->greedy = 1;
    }

    return p;
}