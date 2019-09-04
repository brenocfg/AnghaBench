#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  stbi__uint8 ;

/* Variables and functions */

__attribute__((used)) static stbi__uint8 compute_y(int r, int g, int b)
{
   return (stbi__uint8) (((r*77) + (g*150) +  (29*b)) >> 8);
}