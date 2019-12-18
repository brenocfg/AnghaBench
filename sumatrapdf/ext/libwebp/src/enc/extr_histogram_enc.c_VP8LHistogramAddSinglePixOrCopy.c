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
struct TYPE_3__ {int /*<<< orphan*/ * distance_; int /*<<< orphan*/ * literal_; int /*<<< orphan*/ * blue_; int /*<<< orphan*/ * red_; int /*<<< orphan*/ * alpha_; } ;
typedef  TYPE_1__ VP8LHistogram ;
typedef  int /*<<< orphan*/  PixOrCopy ;

/* Variables and functions */
 int NUM_LENGTH_CODES ; 
 int NUM_LITERAL_CODES ; 
 int PixOrCopyCacheIdx (int /*<<< orphan*/  const* const) ; 
 int PixOrCopyDistance (int /*<<< orphan*/  const* const) ; 
 scalar_t__ PixOrCopyIsCacheIdx (int /*<<< orphan*/  const* const) ; 
 scalar_t__ PixOrCopyIsLiteral (int /*<<< orphan*/  const* const) ; 
 int PixOrCopyLength (int /*<<< orphan*/  const* const) ; 
 size_t PixOrCopyLiteral (int /*<<< orphan*/  const* const,int) ; 
 int /*<<< orphan*/  VP8LPrefixEncodeBits (int,int*,int*) ; 

void VP8LHistogramAddSinglePixOrCopy(VP8LHistogram* const histo,
                                     const PixOrCopy* const v,
                                     int (*const distance_modifier)(int, int),
                                     int distance_modifier_arg0) {
  if (PixOrCopyIsLiteral(v)) {
    ++histo->alpha_[PixOrCopyLiteral(v, 3)];
    ++histo->red_[PixOrCopyLiteral(v, 2)];
    ++histo->literal_[PixOrCopyLiteral(v, 1)];
    ++histo->blue_[PixOrCopyLiteral(v, 0)];
  } else if (PixOrCopyIsCacheIdx(v)) {
    const int literal_ix =
        NUM_LITERAL_CODES + NUM_LENGTH_CODES + PixOrCopyCacheIdx(v);
    ++histo->literal_[literal_ix];
  } else {
    int code, extra_bits;
    VP8LPrefixEncodeBits(PixOrCopyLength(v), &code, &extra_bits);
    ++histo->literal_[NUM_LITERAL_CODES + code];
    if (distance_modifier == NULL) {
      VP8LPrefixEncodeBits(PixOrCopyDistance(v), &code, &extra_bits);
    } else {
      VP8LPrefixEncodeBits(
          distance_modifier(distance_modifier_arg0, PixOrCopyDistance(v)),
          &code, &extra_bits);
    }
    ++histo->distance_[code];
  }
}