#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void hash_step(const unsigned char *data,  unsigned int len){
  unsigned int i, j;

  j = g.cx.count[0];
  if( (g.cx.count[0] += len << 3) < j ){
    g.cx.count[1] += (len>>29)+1;
  }
  j = (j >> 3) & 63;
  if( (j + len) > 63 ){
    (void)memcpy(&g.cx.buffer[j], data, (i = 64-j));
    SHA1Transform(g.cx.state, g.cx.buffer);
    for(; i + 63 < len; i += 64){
      SHA1Transform(g.cx.state, &data[i]);
    }
    j = 0;
  }else{
    i = 0;
  }
  (void)memcpy(&g.cx.buffer[j], &data[i], len - i);
}