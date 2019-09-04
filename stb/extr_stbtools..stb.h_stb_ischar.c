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
typedef  int /*<<< orphan*/  stb_perfect ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (unsigned char**) ; 
 int /*<<< orphan*/  memset (unsigned char**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (unsigned char**,int) ; 
 int /*<<< orphan*/  stb_arr_free (char**) ; 
 int stb_arr_len (char**) ; 
 int /*<<< orphan*/  stb_arr_push (char**,char*) ; 
 int stb_perfect_create (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int /*<<< orphan*/  stb_perfect_destroy (int /*<<< orphan*/ *) ; 
 int stb_perfect_hash (int /*<<< orphan*/ *,int) ; 

int stb_ischar(char c, char *set)
{
   static unsigned char bit[8] = { 1,2,4,8,16,32,64,128 };
   static stb_perfect p;
   static unsigned char (*tables)[256];
   static char ** sets = NULL;

   int z = stb_perfect_hash(&p, (int)(size_t) set);
   if (z < 0) {
      int i,k,n,j,f;
      // special code that means free all existing data
      if (set == NULL) {
         stb_arr_free(sets);
         free(tables);
         tables = NULL;
         stb_perfect_destroy(&p);
         return 0;
      }
      stb_arr_push(sets, set);
      stb_perfect_destroy(&p);
      n = stb_perfect_create(&p, (unsigned int *) (char **) sets, stb_arr_len(sets));
      assert(n != 0);
      k = (n+7) >> 3;
      tables = (unsigned char (*)[256]) realloc(tables, sizeof(*tables) * k);
      memset(tables, 0, sizeof(*tables) * k);
      for (i=0; i < stb_arr_len(sets); ++i) {
          k = stb_perfect_hash(&p, (int)(size_t) sets[i]);
         assert(k >= 0);
         n = k >> 3;
         f = bit[k&7];
         for (j=0; !j || sets[i][j]; ++j) {
            tables[n][(unsigned char) sets[i][j]] |= f;
         }
      }
      z = stb_perfect_hash(&p, (int)(size_t) set);
   }
   return tables[z >> 3][(unsigned char) c] & bit[z & 7];
}