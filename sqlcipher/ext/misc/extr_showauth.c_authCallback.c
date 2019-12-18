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
typedef  int /*<<< orphan*/  zOpSpace ;

/* Variables and functions */
#define  SQLITE_ALTER_TABLE 161 
#define  SQLITE_ANALYZE 160 
#define  SQLITE_ATTACH 159 
#define  SQLITE_COPY 158 
#define  SQLITE_CREATE_INDEX 157 
#define  SQLITE_CREATE_TABLE 156 
#define  SQLITE_CREATE_TEMP_INDEX 155 
#define  SQLITE_CREATE_TEMP_TABLE 154 
#define  SQLITE_CREATE_TEMP_TRIGGER 153 
#define  SQLITE_CREATE_TEMP_VIEW 152 
#define  SQLITE_CREATE_TRIGGER 151 
#define  SQLITE_CREATE_VIEW 150 
#define  SQLITE_CREATE_VTABLE 149 
#define  SQLITE_DELETE 148 
#define  SQLITE_DETACH 147 
#define  SQLITE_DROP_INDEX 146 
#define  SQLITE_DROP_TABLE 145 
#define  SQLITE_DROP_TEMP_INDEX 144 
#define  SQLITE_DROP_TEMP_TABLE 143 
#define  SQLITE_DROP_TEMP_TRIGGER 142 
#define  SQLITE_DROP_TEMP_VIEW 141 
#define  SQLITE_DROP_TRIGGER 140 
#define  SQLITE_DROP_VIEW 139 
#define  SQLITE_DROP_VTABLE 138 
#define  SQLITE_FUNCTION 137 
#define  SQLITE_INSERT 136 
 int SQLITE_OK ; 
#define  SQLITE_PRAGMA 135 
#define  SQLITE_READ 134 
#define  SQLITE_RECURSIVE 133 
#define  SQLITE_REINDEX 132 
#define  SQLITE_SAVEPOINT 131 
#define  SQLITE_SELECT 130 
#define  SQLITE_TRANSACTION 129 
#define  SQLITE_UPDATE 128 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 

__attribute__((used)) static int authCallback(
  void *pClientData,
  int op,
  const char *z1,
  const char *z2,
  const char *z3,
  const char *z4
){
  const char *zOp;
  char zOpSpace[50];
  switch( op ){
    case SQLITE_CREATE_INDEX:        zOp = "CREATE_INDEX";        break;
    case SQLITE_CREATE_TABLE:        zOp = "CREATE_TABLE";        break;
    case SQLITE_CREATE_TEMP_INDEX:   zOp = "CREATE_TEMP_INDEX";   break;
    case SQLITE_CREATE_TEMP_TABLE:   zOp = "CREATE_TEMP_TABLE";   break;
    case SQLITE_CREATE_TEMP_TRIGGER: zOp = "CREATE_TEMP_TRIGGER"; break;
    case SQLITE_CREATE_TEMP_VIEW:    zOp = "CREATE_TEMP_VIEW";    break;
    case SQLITE_CREATE_TRIGGER:      zOp = "CREATE_TRIGGER";      break;
    case SQLITE_CREATE_VIEW:         zOp = "CREATE_VIEW";         break;
    case SQLITE_DELETE:              zOp = "DELETE";              break;
    case SQLITE_DROP_INDEX:          zOp = "DROP_INDEX";          break;
    case SQLITE_DROP_TABLE:          zOp = "DROP_TABLE";          break;
    case SQLITE_DROP_TEMP_INDEX:     zOp = "DROP_TEMP_INDEX";     break;
    case SQLITE_DROP_TEMP_TABLE:     zOp = "DROP_TEMP_TABLE";     break;
    case SQLITE_DROP_TEMP_TRIGGER:   zOp = "DROP_TEMP_TRIGGER";   break;
    case SQLITE_DROP_TEMP_VIEW:      zOp = "DROP_TEMP_VIEW";      break;
    case SQLITE_DROP_TRIGGER:        zOp = "DROP_TRIGGER";        break;
    case SQLITE_DROP_VIEW:           zOp = "DROP_VIEW";           break;
    case SQLITE_INSERT:              zOp = "INSERT";              break;
    case SQLITE_PRAGMA:              zOp = "PRAGMA";              break;
    case SQLITE_READ:                zOp = "READ";                break;
    case SQLITE_SELECT:              zOp = "SELECT";              break;
    case SQLITE_TRANSACTION:         zOp = "TRANSACTION";         break;
    case SQLITE_UPDATE:              zOp = "UPDATE";              break;
    case SQLITE_ATTACH:              zOp = "ATTACH";              break;
    case SQLITE_DETACH:              zOp = "DETACH";              break;
    case SQLITE_ALTER_TABLE:         zOp = "ALTER_TABLE";         break;
    case SQLITE_REINDEX:             zOp = "REINDEX";             break;
    case SQLITE_ANALYZE:             zOp = "ANALYZE";             break;
    case SQLITE_CREATE_VTABLE:       zOp = "CREATE_VTABLE";       break;
    case SQLITE_DROP_VTABLE:         zOp = "DROP_VTABLE";         break;
    case SQLITE_FUNCTION:            zOp = "FUNCTION";            break;
    case SQLITE_SAVEPOINT:           zOp = "SAVEPOINT";           break;
    case SQLITE_COPY:                zOp = "COPY";                break;
    case SQLITE_RECURSIVE:           zOp = "RECURSIVE";           break;


    default: {
      sqlite3_snprintf(sizeof(zOpSpace), zOpSpace, "%d", op);
      zOp = zOpSpace;
      break;
    }
  }
  if( z1==0 ) z1 = "NULL";
  if( z2==0 ) z2 = "NULL";
  if( z3==0 ) z3 = "NULL";
  if( z4==0 ) z4 = "NULL";
  printf("AUTH: %s,%s,%s,%s,%s\n", zOp, z1, z2, z3, z4);
  return SQLITE_OK;
}