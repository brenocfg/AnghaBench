#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_6__ {TYPE_2__* root; } ;
typedef  TYPE_1__ ngx_trie_t ;
struct TYPE_7__ {size_t key; int /*<<< orphan*/  greedy; void* value; struct TYPE_7__** next; struct TYPE_7__* search_clue; } ;
typedef  TYPE_2__ ngx_trie_node_t ;
struct TYPE_8__ {size_t len; size_t* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  size_t ngx_int_t ;

/* Variables and functions */
 size_t NGX_TRIE_KIND ; 
 int NGX_TRIE_REVERSE ; 

void *
ngx_trie_query(ngx_trie_t *trie, ngx_str_t *str, ngx_int_t *version_pos,
    ngx_uint_t mode)
{
    void            *value;
    size_t           i;
    ngx_int_t        step, pos, index;
    ngx_trie_node_t *p, *root;

    value = NULL;
    root = trie->root;
    p = root;
    i = 0;

    if (mode & NGX_TRIE_REVERSE) {
        pos = str->len;
        step = -1;
    } else {
        pos = -1;
        step = 1;
    }

    if (p->next == NULL) {
        return NULL;
    }

    while (i < str->len) {
        pos += step;
        index = str->data[pos];
        if (index < 0 || index >= NGX_TRIE_KIND) {
            index = 0;
        }

        while (p->next[index] == NULL) {
            if (p == root) {
                break;
            }
            p = p->search_clue;
        }

        p = p->next[index];
        p = p == NULL ? root : p;
        if (p->key) {
            value = p->value;
            *version_pos = pos + p->key;
            if (!p->greedy) {
                return value;
            }
            p = root;
        }

        i++;
    }

    return value;
}