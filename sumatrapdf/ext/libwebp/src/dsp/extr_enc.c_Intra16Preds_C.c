#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCMode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  HorizontalPred (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int I16DC16 ; 
 int I16HE16 ; 
 int I16TM16 ; 
 int I16VE16 ; 
 int /*<<< orphan*/  TrueMotion (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  VerticalPred (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void Intra16Preds_C(uint8_t* dst,
                           const uint8_t* left, const uint8_t* top) {
  DCMode(I16DC16 + dst, left, top, 16, 16, 5);
  VerticalPred(I16VE16 + dst, top, 16);
  HorizontalPred(I16HE16 + dst, left, 16);
  TrueMotion(I16TM16 + dst, left, top, 16);
}