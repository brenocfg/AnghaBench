#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tchunkptr ;
typedef  TYPE_1__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
typedef  int /*<<< orphan*/  bindex_t ;
struct TYPE_8__ {int /*<<< orphan*/  treemap; } ;

/* Variables and functions */
 size_t MIN_CHUNK_SIZE ; 
 void* chunk2mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_plus_offset (int /*<<< orphan*/ ,size_t) ; 
 size_t chunksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leftmost_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_dv (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_inuse_and_pinuse (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_free_chunk (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_inuse_chunk (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * treebin_at (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_large_chunk (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *tmalloc_small(mstate m, size_t nb)
{
  tchunkptr t, v;
  mchunkptr r;
  size_t rsize;
  bindex_t i = lj_ffs(m->treemap);

  v = t = *treebin_at(m, i);
  rsize = chunksize(t) - nb;

  while ((t = leftmost_child(t)) != 0) {
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
  }

  r = chunk_plus_offset(v, nb);
  unlink_large_chunk(m, v);
  if (rsize < MIN_CHUNK_SIZE) {
    set_inuse_and_pinuse(m, v, (rsize + nb));
  } else {
    set_size_and_pinuse_of_inuse_chunk(m, v, nb);
    set_size_and_pinuse_of_free_chunk(r, rsize);
    replace_dv(m, r, rsize);
  }
  return chunk2mem(v);
}