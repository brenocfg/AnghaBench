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
struct TYPE_3__ {int nAvgBytesPerSec; int nBlockAlign; int /*<<< orphan*/  StartOfFile; } ;
typedef  TYPE_1__ WAVEParserImpl ;
typedef  int LONGLONG ;

/* Variables and functions */
 scalar_t__ BYTES_FROM_MEDIATIME (int /*<<< orphan*/ ) ; 
 int MEDIATIME_FROM_BYTES (int) ; 

__attribute__((used)) static LONGLONG duration_to_bytepos(WAVEParserImpl *This, LONGLONG duration)
{
    LONGLONG bytepos;

    bytepos = This->nAvgBytesPerSec;
    bytepos *= duration;
    bytepos /= 10000000;
    bytepos -= bytepos % This->nBlockAlign;
    bytepos += BYTES_FROM_MEDIATIME(This->StartOfFile);

    return MEDIATIME_FROM_BYTES(bytepos);
}