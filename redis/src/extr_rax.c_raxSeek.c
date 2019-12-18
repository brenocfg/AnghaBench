#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {unsigned char* data; int size; scalar_t__ iscompr; } ;
typedef  TYPE_1__ raxNode ;
struct TYPE_22__ {size_t items; TYPE_1__** stack; scalar_t__ oom; } ;
struct TYPE_21__ {int /*<<< orphan*/  flags; TYPE_4__* node; scalar_t__ key; scalar_t__ key_len; void* data; TYPE_3__ stack; TYPE_10__* rt; } ;
typedef  TYPE_2__ raxIterator ;
typedef  int /*<<< orphan*/  aux ;
struct TYPE_23__ {int* data; int size; scalar_t__ iskey; scalar_t__ iscompr; } ;
struct TYPE_19__ {scalar_t__ numele; TYPE_4__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAX_ITER_EOF ; 
 int /*<<< orphan*/  RAX_ITER_JUST_SEEKED ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  debugf (char*,int,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 
 void* raxGetData (TYPE_4__*) ; 
 int /*<<< orphan*/  raxIteratorAddChars (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  raxIteratorNextStep (TYPE_2__*,int) ; 
 int /*<<< orphan*/  raxIteratorPrevStep (TYPE_2__*,int) ; 
 size_t raxLowWalk (TYPE_10__*,unsigned char*,size_t,TYPE_4__**,int /*<<< orphan*/ *,int*,TYPE_3__*) ; 
 TYPE_1__** raxNodeFirstChildPtr (TYPE_1__*) ; 
 int /*<<< orphan*/  raxSeekGreatest (TYPE_2__*) ; 
 int /*<<< orphan*/  raxStackPop (TYPE_3__*) ; 
 int /*<<< orphan*/  raxStackPush (TYPE_3__*,TYPE_4__*) ; 

int raxSeek(raxIterator *it, const char *op, unsigned char *ele, size_t len) {
    int eq = 0, lt = 0, gt = 0, first = 0, last = 0;

    it->stack.items = 0; /* Just resetting. Intialized by raxStart(). */
    it->flags |= RAX_ITER_JUST_SEEKED;
    it->flags &= ~RAX_ITER_EOF;
    it->key_len = 0;
    it->node = NULL;

    /* Set flags according to the operator used to perform the seek. */
    if (op[0] == '>') {
        gt = 1;
        if (op[1] == '=') eq = 1;
    } else if (op[0] == '<') {
        lt = 1;
        if (op[1] == '=') eq = 1;
    } else if (op[0] == '=') {
        eq = 1;
    } else if (op[0] == '^') {
        first = 1;
    } else if (op[0] == '$') {
        last = 1;
    } else {
        errno = 0;
        return 0; /* Error. */
    }

    /* If there are no elements, set the EOF condition immediately and
     * return. */
    if (it->rt->numele == 0) {
        it->flags |= RAX_ITER_EOF;
        return 1;
    }

    if (first) {
        /* Seeking the first key greater or equal to the empty string
         * is equivalent to seeking the smaller key available. */
        return raxSeek(it,">=",NULL,0);
    }

    if (last) {
        /* Find the greatest key taking always the last child till a
         * final node is found. */
        it->node = it->rt->head;
        if (!raxSeekGreatest(it)) return 0;
        assert(it->node->iskey);
        it->data = raxGetData(it->node);
        return 1;
    }

    /* We need to seek the specified key. What we do here is to actually
     * perform a lookup, and later invoke the prev/next key code that
     * we already use for iteration. */
    int splitpos = 0;
    size_t i = raxLowWalk(it->rt,ele,len,&it->node,NULL,&splitpos,&it->stack);

    /* Return OOM on incomplete stack info. */
    if (it->stack.oom) return 0;

    if (eq && i == len && (!it->node->iscompr || splitpos == 0) &&
        it->node->iskey)
    {
        /* We found our node, since the key matches and we have an
         * "equal" condition. */
        if (!raxIteratorAddChars(it,ele,len)) return 0; /* OOM. */
        it->data = raxGetData(it->node);
    } else if (lt || gt) {
        /* Exact key not found or eq flag not set. We have to set as current
         * key the one represented by the node we stopped at, and perform
         * a next/prev operation to seek. To reconstruct the key at this node
         * we start from the parent and go to the current node, accumulating
         * the characters found along the way. */
        if (!raxStackPush(&it->stack,it->node)) return 0;
        for (size_t j = 1; j < it->stack.items; j++) {
            raxNode *parent = it->stack.stack[j-1];
            raxNode *child = it->stack.stack[j];
            if (parent->iscompr) {
                if (!raxIteratorAddChars(it,parent->data,parent->size))
                    return 0;
            } else {
                raxNode **cp = raxNodeFirstChildPtr(parent);
                unsigned char *p = parent->data;
                while(1) {
                    raxNode *aux;
                    memcpy(&aux,cp,sizeof(aux));
                    if (aux == child) break;
                    cp++;
                    p++;
                }
                if (!raxIteratorAddChars(it,p,1)) return 0;
            }
        }
        raxStackPop(&it->stack);

        /* We need to set the iterator in the correct state to call next/prev
         * step in order to seek the desired element. */
        debugf("After initial seek: i=%d len=%d key=%.*s\n",
            (int)i, (int)len, (int)it->key_len, it->key);
        if (i != len && !it->node->iscompr) {
            /* If we stopped in the middle of a normal node because of a
             * mismatch, add the mismatching character to the current key
             * and call the iterator with the 'noup' flag so that it will try
             * to seek the next/prev child in the current node directly based
             * on the mismatching character. */
            if (!raxIteratorAddChars(it,ele+i,1)) return 0;
            debugf("Seek normal node on mismatch: %.*s\n",
                (int)it->key_len, (char*)it->key);

            it->flags &= ~RAX_ITER_JUST_SEEKED;
            if (lt && !raxIteratorPrevStep(it,1)) return 0;
            if (gt && !raxIteratorNextStep(it,1)) return 0;
            it->flags |= RAX_ITER_JUST_SEEKED; /* Ignore next call. */
        } else if (i != len && it->node->iscompr) {
            debugf("Compressed mismatch: %.*s\n",
                (int)it->key_len, (char*)it->key);
            /* In case of a mismatch within a compressed node. */
            int nodechar = it->node->data[splitpos];
            int keychar = ele[i];
            it->flags &= ~RAX_ITER_JUST_SEEKED;
            if (gt) {
                /* If the key the compressed node represents is greater
                 * than our seek element, continue forward, otherwise set the
                 * state in order to go back to the next sub-tree. */
                if (nodechar > keychar) {
                    if (!raxIteratorNextStep(it,0)) return 0;
                } else {
                    if (!raxIteratorAddChars(it,it->node->data,it->node->size))
                        return 0;
                    if (!raxIteratorNextStep(it,1)) return 0;
                }
            }
            if (lt) {
                /* If the key the compressed node represents is smaller
                 * than our seek element, seek the greater key in this
                 * subtree, otherwise set the state in order to go back to
                 * the previous sub-tree. */
                if (nodechar < keychar) {
                    if (!raxSeekGreatest(it)) return 0;
                    it->data = raxGetData(it->node);
                } else {
                    if (!raxIteratorAddChars(it,it->node->data,it->node->size))
                        return 0;
                    if (!raxIteratorPrevStep(it,1)) return 0;
                }
            }
            it->flags |= RAX_ITER_JUST_SEEKED; /* Ignore next call. */
        } else {
            debugf("No mismatch: %.*s\n",
                (int)it->key_len, (char*)it->key);
            /* If there was no mismatch we are into a node representing the
             * key, (but which is not a key or the seek operator does not
             * include 'eq'), or we stopped in the middle of a compressed node
             * after processing all the key. Continue iterating as this was
             * a legitimate key we stopped at. */
            it->flags &= ~RAX_ITER_JUST_SEEKED;
            if (it->node->iscompr && it->node->iskey && splitpos && lt) {
                /* If we stopped in the middle of a compressed node with
                 * perfect match, and the condition is to seek a key "<" than
                 * the specified one, then if this node is a key it already
                 * represents our match. For instance we may have nodes:
                 *
                 * "f" -> "oobar" = 1 -> "" = 2
                 *
                 * Representing keys "f" = 1, "foobar" = 2. A seek for
                 * the key < "foo" will stop in the middle of the "oobar"
                 * node, but will be our match, representing the key "f".
                 *
                 * So in that case, we don't seek backward. */
            } else {
                if (gt && !raxIteratorNextStep(it,0)) return 0;
                if (lt && !raxIteratorPrevStep(it,0)) return 0;
            }
            it->flags |= RAX_ITER_JUST_SEEKED; /* Ignore next call. */
        }
    } else {
        /* If we are here just eq was set but no match was found. */
        it->flags |= RAX_ITER_EOF;
        return 1;
    }
    return 1;
}