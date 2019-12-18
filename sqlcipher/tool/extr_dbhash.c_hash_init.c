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
struct TYPE_3__ {int* state; scalar_t__* count; } ;
struct TYPE_4__ {TYPE_1__ cx; } ;

/* Variables and functions */
 TYPE_2__ g ; 

__attribute__((used)) static void hash_init(void){
  /* SHA1 initialization constants */
  g.cx.state[0] = 0x67452301;
  g.cx.state[1] = 0xEFCDAB89;
  g.cx.state[2] = 0x98BADCFE;
  g.cx.state[3] = 0x10325476;
  g.cx.state[4] = 0xC3D2E1F0;
  g.cx.count[0] = g.cx.count[1] = 0;
}