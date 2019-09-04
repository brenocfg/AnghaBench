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
struct TYPE_4__ {scalar_t__ pos; scalar_t__ buffer; } ;
typedef  TYPE_1__ ME_OutStream ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_StreamOutFlush (TYPE_1__*) ; 
 scalar_t__ STREAMOUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,char const*,int) ; 
 int min (int,int) ; 

__attribute__((used)) static BOOL
ME_StreamOutMove(ME_OutStream *pStream, const char *buffer, int len)
{
  while (len) {
    int space = STREAMOUT_BUFFER_SIZE - pStream->pos;
    int fit = min(space, len);

    TRACE("%u:%u:%s\n", pStream->pos, fit, debugstr_an(buffer,fit));
    memmove(pStream->buffer + pStream->pos, buffer, fit);
    len -= fit;
    buffer += fit;
    pStream->pos += fit;
    if (pStream->pos == STREAMOUT_BUFFER_SIZE) {
      if (!ME_StreamOutFlush(pStream))
        return FALSE;
    }
  }
  return TRUE;
}