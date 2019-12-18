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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void flipover(uint8 * data)
{
  uint8 adata[128];
  int index;

  if (data == 0)
  {
    return;
  }
  memcpy(adata, data, 128);
  for (index = 0; index <= 31; index++)
  {
    data[127 - (index * 4 + 3)] = adata[index * 4];
    data[127 - (index * 4 + 2)] = adata[index * 4 + 1];
    data[127 - (index * 4 + 1)] = adata[index * 4 + 2];
    data[127 - index * 4] = adata[index * 4 + 3];
  }
}