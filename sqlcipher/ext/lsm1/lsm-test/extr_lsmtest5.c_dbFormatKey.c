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
struct TYPE_3__ {int nFanout; } ;
typedef  TYPE_1__ DbParameters ;

/* Variables and functions */
 int /*<<< orphan*/  DB_KEY_BYTES ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void dbFormatKey(
  DbParameters *pParam,
  int iLevel,
  int iKey,                       /* Key value */
  char *aBuf                      /* Write key string here */
){
  if( iLevel==0 ){
    snprintf(aBuf, DB_KEY_BYTES, "k.%.10d", iKey);
  }else{
    int f = 1;
    int i;
    for(i=0; i<iLevel; i++) f = f * pParam->nFanout;
    snprintf(aBuf, DB_KEY_BYTES, "c.%d.%.10d", iLevel, f*(iKey/f));
  }
}