#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* cur; scalar_t__ buffer_end; } ;
typedef  TYPE_1__ nbt ;

/* Variables and functions */
#define  TAG_Byte 138 
#define  TAG_Byte_Array 137 
#define  TAG_Compound 136 
#define  TAG_Double 135 
 int TAG_End ; 
#define  TAG_Float 134 
#define  TAG_Int 133 
#define  TAG_Int_Array 132 
#define  TAG_List 131 
#define  TAG_Long 130 
#define  TAG_Short 129 
#define  TAG_String 128 
 int /*<<< orphan*/  assert (int) ; 
 int nbt_parse_uint32 (int*) ; 
 int /*<<< orphan*/  nbt_skip (TYPE_1__*) ; 

__attribute__((used)) static void nbt_skip_raw(nbt *n, unsigned char type)
{
   switch (type) {
      case TAG_Byte  : n->cur += 1; break;
      case TAG_Short : n->cur += 2; break;
      case TAG_Int   : n->cur += 4; break;
      case TAG_Long  : n->cur += 8; break;
      case TAG_Float : n->cur += 4; break;
      case TAG_Double: n->cur += 8; break;
      case TAG_Byte_Array: n->cur += 4 + 1*nbt_parse_uint32(n->cur); break;
      case TAG_Int_Array : n->cur += 4 + 4*nbt_parse_uint32(n->cur); break;
      case TAG_String    : n->cur += 2 + (n->cur[0]*256 + n->cur[1]); break;
      case TAG_List      : {
         unsigned char list_type = *n->cur++;
         unsigned int list_len = nbt_parse_uint32(n->cur);
         unsigned int i;
         n->cur += 4; // list_len
         for (i=0; i < list_len; ++i)
            nbt_skip_raw(n, list_type);
         break;
      }
      case TAG_Compound : {
         while (*n->cur != TAG_End)
            nbt_skip(n);
         nbt_skip(n); // skip the TAG_end
         break;
      }
   }
   assert(n->cur <= n->buffer_end);
}