#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* fast; int* firstcode; int* firstsymbol; int* maxcode; size_t* size; void** value; } ;
typedef  TYPE_1__ zhuffman ;
typedef  size_t stbi__uint8 ;
typedef  void* stbi__uint16 ;
typedef  int /*<<< orphan*/  sizes ;

/* Variables and functions */
 int ZFAST_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 int bit_reverse (int,int) ; 
 int e (char*,char*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int zbuild_huffman(zhuffman *z, stbi__uint8 *sizelist, int num)
{
   int i,k=0;
   int code, next_code[16], sizes[17];

   // DEFLATE spec for generating codes
   memset(sizes, 0, sizeof(sizes));
   memset(z->fast, 255, sizeof(z->fast));
   for (i=0; i < num; ++i) 
      ++sizes[sizelist[i]];
   sizes[0] = 0;
   for (i=1; i < 16; ++i)
      assert(sizes[i] <= (1 << i));
   code = 0;
   for (i=1; i < 16; ++i) {
      next_code[i] = code;
      z->firstcode[i] = (stbi__uint16) code;
      z->firstsymbol[i] = (stbi__uint16) k;
      code = (code + sizes[i]);
      if (sizes[i])
         if (code-1 >= (1 << i)) return e("bad codelengths","Corrupt JPEG");
      z->maxcode[i] = code << (16-i); // preshift for inner loop
      code <<= 1;
      k += sizes[i];
   }
   z->maxcode[16] = 0x10000; // sentinel
   for (i=0; i < num; ++i) {
      int s = sizelist[i];
      if (s) {
         int c = next_code[s] - z->firstcode[s] + z->firstsymbol[s];
         z->size[c] = (stbi__uint8)s;
         z->value[c] = (stbi__uint16)i;
         if (s <= ZFAST_BITS) {
            int k = bit_reverse(next_code[s],s);
            while (k < (1 << ZFAST_BITS)) {
               z->fast[k] = (stbi__uint16) c;
               k += (1 << s);
            }
         }
         ++next_code[s];
      }
   }
   return 1;
}