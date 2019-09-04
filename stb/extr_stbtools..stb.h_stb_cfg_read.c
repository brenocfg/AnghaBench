#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* data; } ;
typedef  TYPE_1__ stb_cfg ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  value_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int stb_arr_len (TYPE_3__*) ; 
 int stb_min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_stricmp (int /*<<< orphan*/ ,char*) ; 

int stb_cfg_read(stb_cfg *z, char *key, void *value, int len)
{
   int i;
   for (i=0; i < stb_arr_len(z->data); ++i) {
      if (!stb_stricmp(z->data[i].key, key)) {
         int n = stb_min(len, z->data[i].value_len);
         memcpy(value, z->data[i].value, n);
         if (n < len)
            *((char *) value + n) = 0;
         return 1;
      }
   }
   return 0;
}