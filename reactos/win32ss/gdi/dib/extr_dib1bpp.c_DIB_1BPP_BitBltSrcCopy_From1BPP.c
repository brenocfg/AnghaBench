#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLATEOBJ ;
struct TYPE_10__ {int x; int y; } ;
struct TYPE_9__ {int left; int right; int top; int bottom; } ;
struct TYPE_8__ {int lDelta; scalar_t__ pvScan0; } ;
typedef  TYPE_1__ SURFOBJ ;
typedef  TYPE_2__* PRECTL ;
typedef  TYPE_3__ POINTL ;
typedef  int* PBYTE ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ XLATEOBJ_iXlate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
DIB_1BPP_BitBltSrcCopy_From1BPP (
                                 SURFOBJ* DestSurf,
                                 SURFOBJ* SourceSurf,
                                 XLATEOBJ* pxlo,
                                 PRECTL DestRect,
                                 POINTL *SourcePoint )
{
  // The 'window' in this sense is the x-position that corresponds
  // to the left-edge of the 8-pixel byte we are currently working with.
  // dwx is current x-window, dwx2 is the 'last' window we need to process.
  int dwx, dwx2;  // Destination window x-position
  int swx;        // Source window y-position

  // Left and right edges of source and dest rectangles
  int dl = DestRect->left; // dest left
  int dr = DestRect->right-1; // dest right (inclusive)
  int sl = SourcePoint->x; // source left
  int sr = sl + dr - dl; // source right (inclusive)

  // Which direction are we going?
  int xinc;
  int yinc;
  int ySrcDelta, yDstDelta;

  // The following 4 variables are used for the y-sweep
  int dy;  // dest y
  int dy1; // dest y start
  int dy2; // dest y end
  int sy1; // src  y start

  int shift;
  BYTE srcmask, dstmask, xormask;

  // 'd' and 's' are the dest & src buffer pointers that I use on my x-sweep
  // 'pd' and 'ps' are the dest & src buffer pointers used on the inner y-sweep
  PBYTE d, pd; // dest ptrs
  PBYTE s, ps; // src ptrs

  shift = (dl-sl)&7;

  xormask = 0xFF * (BYTE)XLATEOBJ_iXlate(pxlo, 0);

  if ( DestRect->top <= SourcePoint->y )
  {
    // Moving up (scan top -> bottom)
    dy1 = DestRect->top;
    dy2 = DestRect->bottom - 1;
    sy1 = SourcePoint->y;
    yinc = 1;
    ySrcDelta = SourceSurf->lDelta;
    yDstDelta = DestSurf->lDelta;
  }
  else
  {
    // Moving down (scan bottom -> top)
    dy1 = DestRect->bottom - 1;
    dy2 = DestRect->top;
    sy1 = SourcePoint->y + dy1 - dy2;
    yinc = -1;
    ySrcDelta = -SourceSurf->lDelta;
    yDstDelta = -DestSurf->lDelta;
  }
  if ( DestRect->left <= SourcePoint->x )
  {
    // Moving left (scan left->right)
    dwx = dl&~7;
    swx = (sl-(dl&7))&~7;
    dwx2 = dr&~7;
    xinc = 1;
  }
  else
  {
    // Moving right (scan right->left)
    dwx = dr & ~7;
    swx = (sr - (dr & 7)) & ~7; // (sr - 7) & ~7; // We need the left edge of this block. Thus the -7
    dwx2 = dl & ~7;
    xinc = -1;
  }
  d = &(((PBYTE)DestSurf->pvScan0)[dy1*DestSurf->lDelta + (dwx>>3)]);
  s = &(((PBYTE)SourceSurf->pvScan0)[sy1*SourceSurf->lDelta + (swx>>3)]);
  for ( ;; )
  {
    dy = dy1;
    pd = d;
    ps = s;
    srcmask = 0xff;
    if ( dwx < dl )
    {
      int diff = dl-dwx;
      srcmask &= (1<<(8-diff))-1;
    }
    if ( dwx+7 > dr )
    {
      int diff = dr-dwx+1;
      srcmask &= ~((1<<(8-diff))-1);
    }
    dstmask = ~srcmask;

    // We unfortunately *must* have 5 different versions of the inner
    // loop to be certain we don't try to read from memory that is not
    // needed and may in fact be invalid.
    if ( !shift )
    {
      for ( ;; )
      {
        *pd = (BYTE)((*pd & dstmask) | ((ps[0]^xormask) & srcmask));

        // This *must* be here, because we could be going up *or* down...
        if ( dy == dy2 )
          break;
        dy += yinc;
        pd += yDstDelta;
        ps += ySrcDelta;
      }
    }
    else if ( !(0xFF00 & (srcmask<<shift) ) ) // Check if ps[0] not needed...
    {
      for ( ;; )
      {
        *pd = (BYTE)((*pd & dstmask)
          | ( ( (ps[1]^xormask) >> shift ) & srcmask ));

        // This *must* be here, because we could be going up *or* down...
        if ( dy == dy2 )
          break;
        dy += yinc;
        pd += yDstDelta;
        ps += ySrcDelta;
      }
    }
    else if ( !(0xFF & (srcmask<<shift) ) ) // Check if ps[1] not needed...
    {
      for ( ;; )
      {
        *pd = (*pd & dstmask)
          | ( ( (ps[0]^xormask) << ( 8 - shift ) ) & srcmask );

        // This *must* be here, because we could be going up *or* down...
        if ( dy == dy2 )
          break;
        dy += yinc;
        pd += yDstDelta;
        ps += ySrcDelta;
      }
    }
    else // Both ps[0] and ps[1] are needed
    {
      for ( ;; )
      {
        *pd = (*pd & dstmask)
          | ( ( ( ((ps[1]^xormask))|((ps[0]^xormask)<<8) ) >> shift ) & srcmask );

        // This *must* be here, because we could be going up *or* down...
        if ( dy == dy2 )
          break;
        dy += yinc;
        pd += yDstDelta;
        ps += ySrcDelta;
      }
    }

    // This *must* be here, because we could be going right *or* left...
    if ( dwx == dwx2 )
      break;
    d += xinc;
    s += xinc;
    dwx += xinc<<3;
    swx += xinc<<3;
  }
}