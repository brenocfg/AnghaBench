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
struct Ziphuft {int dummy; } ;
typedef  int /*<<< orphan*/  fdi_decomp_state ;
typedef  int cab_ULONG ;
typedef  int cab_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  CAB (int /*<<< orphan*/ ) ; 
 int* ZIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zipcpdext ; 
 int /*<<< orphan*/  Zipcpdist ; 
 int /*<<< orphan*/  Zipcplens ; 
 int /*<<< orphan*/  Zipcplext ; 
 int /*<<< orphan*/  fdi ; 
 int fdi_Ziphuft_build (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct Ziphuft**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdi_Ziphuft_free (int /*<<< orphan*/ ,struct Ziphuft*) ; 
 int fdi_Zipinflate_codes (struct Ziphuft*,struct Ziphuft*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll ; 

__attribute__((used)) static cab_LONG fdi_Zipinflate_fixed(fdi_decomp_state *decomp_state)
{
  struct Ziphuft *fixed_tl;
  struct Ziphuft *fixed_td;
  cab_LONG fixed_bl, fixed_bd;
  cab_LONG i;                /* temporary variable */
  cab_ULONG *l;

  l = ZIP(ll);

  /* literal table */
  for(i = 0; i < 144; i++)
    l[i] = 8;
  for(; i < 256; i++)
    l[i] = 9;
  for(; i < 280; i++)
    l[i] = 7;
  for(; i < 288; i++)          /* make a complete, but wrong code set */
    l[i] = 8;
  fixed_bl = 7;
  if((i = fdi_Ziphuft_build(l, 288, 257, Zipcplens, Zipcplext, &fixed_tl, &fixed_bl, decomp_state)))
    return i;

  /* distance table */
  for(i = 0; i < 30; i++)      /* make an incomplete code set */
    l[i] = 5;
  fixed_bd = 5;
  if((i = fdi_Ziphuft_build(l, 30, 0, Zipcpdist, Zipcpdext, &fixed_td, &fixed_bd, decomp_state)) > 1)
  {
    fdi_Ziphuft_free(CAB(fdi), fixed_tl);
    return i;
  }

  /* decompress until an end-of-block code */
  i = fdi_Zipinflate_codes(fixed_tl, fixed_td, fixed_bl, fixed_bd, decomp_state);

  fdi_Ziphuft_free(CAB(fdi), fixed_td);
  fdi_Ziphuft_free(CAB(fdi), fixed_tl);
  return i;
}