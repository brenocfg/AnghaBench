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
typedef  int /*<<< orphan*/  CTRepr ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_CONST ; 
 int CTF_VOLATILE ; 
 int /*<<< orphan*/  ctype_preplit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ctype_prepqual(CTRepr *ctr, CTInfo info)
{
  if ((info & CTF_VOLATILE)) ctype_preplit(ctr, "volatile");
  if ((info & CTF_CONST)) ctype_preplit(ctr, "const");
}