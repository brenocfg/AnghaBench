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
typedef  int /*<<< orphan*/  stbi_uc ;
struct TYPE_4__ {int (* read ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_5__ {scalar_t__ img_buffer_end; scalar_t__ img_buffer; int /*<<< orphan*/  io_user_data; TYPE_1__ io; } ;
typedef  TYPE_2__ stbi ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int getn(stbi *s, stbi_uc *buffer, int n)
{
   if (s->io.read) {
      int blen = (int) (s->img_buffer_end - s->img_buffer);
      if (blen < n) {
         int res, count;

         memcpy(buffer, s->img_buffer, blen);
         
         count = (s->io.read)(s->io_user_data, (char*) buffer + blen, n - blen);
         res = (count == (n-blen));
         s->img_buffer = s->img_buffer_end;
         return res;
      }
   }

   if (s->img_buffer+n <= s->img_buffer_end) {
      memcpy(buffer, s->img_buffer, n);
      s->img_buffer += n;
      return 1;
   } else
      return 0;
}