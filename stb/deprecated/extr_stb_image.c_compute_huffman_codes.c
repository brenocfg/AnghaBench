#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zhuffman ;
struct TYPE_5__ {int /*<<< orphan*/  z_distance; int /*<<< orphan*/  z_length; } ;
typedef  TYPE_1__ zbuf ;
typedef  int stbi__uint8 ;
typedef  int /*<<< orphan*/  codelength_sizes ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int e (char*,char*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  zbuild_huffman (int /*<<< orphan*/ *,int*,int) ; 
 int zhuffman_decode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zreceive (TYPE_1__*,int) ; 

__attribute__((used)) static int compute_huffman_codes(zbuf *a)
{
   static stbi__uint8 length_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
   zhuffman z_codelength;
   stbi__uint8 lencodes[286+32+137];//padding for maximum single op
   stbi__uint8 codelength_sizes[19];
   int i,n;

   int hlit  = zreceive(a,5) + 257;
   int hdist = zreceive(a,5) + 1;
   int hclen = zreceive(a,4) + 4;

   memset(codelength_sizes, 0, sizeof(codelength_sizes));
   for (i=0; i < hclen; ++i) {
      int s = zreceive(a,3);
      codelength_sizes[length_dezigzag[i]] = (stbi__uint8) s;
   }
   if (!zbuild_huffman(&z_codelength, codelength_sizes, 19)) return 0;

   n = 0;
   while (n < hlit + hdist) {
      int c = zhuffman_decode(a, &z_codelength);
      assert(c >= 0 && c < 19);
      if (c < 16)
         lencodes[n++] = (stbi__uint8) c;
      else if (c == 16) {
         c = zreceive(a,2)+3;
         memset(lencodes+n, lencodes[n-1], c);
         n += c;
      } else if (c == 17) {
         c = zreceive(a,3)+3;
         memset(lencodes+n, 0, c);
         n += c;
      } else {
         assert(c == 18);
         c = zreceive(a,7)+11;
         memset(lencodes+n, 0, c);
         n += c;
      }
   }
   if (n != hlit+hdist) return e("bad codelengths","Corrupt PNG");
   if (!zbuild_huffman(&a->z_length, lencodes, hlit)) return 0;
   if (!zbuild_huffman(&a->z_distance, lencodes+hlit, hdist)) return 0;
   return 1;
}