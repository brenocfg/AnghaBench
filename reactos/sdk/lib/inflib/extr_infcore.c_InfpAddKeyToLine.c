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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * Key; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  PCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

PVOID
InfpAddKeyToLine(PINFCACHELINE Line,
                 PCWSTR Key)
{
  if (Line == NULL)
    {
      DPRINT1("Invalid Line\n");
      return NULL;
    }

  if (Line->Key != NULL)
    {
      DPRINT1("Line already has a key\n");
      return NULL;
    }

  Line->Key = (PWCHAR)MALLOC((strlenW(Key) + 1) * sizeof(WCHAR));
  if (Line->Key == NULL)
    {
      DPRINT1("MALLOC() failed\n");
      return NULL;
    }

  strcpyW(Line->Key, Key);

  return (PVOID)Line->Key;
}