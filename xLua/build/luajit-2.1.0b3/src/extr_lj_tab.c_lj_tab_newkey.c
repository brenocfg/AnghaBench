#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_34__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_35__ {scalar_t__ u64; } ;
typedef  TYPE_1__ cTValue ;
struct TYPE_38__ {scalar_t__ hmask; int /*<<< orphan*/  node; } ;
struct TYPE_37__ {TYPE_1__ val; TYPE_1__ key; int /*<<< orphan*/  next; } ;
struct TYPE_36__ {TYPE_3__ nilnode; } ;
typedef  TYPE_1__ TValue ;
typedef  TYPE_3__ Node ;
typedef  TYPE_4__ GCtab ;

/* Variables and functions */
 TYPE_34__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 TYPE_3__* getfreetop (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* hashkey (TYPE_4__*,TYPE_1__*) ; 
 TYPE_3__* hashstr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_1__* lj_tab_set (int /*<<< orphan*/ *,TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_3__* nextnode (TYPE_3__*) ; 
 TYPE_3__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rehashtab (int /*<<< orphan*/ *,TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  setfreetop (TYPE_4__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  setmrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (TYPE_1__*) ; 
 int /*<<< orphan*/  strV (TYPE_1__*) ; 
 int /*<<< orphan*/  tvismzero (TYPE_1__*) ; 
 int tvisnil (TYPE_1__*) ; 
 scalar_t__ tvisstr (TYPE_1__*) ; 

TValue *lj_tab_newkey(lua_State *L, GCtab *t, cTValue *key)
{
  Node *n = hashkey(t, key);
  if (!tvisnil(&n->val) || t->hmask == 0) {
    Node *nodebase = noderef(t->node);
    Node *collide, *freenode = getfreetop(t, nodebase);
    lua_assert(freenode >= nodebase && freenode <= nodebase+t->hmask+1);
    do {
      if (freenode == nodebase) {  /* No free node found? */
	rehashtab(L, t, key);  /* Rehash table. */
	return lj_tab_set(L, t, key);  /* Retry key insertion. */
      }
    } while (!tvisnil(&(--freenode)->key));
    setfreetop(t, nodebase, freenode);
    lua_assert(freenode != &G(L)->nilnode);
    collide = hashkey(t, &n->key);
    if (collide != n) {  /* Colliding node not the main node? */
      while (noderef(collide->next) != n)  /* Find predecessor. */
	collide = nextnode(collide);
      setmref(collide->next, freenode);  /* Relink chain. */
      /* Copy colliding node into free node and free main node. */
      freenode->val = n->val;
      freenode->key = n->key;
      freenode->next = n->next;
      setmref(n->next, NULL);
      setnilV(&n->val);
      /* Rechain pseudo-resurrected string keys with colliding hashes. */
      while (nextnode(freenode)) {
	Node *nn = nextnode(freenode);
	if (tvisstr(&nn->key) && !tvisnil(&nn->val) &&
	    hashstr(t, strV(&nn->key)) == n) {
	  freenode->next = nn->next;
	  nn->next = n->next;
	  setmref(n->next, nn);
	} else {
	  freenode = nn;
	}
      }
    } else {  /* Otherwise use free node. */
      setmrefr(freenode->next, n->next);  /* Insert into chain. */
      setmref(n->next, freenode);
      n = freenode;
    }
  }
  n->key.u64 = key->u64;
  if (LJ_UNLIKELY(tvismzero(&n->key)))
    n->key.u64 = 0;
  lj_gc_anybarriert(L, t);
  lua_assert(tvisnil(&n->val));
  return &n->val;
}