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
struct TYPE_3__ {int /*<<< orphan*/ ** p; } ;
typedef  TYPE_1__ stb_ps_bucket ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static stb_ps_bucket * stb_bucket_create3(void **v)
{
   stb_ps_bucket *b = (stb_ps_bucket*) malloc(sizeof(*b));
   b->p[0] = v[0];
   b->p[1] = v[1];
   b->p[2] = v[2];
   b->p[3] = NULL;
   return b;
}