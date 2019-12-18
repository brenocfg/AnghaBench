#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_9__ {int iPgOne; int /*<<< orphan*/  iMark; } ;
struct TYPE_7__ {int (* xWrite ) (TYPE_2__*,unsigned char*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ ApndFile ;

/* Variables and functions */
 int /*<<< orphan*/  APND_MARK_PREFIX ; 
 int APND_MARK_PREFIX_SZ ; 
 int APND_MARK_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apndWriteMark(ApndFile *p, sqlite3_file *pFile){
  int i;
  unsigned char a[APND_MARK_SIZE];
  memcpy(a, APND_MARK_PREFIX, APND_MARK_PREFIX_SZ);
  for(i=0; i<8; i++){
    a[APND_MARK_PREFIX_SZ+i] = (p->iPgOne >> (56 - i*8)) & 0xff;
  }
  return pFile->pMethods->xWrite(pFile, a, APND_MARK_SIZE, p->iMark);
}