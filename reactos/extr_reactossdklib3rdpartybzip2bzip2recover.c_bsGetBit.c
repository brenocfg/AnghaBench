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
struct TYPE_3__ {int buffLive; int buffer; int /*<<< orphan*/  handle; } ;
typedef  int Int32 ;
typedef  TYPE_1__ BitStream ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ errno ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readError () ; 

__attribute__((used)) static Int32 bsGetBit ( BitStream* bs )
{
   if (bs->buffLive > 0) {
      bs->buffLive --;
      return ( ((bs->buffer) >> (bs->buffLive)) & 0x1 );
   } else {
      Int32 retVal = getc ( bs->handle );
      if ( retVal == EOF ) {
         if (errno != 0) readError();
         return 2;
      }
      bs->buffLive = 7;
      bs->buffer = retVal;
      return ( ((bs->buffer) >> 7) & 0x1 );
   }
}