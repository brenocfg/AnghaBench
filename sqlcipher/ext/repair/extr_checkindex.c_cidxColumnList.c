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
struct TYPE_5__ {size_t bDesc; int bKey; int /*<<< orphan*/  zExpr; } ;
struct TYPE_4__ {int nCol; TYPE_2__* aCol; } ;
typedef  TYPE_1__ CidxIndex ;
typedef  TYPE_2__ CidxColumn ;

/* Variables and functions */
 int CIDX_CLIST_ALL ; 
#define  CIDX_CLIST_CURRENT_KEY 131 
#define  CIDX_CLIST_ORDERBY 130 
#define  CIDX_CLIST_SUBEXPR 129 
#define  CIDX_CLIST_SUBWHERE 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* cidxMprintf (int*,char*,char*,char const*,int,...) ; 

__attribute__((used)) static char *cidxColumnList(
  int *pRc,                       /* IN/OUT: Error code */
  const char *zIdx,
  CidxIndex *pIdx,                /* Indexed columns */
  int eType                       /* True to include ASC/DESC */
){
  char *zRet = 0;
  if( *pRc==SQLITE_OK ){
    const char *aDir[2] = {"", " DESC"};
    int i;
    const char *zSep = "";

    for(i=0; i<pIdx->nCol; i++){
      CidxColumn *p = &pIdx->aCol[i];
      assert( pIdx->aCol[i].bDesc==0 || pIdx->aCol[i].bDesc==1 );
      switch( eType ){

        case CIDX_CLIST_ORDERBY:
          zRet = cidxMprintf(pRc, "%z%s%d%s", zRet, zSep, i+1, aDir[p->bDesc]);
          zSep = ",";
          break;

        case CIDX_CLIST_CURRENT_KEY:
          zRet = cidxMprintf(pRc, "%z%squote(i%d)", zRet, zSep, i);
          zSep = "||','||";
          break;

        case CIDX_CLIST_SUBWHERE:
          if( p->bKey==0 ){
            zRet = cidxMprintf(pRc, "%z%s%s IS i.i%d", zRet, 
                zSep, p->zExpr, i
            );
            zSep = " AND ";
          }
          break;

        case CIDX_CLIST_SUBEXPR:
          if( p->bKey==1 ){
            zRet = cidxMprintf(pRc, "%z%s%s IS i.i%d", zRet, 
                zSep, p->zExpr, i
            );
            zSep = " AND ";
          }
          break;

        default:
          assert( eType==CIDX_CLIST_ALL );
          zRet = cidxMprintf(pRc, "%z%s(%s) AS i%d", zRet, zSep, p->zExpr, i);
          zSep = ", ";
          break;
      }
    }
  }

  return zRet;
}