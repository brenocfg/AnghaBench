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
typedef  int stbi__uint8 ;
struct TYPE_3__ {scalar_t__ marker; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ jpeg ;

/* Variables and functions */
 scalar_t__ MARKER_none ; 
 int get8u (int /*<<< orphan*/ ) ; 

__attribute__((used)) static stbi__uint8 get_marker(jpeg *j)
{
   stbi__uint8 x;
   if (j->marker != MARKER_none) { x = j->marker; j->marker = MARKER_none; return x; }
   x = get8u(j->s);
   if (x != 0xff) return MARKER_none;
   while (x == 0xff)
      x = get8u(j->s);
   return x;
}