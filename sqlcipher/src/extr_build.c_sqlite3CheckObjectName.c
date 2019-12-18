#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  busy; } ;
struct TYPE_8__ {TYPE_1__ init; } ;
struct TYPE_7__ {scalar_t__ nested; TYPE_3__* db; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*,char const*) ; 
 scalar_t__ sqlite3StrNICmp (char const*,char*,int) ; 
 scalar_t__ sqlite3WritableSchema (TYPE_3__*) ; 

int sqlite3CheckObjectName(Parse *pParse, const char *zName){
  if( !pParse->db->init.busy && pParse->nested==0 
          && sqlite3WritableSchema(pParse->db)==0
          && 0==sqlite3StrNICmp(zName, "sqlite_", 7) ){
    sqlite3ErrorMsg(pParse, "object name reserved for internal use: %s", zName);
    return SQLITE_ERROR;
  }
  return SQLITE_OK;
}