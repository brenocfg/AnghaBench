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
typedef  int uint32_t ;
struct msg_tqh {int dummy; } ;
struct msg {int narg; scalar_t__ type; scalar_t__ nfrag; struct msg* frag_owner; int /*<<< orphan*/  frag_id; struct msg** frag_seq; int /*<<< orphan*/  redis; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; int /*<<< orphan*/  keys; int /*<<< orphan*/  mhdr; } ;
struct mbuf {char* pos; char* start; } ;
struct keypos {scalar_t__ start; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MSG_REQ_REDIS_DEL ; 
 scalar_t__ MSG_REQ_REDIS_MGET ; 
 scalar_t__ MSG_REQ_REDIS_MSET ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
 struct mbuf* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct msg_tqh*,struct msg*,int /*<<< orphan*/ ) ; 
 struct keypos* array_get (int /*<<< orphan*/ ,int) ; 
 int array_n (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tqe ; 
 int msg_backend_idx (struct msg*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_gen_frag_id () ; 
 struct msg* msg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_prepend_format (struct msg*,char*,int) ; 
 struct msg** nc_alloc (int) ; 
 int /*<<< orphan*/  nc_free (struct msg**) ; 
 struct msg** nc_zalloc (int) ; 
 int /*<<< orphan*/  redis_append_key (struct msg*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  redis_copy_bulk (struct msg*,struct msg*) ; 

__attribute__((used)) static rstatus_t
redis_fragment_argx(struct msg *r, uint32_t ncontinuum, struct msg_tqh *frag_msgq,
                    uint32_t key_step)
{
    struct mbuf *mbuf;
    struct msg **sub_msgs;
    uint32_t i;
    rstatus_t status;

    ASSERT(array_n(r->keys) == (r->narg - 1) / key_step);

    sub_msgs = nc_zalloc(ncontinuum * sizeof(*sub_msgs));
    if (sub_msgs == NULL) {
        return NC_ENOMEM;
    }

    ASSERT(r->frag_seq == NULL);
    r->frag_seq = nc_alloc(array_n(r->keys) * sizeof(*r->frag_seq));
    if (r->frag_seq == NULL) {
        nc_free(sub_msgs);
        return NC_ENOMEM;
    }

    mbuf = STAILQ_FIRST(&r->mhdr);
    mbuf->pos = mbuf->start;

    /*
     * This code is based on the assumption that '*narg\r\n$4\r\nMGET\r\n' is located
     * in a contiguous location.
     * This is always true because we have capped our MBUF_MIN_SIZE at 512 and
     * whenever we have multiple messages, we copy the tail message into a new mbuf
     */
    for (i = 0; i < 3; i++) {                 /* eat *narg\r\n$4\r\nMGET\r\n */
        for (; *(mbuf->pos) != '\n';) {
            mbuf->pos++;
        }
        mbuf->pos++;
    }

    r->frag_id = msg_gen_frag_id();
    r->nfrag = 0;
    r->frag_owner = r;

    for (i = 0; i < array_n(r->keys); i++) {        /* for each key */
        struct msg *sub_msg;
        struct keypos *kpos = array_get(r->keys, i);
        uint32_t idx = msg_backend_idx(r, kpos->start, kpos->end - kpos->start);

        if (sub_msgs[idx] == NULL) {
            sub_msgs[idx] = msg_get(r->owner, r->request, r->redis);
            if (sub_msgs[idx] == NULL) {
                nc_free(sub_msgs);
                return NC_ENOMEM;
            }
        }
        r->frag_seq[i] = sub_msg = sub_msgs[idx];

        sub_msg->narg++;
        status = redis_append_key(sub_msg, kpos->start, kpos->end - kpos->start);
        if (status != NC_OK) {
            nc_free(sub_msgs);
            return status;
        }

        if (key_step == 1) {                            /* mget,del */
            continue;
        } else {                                        /* mset */
            status = redis_copy_bulk(NULL, r);          /* eat key */
            if (status != NC_OK) {
                nc_free(sub_msgs);
                return status;
            }

            status = redis_copy_bulk(sub_msg, r);
            if (status != NC_OK) {
                nc_free(sub_msgs);
                return status;
            }

            sub_msg->narg++;
        }
    }

    for (i = 0; i < ncontinuum; i++) {     /* prepend mget header, and forward it */
        struct msg *sub_msg = sub_msgs[i];
        if (sub_msg == NULL) {
            continue;
        }

        if (r->type == MSG_REQ_REDIS_MGET) {
            status = msg_prepend_format(sub_msg, "*%d\r\n$4\r\nmget\r\n",
                                        sub_msg->narg + 1);
        } else if (r->type == MSG_REQ_REDIS_DEL) {
            status = msg_prepend_format(sub_msg, "*%d\r\n$3\r\ndel\r\n",
                                        sub_msg->narg + 1);
        } else if (r->type == MSG_REQ_REDIS_MSET) {
            status = msg_prepend_format(sub_msg, "*%d\r\n$4\r\nmset\r\n",
                                        sub_msg->narg + 1);
        } else {
            NOT_REACHED();
        }
        if (status != NC_OK) {
            nc_free(sub_msgs);
            return status;
        }

        sub_msg->type = r->type;
        sub_msg->frag_id = r->frag_id;
        sub_msg->frag_owner = r->frag_owner;

        TAILQ_INSERT_TAIL(frag_msgq, sub_msg, m_tqe);
        r->nfrag++;
    }

    nc_free(sub_msgs);
    return NC_OK;
}