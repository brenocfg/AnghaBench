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

/* Variables and functions */
 int* aKWCode ; 
 scalar_t__* aKWHash ; 
 int* aKWLen ; 
 scalar_t__* aKWNext ; 
 size_t* aKWOffset ; 
 int charMap (char const) ; 
 int /*<<< orphan*/  testcase (int) ; 
 char const toupper (char const) ; 
 char* zKWText ; 

__attribute__((used)) static int keywordCode(const char *z, int n, int *pType){
  int i, j;
  const char *zKW;
  if( n>=2 ){
    i = ((charMap(z[0])*4) ^ (charMap(z[n-1])*3) ^ n) % 127;
    for(i=((int)aKWHash[i])-1; i>=0; i=((int)aKWNext[i])-1){
      if( aKWLen[i]!=n ) continue;
      j = 0;
      zKW = &zKWText[aKWOffset[i]];
#ifdef SQLITE_ASCII
      while( j<n && (z[j]&~0x20)==zKW[j] ){ j++; }
#endif
#ifdef SQLITE_EBCDIC
      while( j<n && toupper(z[j])==zKW[j] ){ j++; }
#endif
      if( j<n ) continue;
      testcase( i==0 ); /* REINDEX */
      testcase( i==1 ); /* INDEXED */
      testcase( i==2 ); /* INDEX */
      testcase( i==3 ); /* DESC */
      testcase( i==4 ); /* ESCAPE */
      testcase( i==5 ); /* EACH */
      testcase( i==6 ); /* CHECK */
      testcase( i==7 ); /* KEY */
      testcase( i==8 ); /* BEFORE */
      testcase( i==9 ); /* FOREIGN */
      testcase( i==10 ); /* FOR */
      testcase( i==11 ); /* IGNORE */
      testcase( i==12 ); /* REGEXP */
      testcase( i==13 ); /* EXPLAIN */
      testcase( i==14 ); /* INSTEAD */
      testcase( i==15 ); /* ADD */
      testcase( i==16 ); /* DATABASE */
      testcase( i==17 ); /* AS */
      testcase( i==18 ); /* SELECT */
      testcase( i==19 ); /* TABLE */
      testcase( i==20 ); /* LEFT */
      testcase( i==21 ); /* THEN */
      testcase( i==22 ); /* END */
      testcase( i==23 ); /* DEFERRABLE */
      testcase( i==24 ); /* ELSE */
      testcase( i==25 ); /* EXCEPT */
      testcase( i==26 ); /* TRANSACTION */
      testcase( i==27 ); /* ACTION */
      testcase( i==28 ); /* ON */
      testcase( i==29 ); /* NATURAL */
      testcase( i==30 ); /* ALTER */
      testcase( i==31 ); /* RAISE */
      testcase( i==32 ); /* EXCLUSIVE */
      testcase( i==33 ); /* EXISTS */
      testcase( i==34 ); /* SAVEPOINT */
      testcase( i==35 ); /* INTERSECT */
      testcase( i==36 ); /* TRIGGER */
      testcase( i==37 ); /* REFERENCES */
      testcase( i==38 ); /* CONSTRAINT */
      testcase( i==39 ); /* INTO */
      testcase( i==40 ); /* OFFSET */
      testcase( i==41 ); /* OF */
      testcase( i==42 ); /* SET */
      testcase( i==43 ); /* TEMPORARY */
      testcase( i==44 ); /* TEMP */
      testcase( i==45 ); /* OR */
      testcase( i==46 ); /* UNIQUE */
      testcase( i==47 ); /* QUERY */
      testcase( i==48 ); /* WITHOUT */
      testcase( i==49 ); /* WITH */
      testcase( i==50 ); /* OUTER */
      testcase( i==51 ); /* RELEASE */
      testcase( i==52 ); /* ATTACH */
      testcase( i==53 ); /* HAVING */
      testcase( i==54 ); /* GROUP */
      testcase( i==55 ); /* UPDATE */
      testcase( i==56 ); /* BEGIN */
      testcase( i==57 ); /* INNER */
      testcase( i==58 ); /* RANGE */
      testcase( i==59 ); /* BETWEEN */
      testcase( i==60 ); /* NOTHING */
      testcase( i==61 ); /* GLOB */
      testcase( i==62 ); /* BY */
      testcase( i==63 ); /* CASCADE */
      testcase( i==64 ); /* ASC */
      testcase( i==65 ); /* DELETE */
      testcase( i==66 ); /* CASE */
      testcase( i==67 ); /* COLLATE */
      testcase( i==68 ); /* CREATE */
      testcase( i==69 ); /* CURRENT_DATE */
      testcase( i==70 ); /* DETACH */
      testcase( i==71 ); /* IMMEDIATE */
      testcase( i==72 ); /* JOIN */
      testcase( i==73 ); /* INSERT */
      testcase( i==74 ); /* LIKE */
      testcase( i==75 ); /* MATCH */
      testcase( i==76 ); /* PLAN */
      testcase( i==77 ); /* ANALYZE */
      testcase( i==78 ); /* PRAGMA */
      testcase( i==79 ); /* ABORT */
      testcase( i==80 ); /* VALUES */
      testcase( i==81 ); /* VIRTUAL */
      testcase( i==82 ); /* LIMIT */
      testcase( i==83 ); /* WHEN */
      testcase( i==84 ); /* NOTNULL */
      testcase( i==85 ); /* NOT */
      testcase( i==86 ); /* NO */
      testcase( i==87 ); /* NULL */
      testcase( i==88 ); /* WHERE */
      testcase( i==89 ); /* RECURSIVE */
      testcase( i==90 ); /* AFTER */
      testcase( i==91 ); /* RENAME */
      testcase( i==92 ); /* AND */
      testcase( i==93 ); /* DEFAULT */
      testcase( i==94 ); /* AUTOINCREMENT */
      testcase( i==95 ); /* TO */
      testcase( i==96 ); /* IN */
      testcase( i==97 ); /* CAST */
      testcase( i==98 ); /* COLUMN */
      testcase( i==99 ); /* COMMIT */
      testcase( i==100 ); /* CONFLICT */
      testcase( i==101 ); /* CROSS */
      testcase( i==102 ); /* CURRENT_TIMESTAMP */
      testcase( i==103 ); /* CURRENT_TIME */
      testcase( i==104 ); /* CURRENT */
      testcase( i==105 ); /* PARTITION */
      testcase( i==106 ); /* DEFERRED */
      testcase( i==107 ); /* DISTINCT */
      testcase( i==108 ); /* IS */
      testcase( i==109 ); /* DROP */
      testcase( i==110 ); /* PRECEDING */
      testcase( i==111 ); /* FAIL */
      testcase( i==112 ); /* FILTER */
      testcase( i==113 ); /* REPLACE */
      testcase( i==114 ); /* FOLLOWING */
      testcase( i==115 ); /* FROM */
      testcase( i==116 ); /* FULL */
      testcase( i==117 ); /* IF */
      testcase( i==118 ); /* ISNULL */
      testcase( i==119 ); /* ORDER */
      testcase( i==120 ); /* RESTRICT */
      testcase( i==121 ); /* OVER */
      testcase( i==122 ); /* RIGHT */
      testcase( i==123 ); /* ROLLBACK */
      testcase( i==124 ); /* ROWS */
      testcase( i==125 ); /* ROW */
      testcase( i==126 ); /* UNBOUNDED */
      testcase( i==127 ); /* UNION */
      testcase( i==128 ); /* USING */
      testcase( i==129 ); /* VACUUM */
      testcase( i==130 ); /* VIEW */
      testcase( i==131 ); /* WINDOW */
      testcase( i==132 ); /* DO */
      testcase( i==133 ); /* INITIALLY */
      testcase( i==134 ); /* ALL */
      testcase( i==135 ); /* PRIMARY */
      *pType = aKWCode[i];
      break;
    }
  }
  return n;
}