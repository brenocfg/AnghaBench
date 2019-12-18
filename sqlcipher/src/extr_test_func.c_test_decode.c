#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {int /*<<< orphan*/  zMalloc; scalar_t__ szMalloc; int /*<<< orphan*/  enc; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  mem ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (int /*<<< orphan*/ *) ; 
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  Tcl_AppendStringsToObj (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_GetString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewDoubleObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char const*,int) ; 
 int /*<<< orphan*/ * Tcl_NewWideIntObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3GetVarint (int*,size_t*) ; 
 int /*<<< orphan*/  sqlite3VdbeSerialGet (int*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_blob (TYPE_1__*) ; 
 int sqlite3_value_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_value_double (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (TYPE_1__*) ; 
 scalar_t__ sqlite3_value_text (TYPE_1__*) ; 
 int sqlite3_value_type (TYPE_1__*) ; 

__attribute__((used)) static void test_decode(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  sqlite3 *db = sqlite3_context_db_handle(context);
  u8 *pRec;
  u8 *pEndHdr;                    /* Points to one byte past record header */
  u8 *pHdr;                       /* Current point in record header */
  u8 *pBody;                      /* Current point in record data */
  u64 nHdr;                       /* Bytes in record header */
  Tcl_Obj *pRet;                  /* Return value */

  pRet = Tcl_NewObj();
  Tcl_IncrRefCount(pRet);

  assert( argc==1 );
  pRec = (u8*)sqlite3_value_blob(argv[0]);

  pHdr = pRec + sqlite3GetVarint(pRec, &nHdr);
  pBody = pEndHdr = &pRec[nHdr];
  while( pHdr<pEndHdr ){
    Tcl_Obj *pVal = 0;
    u64 iSerialType;
    Mem mem;

    memset(&mem, 0, sizeof(mem));
    mem.db = db;
    mem.enc = ENC(db);
    pHdr += sqlite3GetVarint(pHdr, &iSerialType);
    pBody += sqlite3VdbeSerialGet(pBody, (u32)iSerialType, &mem);

    switch( sqlite3_value_type(&mem) ){
      case SQLITE_TEXT:
        pVal = Tcl_NewStringObj((const char*)sqlite3_value_text(&mem), -1);
        break;

      case SQLITE_BLOB: {
        char hexdigit[] = {
          '0', '1', '2', '3', '4', '5', '6', '7',
          '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
        };
        int n = sqlite3_value_bytes(&mem);
        u8 *z = (u8*)sqlite3_value_blob(&mem);
        int i;
        pVal = Tcl_NewStringObj("x'", -1);
        for(i=0; i<n; i++){
          char hex[3];
          hex[0] = hexdigit[((z[i] >> 4) & 0x0F)];
          hex[1] = hexdigit[(z[i] & 0x0F)];
          hex[2] = '\0';
          Tcl_AppendStringsToObj(pVal, hex, 0);
        }
        Tcl_AppendStringsToObj(pVal, "'", 0);
        break;
      }

      case SQLITE_FLOAT:
        pVal = Tcl_NewDoubleObj(sqlite3_value_double(&mem));
        break;

      case SQLITE_INTEGER:
        pVal = Tcl_NewWideIntObj(sqlite3_value_int64(&mem));
        break;

      case SQLITE_NULL:
        pVal = Tcl_NewStringObj("NULL", -1);
        break;

      default:
        assert( 0 );
    }

    Tcl_ListObjAppendElement(0, pRet, pVal);

    if( mem.szMalloc ){
      sqlite3DbFree(db, mem.zMalloc);
    }
  }

  sqlite3_result_text(context, Tcl_GetString(pRet), -1, SQLITE_TRANSIENT);
  Tcl_DecrRefCount(pRet);
}