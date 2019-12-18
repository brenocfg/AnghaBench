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
typedef  int /*<<< orphan*/  Str ;

/* Variables and functions */
 int /*<<< orphan*/  strPrintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strPrintfArray (int /*<<< orphan*/ *,char*,char*,char**,int) ; 

__attribute__((used)) static void getRbudiffQuery(
  const char *zTab,
  char **azCol,
  int nPK,
  int bOtaRowid,
  Str *pSql
){
  int i;

  /* First the newly inserted rows: **/ 
  strPrintf(pSql, "SELECT ");
  strPrintfArray(pSql, ", ", "%s", azCol, -1);
  strPrintf(pSql, ", 0, ");       /* Set ota_control to 0 for an insert */
  strPrintfArray(pSql, ", ", "NULL", azCol, -1);
  strPrintf(pSql, " FROM aux.%Q AS n WHERE NOT EXISTS (\n", zTab);
  strPrintf(pSql, "    SELECT 1 FROM ", zTab);
  strPrintf(pSql, " main.%Q AS o WHERE ", zTab);
  strPrintfArray(pSql, " AND ", "(n.%Q = o.%Q)", azCol, nPK);
  strPrintf(pSql, "\n) AND ");
  strPrintfArray(pSql, " AND ", "(n.%Q IS NOT NULL)", azCol, nPK);

  /* Deleted rows: */
  strPrintf(pSql, "\nUNION ALL\nSELECT ");
  strPrintfArray(pSql, ", ", "%s", azCol, nPK);
  if( azCol[nPK] ){
    strPrintf(pSql, ", ");
    strPrintfArray(pSql, ", ", "NULL", &azCol[nPK], -1);
  }
  strPrintf(pSql, ", 1, ");       /* Set ota_control to 1 for a delete */
  strPrintfArray(pSql, ", ", "NULL", azCol, -1);
  strPrintf(pSql, " FROM main.%Q AS n WHERE NOT EXISTS (\n", zTab);
  strPrintf(pSql, "    SELECT 1 FROM ", zTab);
  strPrintf(pSql, " aux.%Q AS o WHERE ", zTab);
  strPrintfArray(pSql, " AND ", "(n.%Q = o.%Q)", azCol, nPK);
  strPrintf(pSql, "\n) AND ");
  strPrintfArray(pSql, " AND ", "(n.%Q IS NOT NULL)", azCol, nPK);

  /* Updated rows. If all table columns are part of the primary key, there 
  ** can be no updates. In this case this part of the compound SELECT can
  ** be omitted altogether. */
  if( azCol[nPK] ){
    strPrintf(pSql, "\nUNION ALL\nSELECT ");
    strPrintfArray(pSql, ", ", "n.%s", azCol, nPK);
    strPrintf(pSql, ",\n");
    strPrintfArray(pSql, " ,\n", 
        "    CASE WHEN n.%s IS o.%s THEN NULL ELSE n.%s END", &azCol[nPK], -1
    );

    if( bOtaRowid==0 ){
      strPrintf(pSql, ", '");
      strPrintfArray(pSql, "", ".", azCol, nPK);
      strPrintf(pSql, "' ||\n");
    }else{
      strPrintf(pSql, ",\n");
    }
    strPrintfArray(pSql, " ||\n", 
        "    CASE WHEN n.%s IS o.%s THEN '.' ELSE 'x' END", &azCol[nPK], -1
    );
    strPrintf(pSql, "\nAS ota_control, ");
    strPrintfArray(pSql, ", ", "NULL", azCol, nPK);
    strPrintf(pSql, ",\n");
    strPrintfArray(pSql, " ,\n", 
        "    CASE WHEN n.%s IS o.%s THEN NULL ELSE o.%s END", &azCol[nPK], -1
    );

    strPrintf(pSql, "\nFROM main.%Q AS o, aux.%Q AS n\nWHERE ", zTab, zTab);
    strPrintfArray(pSql, " AND ", "(n.%Q = o.%Q)", azCol, nPK);
    strPrintf(pSql, " AND ota_control LIKE '%%x%%'");
  }

  /* Now add an ORDER BY clause to sort everything by PK. */
  strPrintf(pSql, "\nORDER BY ");
  for(i=1; i<=nPK; i++) strPrintf(pSql, "%s%d", ((i>1)?", ":""), i);
}