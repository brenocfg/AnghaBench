#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sorted ;
typedef  int /*<<< orphan*/  items ;
struct TYPE_23__ {int v; } ;
typedef  TYPE_1__ Btest ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btest__validate (TYPE_1__*,int) ; 
 TYPE_1__* btest_find (TYPE_1__*,int) ; 
 TYPE_1__* btest_first (TYPE_1__*) ; 
 TYPE_1__* btest_insert (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* btest_last (TYPE_1__*) ; 
 TYPE_1__* btest_next (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* btest_prev (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* btest_remove (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  c (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_intcmp (int /*<<< orphan*/ ) ; 
 int stb_rand () ; 
 int /*<<< orphan*/  stb_reverse (int*,int,int) ; 
 int /*<<< orphan*/  stb_shuffle (int*,int,int,int) ; 

void bst_test(void)
{
   Btest *root = NULL, *t;
   int items[500], sorted[500];
   int i,j,z;
   for (z=0; z < 10; ++z) {
      for (i=0; i < 500; ++i)
         items[i] = stb_rand() & 0xfffffff;

      // check for collisions, and retrry if so
      memcpy(sorted, items, sizeof(sorted));
      qsort(sorted, 500, sizeof(sorted[0]), stb_intcmp(0));
      for (i=1; i < 500; ++i)
         if (sorted[i-1] == sorted[i])
            break;
      if (i != 500) { --z; break; }

      for (i=0; i < 500; ++i)  {
         t = malloc(sizeof(*t));
         t->v = items[i];
         root = btest_insert(root, t);
         #ifdef STB_DEBUG
         btest__validate(root,1);
         #endif
         for (j=0; j <= i; ++j)
            c(btest_find(root, items[j]) != NULL, "stb_bst 1");
         for (   ; j < 500; ++j)
            c(btest_find(root, items[j]) == NULL, "stb_bst 2");
      }

      t = btest_first(root);
      for (i=0; i < 500; ++i)
         t = btest_next(root,t);
      c(t == NULL, "stb_bst 5");
      t = btest_last(root);
      for (i=0; i < 500; ++i)
         t = btest_prev(root,t);
      c(t == NULL, "stb_bst 6");

      memcpy(sorted, items, sizeof(sorted));
      qsort(sorted, 500, sizeof(sorted[0]), stb_intcmp(0));
      t = btest_first(root);
      for (i=0; i < 500; ++i) {
         assert(t->v == sorted[i]);
         t = btest_next(root, t);
      }
      assert(t == NULL);

      if (z==1)
         stb_reverse(items, 500, sizeof(items[0]));
      else if (z)
         stb_shuffle(items, 500, sizeof(items[0]), stb_rand());

      for (i=0; i < 500; ++i)  {
         t = btest_find(root, items[i]);
         assert(t != NULL);
         root = btest_remove(root, t);
         c(btest_find(root, items[i]) == NULL, "stb_bst 5");
         #ifdef STB_DEBUG
         btest__validate(root, 1);
         #endif
         for (j=0; j <= i; ++j)
            c(btest_find(root, items[j]) == NULL, "stb_bst 3");
         for (   ; j < 500; ++j)
            c(btest_find(root, items[j]) != NULL, "stb_bst 4");
         free(t);
      }
   }
}