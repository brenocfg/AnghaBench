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
typedef  size_t stb_uint8 ;
typedef  int stb_uint16 ;
typedef  size_t stb_uint ;
struct TYPE_8__ {int num_charset; size_t* charset; } ;
typedef  TYPE_1__ stb_matcher ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb__add_edge (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stb__add_epsilon (TYPE_1__*,int,int) ; 
 int stb__add_node (TYPE_1__*) ; 
 char* stb__reg_parse_alt (TYPE_1__*,int,char*,int*) ; 
 scalar_t__ stb_malloc (TYPE_1__*,int) ; 

__attribute__((used)) static char *stb__reg_parse(stb_matcher *matcher, int start, char *regex, stb_uint16 *end)
{
   int n;
   int last_start = -1;
   stb_uint16 last_end = start;

   while (*regex) {
      switch (*regex) {
         case '(':
            last_start = last_end;
            regex = stb__reg_parse_alt(matcher, last_end, regex+1, &last_end);
            if (regex == NULL || *regex != ')')
               return NULL;
            ++regex;
            break;

         case '|':
         case ')':
            *end = last_end;
            return regex;

         case '?':
            if (last_start < 0) return NULL;
            stb__add_epsilon(matcher, last_start, last_end);
            ++regex;
            break;

         case '*':
            if (last_start < 0) return NULL;
            stb__add_epsilon(matcher, last_start, last_end);

            // fall through

         case '+':
            if (last_start < 0) return NULL;
            stb__add_epsilon(matcher, last_end, last_start);
            // prevent links back to last_end from chaining to last_start
            n = stb__add_node(matcher);
            stb__add_epsilon(matcher, last_end, n);
            last_end = n;
            ++regex;
            break;

         case '{':   // not supported!
            // @TODO: given {n,m}, clone last_start to last_end m times,
            // and include epsilons from start to first m-n blocks
            return NULL; 

         case '\\':
            ++regex;
            if (!*regex) return NULL;

            // fallthrough
         default: // match exactly this character
            n = stb__add_node(matcher);
            stb__add_edge(matcher, last_end, n, *regex);
            last_start = last_end;
            last_end = n;
            ++regex;
            break;

         case '$':
            n = stb__add_node(matcher);
            stb__add_edge(matcher, last_end, n, '\n');
            last_start = last_end;
            last_end = n;
            ++regex;
            break;

         case '.':
            n = stb__add_node(matcher);
            stb__add_edge(matcher, last_end, n, -1);
            last_start = last_end;
            last_end = n;
            ++regex;
            break;

         case '[': {
            stb_uint8 flags[256];
            int invert = 0,z;
            ++regex;
            if (matcher->num_charset == 0) {
               matcher->charset = (stb_uint *) stb_malloc(matcher, sizeof(*matcher->charset) * 256);
               memset(matcher->charset, 0, sizeof(*matcher->charset) * 256);
            }

            memset(flags,0,sizeof(flags));

            // leading ^ is special
            if (*regex == '^')
               ++regex, invert = 1;

            // leading ] is special
            if (*regex == ']') {
               flags[(int) ']'] = 1;
               ++regex;
            }
            while (*regex != ']') {
               stb_uint a;
               if (!*regex) return NULL;
               a = *regex++;
               if (regex[0] == '-' && regex[1] != ']') {
                  stb_uint i,b = regex[1];
                  regex += 2;
                  if (b == 0) return NULL;
                  if (a > b) return NULL;
                  for (i=a; i <= b; ++i)
                     flags[i] = 1;
               } else
                  flags[a] = 1;
            }
            ++regex;
            if (invert) {
               int i;
               for (i=0; i < 256; ++i)
                  flags[i] = 1-flags[i];
            }

            // now check if any existing charset matches
            for (z=0; z < matcher->num_charset; ++z) {
               int i, k[2] = { 0, 1 << z};
               for (i=0; i < 256; ++i) {
                  unsigned int f = k[flags[i]];
                  if ((matcher->charset[i] & k[1]) != f)
                     break;
               }
               if (i == 256) break;
            }

            if (z == matcher->num_charset) {
               int i;
               ++matcher->num_charset;
               if (matcher->num_charset > 32) {
                  assert(0); /* NOTREACHED */
                  return NULL; // too many charsets, oops
               }
               for (i=0; i < 256; ++i)
                  if (flags[i])
                     matcher->charset[i] |= (1 << z);
            }

            n = stb__add_node(matcher);
            stb__add_edge(matcher, last_end, n, -2 - z);
            last_start = last_end;
            last_end = n;
            break;
         }
      }
   }
   *end = last_end;
   return regex;
}