#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uval ;
struct TYPE_6__ {scalar_t__ dont_care; int length; int fastpath; scalar_t__* input; scalar_t__ fallback; size_t input_size; scalar_t__ depth; scalar_t__ inherited_storage; scalar_t__ splittable; int /*<<< orphan*/  has_sign; int /*<<< orphan*/  replace_fallback_with_codepoint; } ;
typedef  TYPE_1__ table ;
struct TYPE_7__ {size_t overhead; scalar_t__ trim_end; scalar_t__ special; scalar_t__ indirect; int /*<<< orphan*/  aligned; scalar_t__ trim_start; } ;
typedef  TYPE_2__ mode_info ;

/* Variables and functions */
 int MODECOUNT ; 
 scalar_t__ UVAL_DONT_CARE_DEFAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ find_packed (scalar_t__**,scalar_t__*,int,int /*<<< orphan*/ ,int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* modes ; 
 int /*<<< orphan*/  output_table (char*,char*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_table_with_trims (char*,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 size_t size_for_max_number (scalar_t__) ; 
 size_t size_for_max_number_aligned (scalar_t__) ; 
 int /*<<< orphan*/  stb_arr_free (scalar_t__*) ; 
 int stb_arr_len (scalar_t__*) ; 
 int /*<<< orphan*/  stb_arr_push (scalar_t__*,scalar_t__) ; 
 int stb_max (scalar_t__,scalar_t__) ; 
 size_t weight ; 

table pack_for_mode(table *t, int mode, char *table_name)
{
   size_t extra_size;
   int i;
   uval maxv;
   mode_info mi = modes[mode % MODECOUNT];
   int size = 8 << (mode / MODECOUNT);
   table newtab;
   uval *packed = NULL;
   uval *index = NULL;
   uval *indirect = NULL;
   uval *specials = NULL;
   newtab.dont_care = UVAL_DONT_CARE_DEFAULT;
   if (table_name)
      printf("// clusters of %d\n", size);
   for (i=0; i < t->length; i += size) {
      uval newval;
      int fastpath = (i < t->fastpath);
      if (mi.special) {
         int end_trim = size-1;
         int start_trim = 0;
         uval special;
         // @TODO: pick special from start or end instead of only end depending on which is longer
         for(;;) {
            special = t->input[i + end_trim];
            if (special != t->dont_care || end_trim == 0)
               break;
            --end_trim;
         }
         // at this point, special==inp[end_trim], and end_trim >= 0
         if (special == t->dont_care && !fastpath) {
            // entire block is don't care, so OUTPUT don't care
            stb_arr_push(index, newtab.dont_care);
            continue;
         } else {
            uval pos, trim;
            if (mi.trim_end && !fastpath) {
               while (end_trim >= 0) {
                  if (t->input[i + end_trim] == special || t->input[i + end_trim] == t->dont_care)
                     --end_trim;
                  else
                     break;
               }
            }

            if (mi.trim_start && !fastpath) {
               while (start_trim < end_trim) {
                  if (t->input[i + start_trim] == special || t->input[i + start_trim] == t->dont_care)
                     ++start_trim;
                  else
                     break;
               }
            }

            // end_trim points to the last character we have to output

            // find the first match, or add it
            pos = find_packed(&packed, &t->input[i+start_trim], end_trim-start_trim+1, mi.aligned, fastpath, &t->input[t->length], i+start_trim, t->replace_fallback_with_codepoint);

            // encode as a uval
            if (!mi.trim_end) {
               if (end_trim == 0)
                  pos = special;
               else
                  pos = pos | 0x80000000;
            } else {
               assert(end_trim < size && end_trim >= -1);
               if (!fastpath) assert(end_trim < size-1); // special always matches last one
               assert(end_trim < size && end_trim+1 >= 0);
               if (!fastpath) assert(end_trim+1 < size);

               if (mi.trim_start)
                  trim = start_trim*256 + (end_trim+1);
               else
                  trim = end_trim+1;

               assert(pos < 65536); // @TODO: if this triggers, just bail on this search path
               pos = pos + (trim << 16);
            }

            newval = pos;

            stb_arr_push(specials, special);
         }
      } else if (mi.trim_end) {
         int end_trim = size-1;
         int start_trim = 0;
         uval pos, trim;

         while (end_trim >= 0 && !fastpath)
            if (t->input[i + end_trim] == t->fallback || t->input[i + end_trim] == t->dont_care)
               --end_trim;
            else
               break;

         if (mi.trim_start && !fastpath) {
            while (start_trim < end_trim) {
               if (t->input[i + start_trim] == t->fallback || t->input[i + start_trim] == t->dont_care)
                  ++start_trim;
               else
                  break;
            }
         }

         // end_trim points to the last character we have to output, and can be -1
         ++end_trim; // make exclusive at end

         if (end_trim == 0 && size == 256)
            start_trim = end_trim = 1;  // we can't make encode a length from 0..256 in 8 bits, so restrict end_trim to 1..256

         // find the first match, or add it
         pos = find_packed(&packed, &t->input[i+start_trim], end_trim - start_trim, mi.aligned, fastpath, &t->input[t->length], i+start_trim, t->replace_fallback_with_codepoint);

         assert(end_trim <= size && end_trim >= 0);
         if (size == 256)
            assert(end_trim-1 < 256 && end_trim-1 >= 0);
         else
            assert(end_trim < 256 && end_trim >= 0);
         if (size == 256)
            --end_trim;

         if (mi.trim_start)
            trim = start_trim*256 + end_trim;
         else
            trim = end_trim;

         assert(pos < 65536); // @TODO: if this triggers, just bail on this search path
         pos = pos + (trim << 16);

         newval = pos;
      } else {
         newval = find_packed(&packed, &t->input[i], size, mi.aligned, fastpath, &t->input[t->length], i, t->replace_fallback_with_codepoint);
      }

      if (mi.indirect) {
         int j;
         for (j=0; j < stb_arr_len(indirect); ++j)
            if (indirect[j] == newval)
               break;
         if (j == stb_arr_len(indirect))
            stb_arr_push(indirect, newval);
         stb_arr_push(index, j);
      } else {
         stb_arr_push(index, newval);
      }
   }

   // total up the new size for everything but the index table
   extra_size = mi.overhead * weight; // not the actual overhead cost; a penalty to avoid excessive complexity
   extra_size += 150; // per indirection
   if (table_name)
      extra_size = 0;
   
   if (t->has_sign) {
      // 'packed' contains two values, which should be packed positive & negative for size
      uval maxv2;
      for (i=0; i < stb_arr_len(packed); ++i)
         if (packed[i] & 0x80000000)
            maxv2 = stb_max(maxv2, packed[i]);
         else
            maxv  = stb_max(maxv, packed[i]);
      maxv = stb_max(maxv, maxv2) << 1;
   } else {
      maxv = 0;
      for (i=0; i < stb_arr_len(packed); ++i)
         if (packed[i] > maxv && packed[i] != t->dont_care)
            maxv = packed[i];
   }
   extra_size += stb_arr_len(packed) * (t->splittable ? size_for_max_number(maxv) : size_for_max_number_aligned(maxv));
   if (table_name) {
      if (t->splittable)
         output_table_with_trims(table_name, "", packed, stb_arr_len(packed));
      else
         output_table(table_name, "", packed, stb_arr_len(packed), t->has_sign, NULL);
   }

   maxv = 0;
   for (i=0; i < stb_arr_len(specials); ++i)
      if (specials[i] > maxv)
         maxv = specials[i];
   extra_size += stb_arr_len(specials) * size_for_max_number_aligned(maxv);
   if (table_name)
      output_table(table_name, "_default", specials, stb_arr_len(specials), 0, NULL);

   maxv = 0;
   for (i=0; i < stb_arr_len(indirect); ++i)
      if (indirect[i] > maxv)
         maxv = indirect[i];
   extra_size += stb_arr_len(indirect) * size_for_max_number(maxv);

   if (table_name && stb_arr_len(indirect)) {
      if (mi.trim_end)
         output_table_with_trims(table_name, "_index", indirect, stb_arr_len(indirect));
      else {
         assert(0); // this case should only trigger in very extreme circumstances
         output_table(table_name, "_index", indirect, stb_arr_len(indirect), 0, NULL);
      }
      mi.trim_end = mi.special = 0;
   }

   if (table_name)
      printf("// above tables should be %d bytes\n", extra_size);

   maxv = 0;
   for (i=0; i < stb_arr_len(index); ++i)
      if (index[i] > maxv && index[i] != t->dont_care)
         maxv = index[i];
   newtab.splittable = mi.trim_end;
   newtab.input_size = newtab.splittable ? size_for_max_number(maxv) : size_for_max_number_aligned(maxv);
   newtab.input = index;
   newtab.length = stb_arr_len(index);
   newtab.inherited_storage = t->inherited_storage + extra_size;
   newtab.fastpath = 0;
   newtab.depth = t->depth+1;
   stb_arr_free(indirect);
   stb_arr_free(packed);
   stb_arr_free(specials);

   return newtab;
}