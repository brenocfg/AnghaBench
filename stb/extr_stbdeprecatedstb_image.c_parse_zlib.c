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
struct TYPE_8__ {int zout; int zout_start; int /*<<< orphan*/  z_distance; int /*<<< orphan*/  z_length; scalar_t__ code_buffer; scalar_t__ num_bits; } ;
typedef  TYPE_1__ zbuf ;

/* Variables and functions */
 int /*<<< orphan*/  compute_huffman_codes (TYPE_1__*) ; 
 int /*<<< orphan*/ * default_distance ; 
 int /*<<< orphan*/ * default_length ; 
 int /*<<< orphan*/  init_defaults () ; 
 int /*<<< orphan*/  parse_huffman_block (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_uncompressed_block (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_zlib_header (TYPE_1__*) ; 
 scalar_t__ stbi_png_partial ; 
 int /*<<< orphan*/  zbuild_huffman (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zreceive (TYPE_1__*,int) ; 

__attribute__((used)) static int parse_zlib(zbuf *a, int parse_header)
{
   int final, type;
   if (parse_header)
      if (!parse_zlib_header(a)) return 0;
   a->num_bits = 0;
   a->code_buffer = 0;
   do {
      final = zreceive(a,1);
      type = zreceive(a,2);
      if (type == 0) {
         if (!parse_uncompressed_block(a)) return 0;
      } else if (type == 3) {
         return 0;
      } else {
         if (type == 1) {
            // use fixed code lengths
            if (!default_distance[31]) init_defaults();
            if (!zbuild_huffman(&a->z_length  , default_length  , 288)) return 0;
            if (!zbuild_huffman(&a->z_distance, default_distance,  32)) return 0;
         } else {
            if (!compute_huffman_codes(a)) return 0;
         }
         if (!parse_huffman_block(a)) return 0;
      }
      if (stbi_png_partial && a->zout - a->zout_start > 65536)
         break;
   } while (!final);
   return 1;
}