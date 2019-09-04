#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stb_uintptr ;
typedef  int /*<<< orphan*/  stb__nochildren ;
typedef  int /*<<< orphan*/  stb__chunked ;
typedef  int stb__alloc_type ;
struct TYPE_9__ {int /*<<< orphan*/ * child; } ;
typedef  TYPE_1__ stb__alloc ;

/* Variables and functions */
#define  STB__alloc 131 
#define  STB__chunk_raw 130 
#define  STB__chunked 129 
#define  STB__nochildren 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t) ; 
 void* stb__alloc_chunk (TYPE_1__*,int,int,int) ; 
 TYPE_1__* stb__get_context (void*) ; 
 int /*<<< orphan*/  stb__insert_alloc (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stb__insert_nochild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb__setchunks (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb__setparent (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stb_alloc_count_alloc ; 
 int /*<<< orphan*/  stb_is_pow2 (int) ; 
 int stb_lowbit8 (unsigned int) ; 

__attribute__((used)) static void * malloc_base(void *context, size_t size, stb__alloc_type t, int align)
{
   void *p;

   stb__alloc *src = stb__get_context(context);

   if (align <= 0) {
      // compute worst-case C packed alignment
      // e.g. a 24-byte struct is 8-aligned
      int align_proposed = 1 << stb_lowbit8((unsigned int) size);

      if (align_proposed < 0)
         align_proposed = 4;

      if (align_proposed == 0) {
         if (size == 0)
            align_proposed = 1;
         else
            align_proposed = 256;
      }

      // a negative alignment means 'don't align any larger
      // than this'; so -16 means we align 1,2,4,8, or 16

      if (align < 0) {
         if (align_proposed > -align)
            align_proposed = -align;
      }

      align = align_proposed;
   }

   assert(stb_is_pow2(align));

   // don't cause misalignment when allocating nochildren
   if (t == STB__nochildren && align > 8)
      t = STB__alloc;

   switch (t) {
      case STB__alloc: {
         stb__alloc *s = (stb__alloc *) malloc(size + sizeof(*s));
         if (s == NULL) return NULL;
         p = s+1;
         s->child = NULL;
         stb__insert_alloc(src, s);

         stb__setchunks(s,NULL);
         break;
      }

      case STB__nochildren: {
         stb__nochildren *s = (stb__nochildren *) malloc(size + sizeof(*s));
         if (s == NULL) return NULL;
         p = s+1;
         stb__insert_nochild(src, s);
         break;
      }

      case STB__chunk_raw: {
         p = stb__alloc_chunk(src, (int) size, align, 0);
         if (p == NULL) return NULL;
         break;
      }

      case STB__chunked: {
         stb__chunked *s;
         if (align < sizeof(stb_uintptr)) align = sizeof(stb_uintptr);
         s = (stb__chunked *) stb__alloc_chunk(src, (int) size, align, sizeof(*s));
         if (s == NULL) return NULL;
         stb__setparent(s, src);
         p = s+1;
         break;
      }

      default: p = NULL; assert(0); /* NOTREACHED */
   }

   ++stb_alloc_count_alloc;
   return p;
}