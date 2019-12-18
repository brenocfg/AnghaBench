#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ stream; scalar_t__ stream_end; int eof; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ vorb ;
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 scalar_t__ USE_MEMORY (TYPE_1__*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int getn(vorb *z, uint8 *data, int n)
{
   if (USE_MEMORY(z)) {
      if (z->stream+n > z->stream_end) { z->eof = 1; return 0; }
      memcpy(data, z->stream, n);
      z->stream += n;
      return 1;
   }

   #ifndef STB_VORBIS_NO_STDIO   
   if (fread(data, n, 1, z->f) == 1)
      return 1;
   else {
      z->eof = 1;
      return 0;
   }
   #endif
}