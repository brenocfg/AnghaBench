#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {int nVertex; } ;
typedef  TYPE_1__ GeoPoly ;

/* Variables and functions */
 int /*<<< orphan*/  GeoX (TYPE_1__*,int) ; 
 int /*<<< orphan*/  GeoY (TYPE_1__*,int) ; 
 TYPE_1__* geopolyFuncParam (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pointBeneathLine (double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void geopolyContainsPointFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  GeoPoly *p1 = geopolyFuncParam(context, argv[0], 0);
  double x0 = sqlite3_value_double(argv[1]);
  double y0 = sqlite3_value_double(argv[2]);
  int v = 0;
  int cnt = 0;
  int ii;
  if( p1==0 ) return;
  for(ii=0; ii<p1->nVertex-1; ii++){
    v = pointBeneathLine(x0,y0,GeoX(p1,ii), GeoY(p1,ii),
                               GeoX(p1,ii+1),GeoY(p1,ii+1));
    if( v==2 ) break;
    cnt += v;
  }
  if( v!=2 ){
    v = pointBeneathLine(x0,y0,GeoX(p1,ii), GeoY(p1,ii),
                               GeoX(p1,0),  GeoY(p1,0));
  }
  if( v==2 ){
    sqlite3_result_int(context, 1);
  }else if( ((v+cnt)&1)==0 ){
    sqlite3_result_int(context, 0);
  }else{
    sqlite3_result_int(context, 2);
  }
  sqlite3_free(p1);
}