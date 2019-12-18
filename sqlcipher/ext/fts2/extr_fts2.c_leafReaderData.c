#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nData; } ;
struct TYPE_5__ {char const* pData; TYPE_1__ term; } ;
typedef  TYPE_2__ LeafReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int getVarint32 (char const*,int*) ; 

__attribute__((used)) static const char *leafReaderData(LeafReader *pReader){
  int n, nData;
  assert( pReader->term.nData>0 );
  n = getVarint32(pReader->pData, &nData);
  return pReader->pData+n;
}