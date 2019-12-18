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
struct TYPE_3__ {int /*<<< orphan*/  pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  scalar_t__ LsmPgno ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 scalar_t__ lsmFsRedirectPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fsPageRedirects(FileSystem *pFS, Segment *p, LsmPgno iPg){
  return (iPg!=0 && iPg!=lsmFsRedirectPage(pFS, p->pRedirect, iPg));
}