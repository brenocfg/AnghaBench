#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* msegmentptr ;
typedef  TYPE_3__* mchunkptr ;
struct TYPE_18__ {size_t head; } ;
struct TYPE_17__ {char* base; int size; struct TYPE_17__* next; } ;
struct TYPE_16__ {size_t topsize; TYPE_3__* top; TYPE_2__ seg; } ;

/* Variables and functions */
 scalar_t__ CALL_MMAP (size_t) ; 
 char* CMFAIL ; 
 size_t DEFAULT_MMAP_THRESHOLD ; 
 scalar_t__ LJ_LIKELY (int) ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 size_t PINUSE_BIT ; 
 size_t SIZE_T_ONE ; 
 size_t TOP_FOOT_SIZE ; 
 int /*<<< orphan*/  add_segment (TYPE_1__*,char*,size_t) ; 
 void* chunk2mem (TYPE_3__*) ; 
 TYPE_3__* chunk_plus_offset (TYPE_3__*,size_t) ; 
 void* direct_alloc (size_t) ; 
 size_t granularity_align (size_t) ; 
 int /*<<< orphan*/  init_top (TYPE_1__*,TYPE_3__*,size_t) ; 
 void* prepend_alloc (TYPE_1__*,char*,char*,size_t) ; 
 scalar_t__ segment_holds (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_inuse_chunk (TYPE_1__*,TYPE_3__*,size_t) ; 

__attribute__((used)) static void *alloc_sys(mstate m, size_t nb)
{
  char *tbase = CMFAIL;
  size_t tsize = 0;

  /* Directly map large chunks */
  if (LJ_UNLIKELY(nb >= DEFAULT_MMAP_THRESHOLD)) {
    void *mem = direct_alloc(nb);
    if (mem != 0)
      return mem;
  }

  {
    size_t req = nb + TOP_FOOT_SIZE + SIZE_T_ONE;
    size_t rsize = granularity_align(req);
    if (LJ_LIKELY(rsize > nb)) { /* Fail if wraps around zero */
      char *mp = (char *)(CALL_MMAP(rsize));
      if (mp != CMFAIL) {
	tbase = mp;
	tsize = rsize;
      }
    }
  }

  if (tbase != CMFAIL) {
    msegmentptr sp = &m->seg;
    /* Try to merge with an existing segment */
    while (sp != 0 && tbase != sp->base + sp->size)
      sp = sp->next;
    if (sp != 0 && segment_holds(sp, m->top)) { /* append */
      sp->size += tsize;
      init_top(m, m->top, m->topsize + tsize);
    } else {
      sp = &m->seg;
      while (sp != 0 && sp->base != tbase + tsize)
	sp = sp->next;
      if (sp != 0) {
	char *oldbase = sp->base;
	sp->base = tbase;
	sp->size += tsize;
	return prepend_alloc(m, tbase, oldbase, nb);
      } else {
	add_segment(m, tbase, tsize);
      }
    }

    if (nb < m->topsize) { /* Allocate from new or extended top space */
      size_t rsize = m->topsize -= nb;
      mchunkptr p = m->top;
      mchunkptr r = m->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(m, p, nb);
      return chunk2mem(p);
    }
  }

  return NULL;
}