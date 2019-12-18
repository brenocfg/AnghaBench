#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uval ;
struct TYPE_5__ {int fastpath; int* input; int length; int replace_fallback_with_codepoint; int /*<<< orphan*/  input_size; scalar_t__ splittable; scalar_t__ has_sign; scalar_t__ inherited_storage; scalar_t__ fallback; int /*<<< orphan*/  dont_care; scalar_t__ depth; } ;
typedef  TYPE_1__ table ;
struct TYPE_6__ {int lo; int hi; } ;
typedef  TYPE_2__ char_range ;

/* Variables and functions */
 int /*<<< orphan*/  UVAL_DONT_CARE_DEFAULT ; 
 int /*<<< orphan*/  assert (char**) ; 
 TYPE_2__ get_range (char*) ; 
 int /*<<< orphan*/  optimize_table (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  size_for_max_number (int) ; 
 char* skip_semi (char*,int) ; 
 int stb_max (int,int) ; 
 char** stb_stringfile (char*,int*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 int* unicode_table ; 

int main(int argc, char **argv)
{
   table t;
   uval maxv=0;
   int i,n=0;
   char **s = stb_stringfile("../../data/UnicodeData.txt", &n);
   assert(s);
   for (i=0; i < n; ++i) {
      if (s[i][0] == '#' || s[i][0] == '\n' || s[i][0] == 0)
         ;
      else {
         char_range cr = get_range(s[i]);
         char *t = skip_semi(s[i], 13);
         uval j, v;
         if (*t == ';' || *t == '\n' || *t == 0)
            v = 0;
         else {
            v = strtol(t, NULL, 16);
            if (v < 65536) {
               maxv = stb_max(v, maxv);
               for (j=cr.lo; j <= cr.hi; ++j) {
                  unicode_table[j] = v;
                  //printf("%06x => %06x\n", j, v);
               }
            }
         }
      }
   }

   t.depth = 0;
   t.dont_care = UVAL_DONT_CARE_DEFAULT;
   t.fallback = 0;
   t.fastpath = 256;
   t.inherited_storage = 0;
   t.has_sign = 0;
   t.splittable = 0;
   t.input = unicode_table;
   t.input_size = size_for_max_number(maxv);
   t.length = 0x110000;
   t.replace_fallback_with_codepoint = 1;

   optimize_table(&t, "stbu_upppercase");
   return 0;
}