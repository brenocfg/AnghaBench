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
struct TYPE_3__ {unsigned char* cur; char* temp_buffer; } ;
typedef  TYPE_1__ nbt ;

/* Variables and functions */
 unsigned char TAG_End ; 
 int /*<<< orphan*/  nbt_get_string_data (unsigned char*,char*,int) ; 

__attribute__((used)) static char *nbt_peek(nbt *n)
{
   unsigned char type = *n->cur;
   if (type == TAG_End)
      return NULL;
   nbt_get_string_data(n->cur+1, n->temp_buffer, sizeof(n->temp_buffer));
   return n->temp_buffer;
}