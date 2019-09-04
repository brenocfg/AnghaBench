#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbi__uint8 ;
struct TYPE_4__ {int /*<<< orphan*/ * read; } ;
struct TYPE_5__ {int /*<<< orphan*/ * img_buffer_end; int /*<<< orphan*/ * img_buffer_original; int /*<<< orphan*/ * img_buffer; scalar_t__ read_from_callbacks; TYPE_1__ io; } ;
typedef  TYPE_2__ stbi ;

/* Variables and functions */

__attribute__((used)) static void start_mem(stbi *s, stbi__uint8 const *buffer, int len)
{
   s->io.read = NULL;
   s->read_from_callbacks = 0;
   s->img_buffer = s->img_buffer_original = (stbi__uint8 *) buffer;
   s->img_buffer_end = (stbi__uint8 *) buffer+len;
}