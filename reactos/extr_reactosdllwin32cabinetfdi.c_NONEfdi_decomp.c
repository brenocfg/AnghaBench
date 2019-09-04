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
typedef  int /*<<< orphan*/  fdi_decomp_state ;

/* Variables and functions */
 int /*<<< orphan*/  CAB (int /*<<< orphan*/ ) ; 
 int CAB_BLOCKMAX ; 
 int DECR_DATAFORMAT ; 
 int DECR_ILLEGALDATA ; 
 int DECR_OK ; 
 int /*<<< orphan*/  inbuf ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  outbuf ; 

__attribute__((used)) static int NONEfdi_decomp(int inlen, int outlen, fdi_decomp_state *decomp_state)
{
  if (inlen != outlen) return DECR_ILLEGALDATA;
  if (outlen > CAB_BLOCKMAX) return DECR_DATAFORMAT;
  memcpy(CAB(outbuf), CAB(inbuf), (size_t) inlen);
  return DECR_OK;
}