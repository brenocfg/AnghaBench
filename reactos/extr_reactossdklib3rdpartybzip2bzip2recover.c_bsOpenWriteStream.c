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
struct TYPE_4__ {char mode; scalar_t__ buffLive; scalar_t__ buffer; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BitStream ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  mallocFail (int) ; 

__attribute__((used)) static BitStream* bsOpenWriteStream ( FILE* stream )
{
   BitStream *bs = malloc ( sizeof(BitStream) );
   if (bs == NULL) mallocFail ( sizeof(BitStream) );
   bs->handle = stream;
   bs->buffer = 0;
   bs->buffLive = 0;
   bs->mode = 'w';
   return bs;
}