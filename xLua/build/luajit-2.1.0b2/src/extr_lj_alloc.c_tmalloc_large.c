#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tchunkptr ;
typedef  TYPE_2__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
typedef  scalar_t__ binmap_t ;
typedef  int /*<<< orphan*/  bindex_t ;
struct TYPE_19__ {scalar_t__ treemap; size_t dvsize; } ;
struct TYPE_18__ {struct TYPE_18__** child; } ;

/* Variables and functions */
 size_t MIN_CHUNK_SIZE ; 
 size_t SIZE_T_BITSIZE ; 
 size_t SIZE_T_ONE ; 
 void* chunk2mem (TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_plus_offset (TYPE_1__*,size_t) ; 
 size_t chunksize (TYPE_1__*) ; 
 int /*<<< orphan*/  compute_tree_index (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx2bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_chunk (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ left_bits (int /*<<< orphan*/ ) ; 
 TYPE_1__* leftmost_child (TYPE_1__*) ; 
 size_t leftshift_for_tree_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ffs (scalar_t__) ; 
 int /*<<< orphan*/  set_inuse_and_pinuse (TYPE_2__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_free_chunk (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_inuse_chunk (TYPE_2__*,TYPE_1__*,size_t) ; 
 TYPE_1__** treebin_at (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_large_chunk (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void *tmalloc_large(mstate m, size_t nb)
{
  tchunkptr v = 0;
  size_t rsize = ~nb+1; /* Unsigned negation */
  tchunkptr t;
  bindex_t idx;
  compute_tree_index(nb, idx);

  if ((t = *treebin_at(m, idx)) != 0) {
    /* Traverse tree for this bin looking for node with size == nb */
    size_t sizebits = nb << leftshift_for_tree_index(idx);
    tchunkptr rst = 0;  /* The deepest untaken right subtree */
    for (;;) {
      tchunkptr rt;
      size_t trem = chunksize(t) - nb;
      if (trem < rsize) {
	v = t;
	if ((rsize = trem) == 0)
	  break;
      }
      rt = t->child[1];
      t = t->child[(sizebits >> (SIZE_T_BITSIZE-SIZE_T_ONE)) & 1];
      if (rt != 0 && rt != t)
	rst = rt;
      if (t == 0) {
	t = rst; /* set t to least subtree holding sizes > nb */
	break;
      }
      sizebits <<= 1;
    }
  }

  if (t == 0 && v == 0) { /* set t to root of next non-empty treebin */
    binmap_t leftbits = left_bits(idx2bit(idx)) & m->treemap;
    if (leftbits != 0)
      t = *treebin_at(m, lj_ffs(leftbits));
  }

  while (t != 0) { /* find smallest of tree or subtree */
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
    t = leftmost_child(t);
  }

  /*  If dv is a better fit, return NULL so malloc will use it */
  if (v != 0 && rsize < (size_t)(m->dvsize - nb)) {
    mchunkptr r = chunk_plus_offset(v, nb);
    unlink_large_chunk(m, v);
    if (rsize < MIN_CHUNK_SIZE) {
      set_inuse_and_pinuse(m, v, (rsize + nb));
    } else {
      set_size_and_pinuse_of_inuse_chunk(m, v, nb);
      set_size_and_pinuse_of_free_chunk(r, rsize);
      insert_chunk(m, r, rsize);
    }
    return chunk2mem(v);
  }
  return NULL;
}