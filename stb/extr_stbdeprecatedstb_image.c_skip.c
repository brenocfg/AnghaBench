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
struct TYPE_4__ {int /*<<< orphan*/  (* skip ) (int /*<<< orphan*/ ,int) ;scalar_t__ read; } ;
struct TYPE_5__ {scalar_t__ img_buffer; int /*<<< orphan*/  io_user_data; TYPE_1__ io; scalar_t__ img_buffer_end; } ;
typedef  TYPE_2__ stbi ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skip(stbi *s, int n)
{
   if (s->io.read) {
      int blen = (int) (s->img_buffer_end - s->img_buffer);
      if (blen < n) {
         s->img_buffer = s->img_buffer_end;
         (s->io.skip)(s->io_user_data, n - blen);
         return;
      }
   }
   s->img_buffer += n;
}