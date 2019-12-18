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
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  Cx86cpuid ;
typedef  int Bool ;

/* Variables and functions */
#define  CPU_FIRM_AMD 130 
#define  CPU_FIRM_INTEL 129 
#define  CPU_FIRM_VIA 128 
 int True ; 
 int /*<<< orphan*/  x86cpuid_CheckAndRead (int /*<<< orphan*/ *) ; 
 int x86cpuid_GetFamily (int /*<<< orphan*/ *) ; 
 int x86cpuid_GetFirm (int /*<<< orphan*/ *) ; 
 int x86cpuid_GetModel (int /*<<< orphan*/ *) ; 

Bool CPU_Is_InOrder()
{
  Cx86cpuid p;
  int firm;
  UInt32 family, model;
  if (!x86cpuid_CheckAndRead(&p))
    return True;
  family = x86cpuid_GetFamily(&p);
  model = x86cpuid_GetModel(&p);
  firm = x86cpuid_GetFirm(&p);
  switch (firm)
  {
    case CPU_FIRM_INTEL: return (family < 6 || (family == 6 && model == 0x100C));
    case CPU_FIRM_AMD: return (family < 5 || (family == 5 && (model < 6 || model == 0xA)));
    case CPU_FIRM_VIA: return (family < 6 || (family == 6 && model < 0xF));
  }
  return True;
}