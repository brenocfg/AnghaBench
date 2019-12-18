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
struct msg {scalar_t__ redis; scalar_t__ swallow; scalar_t__ fdone; scalar_t__ done; scalar_t__ noforward; scalar_t__ noreply; scalar_t__ quit; scalar_t__ request; scalar_t__ ferror; scalar_t__ error; scalar_t__ err; scalar_t__ integer; scalar_t__ rlen; scalar_t__ rnarg; scalar_t__ narg; int /*<<< orphan*/ * narg_end; int /*<<< orphan*/ * narg_start; scalar_t__ frag_id; scalar_t__ nfrag_done; scalar_t__ nfrag; int /*<<< orphan*/ * frag_seq; int /*<<< orphan*/ * frag_owner; int /*<<< orphan*/ * end; scalar_t__ vlen; int /*<<< orphan*/ * keys; int /*<<< orphan*/  type; int /*<<< orphan*/ * post_coalesce; int /*<<< orphan*/ * pre_coalesce; int /*<<< orphan*/ * reply; int /*<<< orphan*/ * fragment; int /*<<< orphan*/  result; int /*<<< orphan*/ * add_auth; int /*<<< orphan*/ * parser; int /*<<< orphan*/ * token; int /*<<< orphan*/ * pos; scalar_t__ state; scalar_t__ start_ts; scalar_t__ mlen; int /*<<< orphan*/  mhdr; int /*<<< orphan*/  tmo_rbe; int /*<<< orphan*/ * owner; int /*<<< orphan*/ * peer; scalar_t__ id; } ;
struct keypos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MSG_PARSE_OK ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * array_create (int,int) ; 
 int /*<<< orphan*/  free_msgq ; 
 int /*<<< orphan*/  m_tqe ; 
 scalar_t__ msg_id ; 
 struct msg* nc_alloc (int) ; 
 int /*<<< orphan*/  nc_free (struct msg*) ; 
 scalar_t__ nfree_msgq ; 
 int /*<<< orphan*/  rbtree_node_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct msg *
_msg_get(void)
{
    struct msg *msg;

    if (!TAILQ_EMPTY(&free_msgq)) {
        ASSERT(nfree_msgq > 0);

        msg = TAILQ_FIRST(&free_msgq);
        nfree_msgq--;
        TAILQ_REMOVE(&free_msgq, msg, m_tqe);
        goto done;
    }

    msg = nc_alloc(sizeof(*msg));
    if (msg == NULL) {
        return NULL;
    }

done:
    /* c_tqe, s_tqe, and m_tqe are left uninitialized */
    msg->id = ++msg_id;
    msg->peer = NULL;
    msg->owner = NULL;

    rbtree_node_init(&msg->tmo_rbe);

    STAILQ_INIT(&msg->mhdr);
    msg->mlen = 0;
    msg->start_ts = 0;

    msg->state = 0;
    msg->pos = NULL;
    msg->token = NULL;

    msg->parser = NULL;
    msg->add_auth = NULL;
    msg->result = MSG_PARSE_OK;

    msg->fragment = NULL;
    msg->reply = NULL;
    msg->pre_coalesce = NULL;
    msg->post_coalesce = NULL;

    msg->type = MSG_UNKNOWN;

    msg->keys = array_create(1, sizeof(struct keypos));
    if (msg->keys == NULL) {
        nc_free(msg);
        return NULL;
    }

    msg->vlen = 0;
    msg->end = NULL;

    msg->frag_owner = NULL;
    msg->frag_seq = NULL;
    msg->nfrag = 0;
    msg->nfrag_done = 0;
    msg->frag_id = 0;

    msg->narg_start = NULL;
    msg->narg_end = NULL;
    msg->narg = 0;
    msg->rnarg = 0;
    msg->rlen = 0;
    msg->integer = 0;

    msg->err = 0;
    msg->error = 0;
    msg->ferror = 0;
    msg->request = 0;
    msg->quit = 0;
    msg->noreply = 0;
    msg->noforward = 0;
    msg->done = 0;
    msg->fdone = 0;
    msg->swallow = 0;
    msg->redis = 0;

    return msg;
}