#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_16__ {scalar_t__ key; } ;
typedef  TYPE_2__ ngx_rbtree_node_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  scalar_t__ ngx_msec_int_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {TYPE_1__* log; int /*<<< orphan*/  handler; int /*<<< orphan*/  data; int /*<<< orphan*/  timer; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_18__ {char* pos; char* last; int memory; int last_buf; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_19__ {int nelts; scalar_t__ elts; } ;
typedef  TYPE_5__ ngx_array_t ;
struct TYPE_15__ {char* action; } ;
struct TYPE_14__ {TYPE_2__* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_INT_T_LEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_PTR_SIZE ; 
 int NGX_TIME_T_LEN ; 
 TYPE_5__* ngx_array_create (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ngx_array_destroy (TYPE_5__*) ; 
 scalar_t__ ngx_current_msec ; 
 TYPE_11__ ngx_event_timer_rbtree ; 
 int /*<<< orphan*/  ngx_http_debug_timer_traversal (TYPE_5__*,TYPE_2__*) ; 
 char* ngx_palloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_pid ; 
 char* ngx_snprintf (char*,int,char*,int,TYPE_2__*,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* ngx_sprintf (char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_debug_timer_buf(ngx_pool_t *pool, ngx_buf_t *b)
{
    u_char              *p;
    size_t               size;
    ngx_uint_t           i, n;
    ngx_event_t         *ev;
    ngx_array_t         *array;
    ngx_msec_int_t       timer;
    ngx_rbtree_node_t   *root;
    ngx_rbtree_node_t  **nodes, *node;

#define NGX_TIMER_TITLE_SIZE     (sizeof(NGX_TIMER_TITLE_FORMAT) - 1 + NGX_TIME_T_LEN + NGX_INT_T_LEN)     /* sizeof pid_t equals time_t */
#define NGX_TIMER_TITLE_FORMAT   "pid:%P\n"                  \
                                 "timer:%ui\n"

#define NGX_TIMER_ENTRY_SIZE     (sizeof(NGX_TIMER_ENTRY_FORMAT) - 1 + \
                                  NGX_INT_T_LEN * 2 + NGX_PTR_SIZE * 4 + 256 /* func name */)
#define NGX_TIMER_ENTRY_FORMAT  "--------- [%ui] --------\n"\
                                "timers[i]: %p\n"          \
                                "    timer: %ui\n"          \
                                "       ev: %p\n"           \
                                "     data: %p\n"           \
                                "  handler: %p\n"           \
                                "   action: %s\n"

    root = ngx_event_timer_rbtree.root;

    array = ngx_array_create(pool, 10, sizeof(ngx_rbtree_node_t **));
    if (array == NULL) {
        return NGX_ERROR;
    }

    ngx_http_debug_timer_traversal(array, root);

    n = array->nelts;

    size = NGX_TIMER_TITLE_SIZE + n * NGX_TIMER_ENTRY_SIZE;
    p = ngx_palloc(pool, size);
    if (p == NULL) {
        ngx_array_destroy(array);
        return NGX_ERROR;
    }

    b->pos = p;

    p = ngx_sprintf(p, NGX_TIMER_TITLE_FORMAT, ngx_pid, n);

    nodes = (ngx_rbtree_node_t **) array->elts;

    for (i = 0; i < n; i++) {
        node = nodes[i]; /* node: timer */
        ev = (ngx_event_t *) ((char *) node - (intptr_t)&((ngx_event_t *) 0x0)->timer);

         /* entry format of timer and ev */

        timer = (ngx_msec_int_t) (node->key - ngx_current_msec);

        p = ngx_snprintf(p, NGX_TIMER_ENTRY_SIZE, NGX_TIMER_ENTRY_FORMAT,
                         i, node, timer, ev, ev->data, ev->handler,
                         (ev->log->action != NULL) ? ev->log->action : "");
    }

    ngx_array_destroy(array);

    p[-1] = '\n';  /* make sure last char is newline */

    b->last = p;
    b->memory = 1;
    b->last_buf = 1;

    return NGX_OK;
}