#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  TYPE_1__ CXzStream ;

/* Variables and functions */
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  Xz_Construct (TYPE_1__*) ; 
 int /*<<< orphan*/  Xz_Free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Xz_WriteFooter (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Xz_WriteHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_Alloc ; 

SRes Xz_EncodeEmpty(ISeqOutStream *outStream)
{
  SRes res;
  CXzStream xz;
  Xz_Construct(&xz);
  res = Xz_WriteHeader(xz.flags, outStream);
  if (res == SZ_OK)
    res = Xz_WriteFooter(&xz, outStream);
  Xz_Free(&xz, &g_Alloc);
  return res;
}