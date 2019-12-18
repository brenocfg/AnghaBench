#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct CfgParam   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct CfgParam {char const* zParam; int eParam; } ;
struct TYPE_4__ {int bFastInsert; int /*<<< orphan*/  pBt; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int BT_CONTROL_AUTOCKPT ; 
 int BT_CONTROL_BLKSZ ; 
 int BT_CONTROL_MULTIPROC ; 
 int BT_CONTROL_PAGESZ ; 
 int BT_CONTROL_SAFETY ; 
 int SQLITE4_OK ; 
 int sqlite4BtControl (int /*<<< orphan*/ ,int,void*) ; 
 int strlen (char const*) ; 
 int testArgSelect (TYPE_3__*,char*,char const*,int*) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 scalar_t__ testMalloc (int) ; 
 int testParseInt (char const*,int*) ; 
 scalar_t__ testParseOption (char const**,char const**,char const**,char*) ; 

__attribute__((used)) static int testBtConfigure(BtDb *pDb, const char *zCfg, int *pbMt){
  int rc = SQLITE4_OK;

  if( zCfg ){
    struct CfgParam {
      const char *zParam;
      int eParam;
    } aParam[] = {
      { "safety",         BT_CONTROL_SAFETY },
      { "autockpt",       BT_CONTROL_AUTOCKPT },
      { "multiproc",      BT_CONTROL_MULTIPROC },
      { "blksz",          BT_CONTROL_BLKSZ },
      { "pagesz",         BT_CONTROL_PAGESZ },
      { "mt",             -1 },
      { "fastinsert",     -2 },
      { 0, 0 }
    };
    const char *z = zCfg;
    int n = strlen(z);
    char *aSpace;
    const char *zOpt;
    const char *zArg;

    aSpace = (char*)testMalloc(n+2);
    while( rc==SQLITE4_OK && 0==testParseOption(&z, &zOpt, &zArg, aSpace) ){
      int i;
      int iVal;
      rc = testArgSelect(aParam, "param", zOpt, &i);
      if( rc!=SQLITE4_OK ) break;

      rc = testParseInt(zArg, &iVal);
      if( rc!=SQLITE4_OK ) break;

      switch( aParam[i].eParam ){
        case -1:
          *pbMt = iVal;
          break;
        case -2:
          pDb->bFastInsert = 1;
          break;
        default:
          rc = sqlite4BtControl(pDb->pBt, aParam[i].eParam, (void*)&iVal);
          break;
      }
    }
    testFree(aSpace);
  }

  return rc;
}