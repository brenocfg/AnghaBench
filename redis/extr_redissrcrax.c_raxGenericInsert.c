#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trimmed ;
typedef  int /*<<< orphan*/  splitnode ;
struct TYPE_26__ {int iscompr; int iskey; int isnull; int size; struct TYPE_26__** data; } ;
typedef  TYPE_1__ raxNode ;
struct TYPE_27__ {int /*<<< orphan*/  numele; int /*<<< orphan*/  numnodes; } ;
typedef  TYPE_2__ rax ;
typedef  int /*<<< orphan*/  postfix ;
typedef  int /*<<< orphan*/  next ;
typedef  int /*<<< orphan*/  h ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 size_t RAX_NODE_MAX_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugf (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 
 TYPE_1__* raxAddChild (TYPE_1__*,unsigned char,TYPE_1__**,TYPE_1__***) ; 
 TYPE_1__* raxCompressNode (TYPE_1__*,unsigned char*,size_t,TYPE_1__**) ; 
 void* raxGetData (TYPE_1__*) ; 
 size_t raxLowWalk (TYPE_2__*,unsigned char*,size_t,TYPE_1__**,TYPE_1__***,int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* raxNewNode (int,int) ; 
 TYPE_1__** raxNodeLastChildPtr (TYPE_1__*) ; 
 int raxPadding (int) ; 
 TYPE_1__* raxReallocForData (TYPE_1__*,void*) ; 
 scalar_t__ raxRemove (TYPE_2__*,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxSetData (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  rax_free (TYPE_1__*) ; 
 TYPE_1__* rax_malloc (size_t) ; 

int raxGenericInsert(rax *rax, unsigned char *s, size_t len, void *data, void **old, int overwrite) {
    size_t i;
    int j = 0; /* Split position. If raxLowWalk() stops in a compressed
                  node, the index 'j' represents the char we stopped within the
                  compressed node, that is, the position where to split the
                  node for insertion. */
    raxNode *h, **parentlink;

    debugf("### Insert %.*s with value %p\n", (int)len, s, data);
    i = raxLowWalk(rax,s,len,&h,&parentlink,&j,NULL);

    /* If i == len we walked following the whole string. If we are not
     * in the middle of a compressed node, the string is either already
     * inserted or this middle node is currently not a key, but can represent
     * our key. We have just to reallocate the node and make space for the
     * data pointer. */
    if (i == len && (!h->iscompr || j == 0 /* not in the middle if j is 0 */)) {
        debugf("### Insert: node representing key exists\n");
        /* Make space for the value pointer if needed. */
        if (!h->iskey || (h->isnull && overwrite)) {
            h = raxReallocForData(h,data);
            if (h) memcpy(parentlink,&h,sizeof(h));
        }
        if (h == NULL) {
            errno = ENOMEM;
            return 0;
        }

        /* Update the existing key if there is already one. */
        if (h->iskey) {
            if (old) *old = raxGetData(h);
            if (overwrite) raxSetData(h,data);
            errno = 0;
            return 0; /* Element already exists. */
        }

        /* Otherwise set the node as a key. Note that raxSetData()
         * will set h->iskey. */
        raxSetData(h,data);
        rax->numele++;
        return 1; /* Element inserted. */
    }

    /* If the node we stopped at is a compressed node, we need to
     * split it before to continue.
     *
     * Splitting a compressed node have a few possible cases.
     * Imagine that the node 'h' we are currently at is a compressed
     * node contaning the string "ANNIBALE" (it means that it represents
     * nodes A -> N -> N -> I -> B -> A -> L -> E with the only child
     * pointer of this node pointing at the 'E' node, because remember that
     * we have characters at the edges of the graph, not inside the nodes
     * themselves.
     *
     * In order to show a real case imagine our node to also point to
     * another compressed node, that finally points at the node without
     * children, representing 'O':
     *
     *     "ANNIBALE" -> "SCO" -> []
     *
     * When inserting we may face the following cases. Note that all the cases
     * require the insertion of a non compressed node with exactly two
     * children, except for the last case which just requires splitting a
     * compressed node.
     *
     * 1) Inserting "ANNIENTARE"
     *
     *               |B| -> "ALE" -> "SCO" -> []
     *     "ANNI" -> |-|
     *               |E| -> (... continue algo ...) "NTARE" -> []
     *
     * 2) Inserting "ANNIBALI"
     *
     *                  |E| -> "SCO" -> []
     *     "ANNIBAL" -> |-|
     *                  |I| -> (... continue algo ...) []
     *
     * 3) Inserting "AGO" (Like case 1, but set iscompr = 0 into original node)
     *
     *            |N| -> "NIBALE" -> "SCO" -> []
     *     |A| -> |-|
     *            |G| -> (... continue algo ...) |O| -> []
     *
     * 4) Inserting "CIAO"
     *
     *     |A| -> "NNIBALE" -> "SCO" -> []
     *     |-|
     *     |C| -> (... continue algo ...) "IAO" -> []
     *
     * 5) Inserting "ANNI"
     *
     *     "ANNI" -> "BALE" -> "SCO" -> []
     *
     * The final algorithm for insertion covering all the above cases is as
     * follows.
     *
     * ============================= ALGO 1 =============================
     *
     * For the above cases 1 to 4, that is, all cases where we stopped in
     * the middle of a compressed node for a character mismatch, do:
     *
     * Let $SPLITPOS be the zero-based index at which, in the
     * compressed node array of characters, we found the mismatching
     * character. For example if the node contains "ANNIBALE" and we add
     * "ANNIENTARE" the $SPLITPOS is 4, that is, the index at which the
     * mismatching character is found.
     *
     * 1. Save the current compressed node $NEXT pointer (the pointer to the
     *    child element, that is always present in compressed nodes).
     *
     * 2. Create "split node" having as child the non common letter
     *    at the compressed node. The other non common letter (at the key)
     *    will be added later as we continue the normal insertion algorithm
     *    at step "6".
     *
     * 3a. IF $SPLITPOS == 0:
     *     Replace the old node with the split node, by copying the auxiliary
     *     data if any. Fix parent's reference. Free old node eventually
     *     (we still need its data for the next steps of the algorithm).
     *
     * 3b. IF $SPLITPOS != 0:
     *     Trim the compressed node (reallocating it as well) in order to
     *     contain $splitpos characters. Change chilid pointer in order to link
     *     to the split node. If new compressed node len is just 1, set
     *     iscompr to 0 (layout is the same). Fix parent's reference.
     *
     * 4a. IF the postfix len (the length of the remaining string of the
     *     original compressed node after the split character) is non zero,
     *     create a "postfix node". If the postfix node has just one character
     *     set iscompr to 0, otherwise iscompr to 1. Set the postfix node
     *     child pointer to $NEXT.
     *
     * 4b. IF the postfix len is zero, just use $NEXT as postfix pointer.
     *
     * 5. Set child[0] of split node to postfix node.
     *
     * 6. Set the split node as the current node, set current index at child[1]
     *    and continue insertion algorithm as usually.
     *
     * ============================= ALGO 2 =============================
     *
     * For case 5, that is, if we stopped in the middle of a compressed
     * node but no mismatch was found, do:
     *
     * Let $SPLITPOS be the zero-based index at which, in the
     * compressed node array of characters, we stopped iterating because
     * there were no more keys character to match. So in the example of
     * the node "ANNIBALE", addig the string "ANNI", the $SPLITPOS is 4.
     *
     * 1. Save the current compressed node $NEXT pointer (the pointer to the
     *    child element, that is always present in compressed nodes).
     *
     * 2. Create a "postfix node" containing all the characters from $SPLITPOS
     *    to the end. Use $NEXT as the postfix node child pointer.
     *    If the postfix node length is 1, set iscompr to 0.
     *    Set the node as a key with the associated value of the new
     *    inserted key.
     *
     * 3. Trim the current node to contain the first $SPLITPOS characters.
     *    As usually if the new node length is just 1, set iscompr to 0.
     *    Take the iskey / associated value as it was in the orignal node.
     *    Fix the parent's reference.
     *
     * 4. Set the postfix node as the only child pointer of the trimmed
     *    node created at step 1.
     */

    /* ------------------------- ALGORITHM 1 --------------------------- */
    if (h->iscompr && i != len) {
        debugf("ALGO 1: Stopped at compressed node %.*s (%p)\n",
            h->size, h->data, (void*)h);
        debugf("Still to insert: %.*s\n", (int)(len-i), s+i);
        debugf("Splitting at %d: '%c'\n", j, ((char*)h->data)[j]);
        debugf("Other (key) letter is '%c'\n", s[i]);

        /* 1: Save next pointer. */
        raxNode **childfield = raxNodeLastChildPtr(h);
        raxNode *next;
        memcpy(&next,childfield,sizeof(next));
        debugf("Next is %p\n", (void*)next);
        debugf("iskey %d\n", h->iskey);
        if (h->iskey) {
            debugf("key value is %p\n", raxGetData(h));
        }

        /* Set the length of the additional nodes we will need. */
        size_t trimmedlen = j;
        size_t postfixlen = h->size - j - 1;
        int split_node_is_key = !trimmedlen && h->iskey && !h->isnull;
        size_t nodesize;

        /* 2: Create the split node. Also allocate the other nodes we'll need
         *    ASAP, so that it will be simpler to handle OOM. */
        raxNode *splitnode = raxNewNode(1, split_node_is_key);
        raxNode *trimmed = NULL;
        raxNode *postfix = NULL;

        if (trimmedlen) {
            nodesize = sizeof(raxNode)+trimmedlen+raxPadding(trimmedlen)+
                       sizeof(raxNode*);
            if (h->iskey && !h->isnull) nodesize += sizeof(void*);
            trimmed = rax_malloc(nodesize);
        }

        if (postfixlen) {
            nodesize = sizeof(raxNode)+postfixlen+raxPadding(postfixlen)+
                       sizeof(raxNode*);
            postfix = rax_malloc(nodesize);
        }

        /* OOM? Abort now that the tree is untouched. */
        if (splitnode == NULL ||
            (trimmedlen && trimmed == NULL) ||
            (postfixlen && postfix == NULL))
        {
            rax_free(splitnode);
            rax_free(trimmed);
            rax_free(postfix);
            errno = ENOMEM;
            return 0;
        }
        splitnode->data[0] = h->data[j];

        if (j == 0) {
            /* 3a: Replace the old node with the split node. */
            if (h->iskey) {
                void *ndata = raxGetData(h);
                raxSetData(splitnode,ndata);
            }
            memcpy(parentlink,&splitnode,sizeof(splitnode));
        } else {
            /* 3b: Trim the compressed node. */
            trimmed->size = j;
            memcpy(trimmed->data,h->data,j);
            trimmed->iscompr = j > 1 ? 1 : 0;
            trimmed->iskey = h->iskey;
            trimmed->isnull = h->isnull;
            if (h->iskey && !h->isnull) {
                void *ndata = raxGetData(h);
                raxSetData(trimmed,ndata);
            }
            raxNode **cp = raxNodeLastChildPtr(trimmed);
            memcpy(cp,&splitnode,sizeof(splitnode));
            memcpy(parentlink,&trimmed,sizeof(trimmed));
            parentlink = cp; /* Set parentlink to splitnode parent. */
            rax->numnodes++;
        }

        /* 4: Create the postfix node: what remains of the original
         * compressed node after the split. */
        if (postfixlen) {
            /* 4a: create a postfix node. */
            postfix->iskey = 0;
            postfix->isnull = 0;
            postfix->size = postfixlen;
            postfix->iscompr = postfixlen > 1;
            memcpy(postfix->data,h->data+j+1,postfixlen);
            raxNode **cp = raxNodeLastChildPtr(postfix);
            memcpy(cp,&next,sizeof(next));
            rax->numnodes++;
        } else {
            /* 4b: just use next as postfix node. */
            postfix = next;
        }

        /* 5: Set splitnode first child as the postfix node. */
        raxNode **splitchild = raxNodeLastChildPtr(splitnode);
        memcpy(splitchild,&postfix,sizeof(postfix));

        /* 6. Continue insertion: this will cause the splitnode to
         * get a new child (the non common character at the currently
         * inserted key). */
        rax_free(h);
        h = splitnode;
    } else if (h->iscompr && i == len) {
    /* ------------------------- ALGORITHM 2 --------------------------- */
        debugf("ALGO 2: Stopped at compressed node %.*s (%p) j = %d\n",
            h->size, h->data, (void*)h, j);

        /* Allocate postfix & trimmed nodes ASAP to fail for OOM gracefully. */
        size_t postfixlen = h->size - j;
        size_t nodesize = sizeof(raxNode)+postfixlen+raxPadding(postfixlen)+
                          sizeof(raxNode*);
        if (data != NULL) nodesize += sizeof(void*);
        raxNode *postfix = rax_malloc(nodesize);

        nodesize = sizeof(raxNode)+j+raxPadding(j)+sizeof(raxNode*);
        if (h->iskey && !h->isnull) nodesize += sizeof(void*);
        raxNode *trimmed = rax_malloc(nodesize);

        if (postfix == NULL || trimmed == NULL) {
            rax_free(postfix);
            rax_free(trimmed);
            errno = ENOMEM;
            return 0;
        }

        /* 1: Save next pointer. */
        raxNode **childfield = raxNodeLastChildPtr(h);
        raxNode *next;
        memcpy(&next,childfield,sizeof(next));

        /* 2: Create the postfix node. */
        postfix->size = postfixlen;
        postfix->iscompr = postfixlen > 1;
        postfix->iskey = 1;
        postfix->isnull = 0;
        memcpy(postfix->data,h->data+j,postfixlen);
        raxSetData(postfix,data);
        raxNode **cp = raxNodeLastChildPtr(postfix);
        memcpy(cp,&next,sizeof(next));
        rax->numnodes++;

        /* 3: Trim the compressed node. */
        trimmed->size = j;
        trimmed->iscompr = j > 1;
        trimmed->iskey = 0;
        trimmed->isnull = 0;
        memcpy(trimmed->data,h->data,j);
        memcpy(parentlink,&trimmed,sizeof(trimmed));
        if (h->iskey) {
            void *aux = raxGetData(h);
            raxSetData(trimmed,aux);
        }

        /* Fix the trimmed node child pointer to point to
         * the postfix node. */
        cp = raxNodeLastChildPtr(trimmed);
        memcpy(cp,&postfix,sizeof(postfix));

        /* Finish! We don't need to continue with the insertion
         * algorithm for ALGO 2. The key is already inserted. */
        rax->numele++;
        rax_free(h);
        return 1; /* Key inserted. */
    }

    /* We walked the radix tree as far as we could, but still there are left
     * chars in our string. We need to insert the missing nodes. */
    while(i < len) {
        raxNode *child;

        /* If this node is going to have a single child, and there
         * are other characters, so that that would result in a chain
         * of single-childed nodes, turn it into a compressed node. */
        if (h->size == 0 && len-i > 1) {
            debugf("Inserting compressed node\n");
            size_t comprsize = len-i;
            if (comprsize > RAX_NODE_MAX_SIZE)
                comprsize = RAX_NODE_MAX_SIZE;
            raxNode *newh = raxCompressNode(h,s+i,comprsize,&child);
            if (newh == NULL) goto oom;
            h = newh;
            memcpy(parentlink,&h,sizeof(h));
            parentlink = raxNodeLastChildPtr(h);
            i += comprsize;
        } else {
            debugf("Inserting normal node\n");
            raxNode **new_parentlink;
            raxNode *newh = raxAddChild(h,s[i],&child,&new_parentlink);
            if (newh == NULL) goto oom;
            h = newh;
            memcpy(parentlink,&h,sizeof(h));
            parentlink = new_parentlink;
            i++;
        }
        rax->numnodes++;
        h = child;
    }
    raxNode *newh = raxReallocForData(h,data);
    if (newh == NULL) goto oom;
    h = newh;
    if (!h->iskey) rax->numele++;
    raxSetData(h,data);
    memcpy(parentlink,&h,sizeof(h));
    return 1; /* Element inserted. */

oom:
    /* This code path handles out of memory after part of the sub-tree was
     * already modified. Set the node as a key, and then remove it. However we
     * do that only if the node is a terminal node, otherwise if the OOM
     * happened reallocating a node in the middle, we don't need to free
     * anything. */
    if (h->size == 0) {
        h->isnull = 1;
        h->iskey = 1;
        rax->numele++; /* Compensate the next remove. */
        assert(raxRemove(rax,s,i,NULL) != 0);
    }
    errno = ENOMEM;
    return 0;
}