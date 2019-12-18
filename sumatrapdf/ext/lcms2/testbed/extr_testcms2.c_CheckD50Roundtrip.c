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
typedef  int /*<<< orphan*/  cmsS15Fixed16Number ;
typedef  int cmsInt32Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,double) ; 
 double _cms15Fixed16toDouble (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsDoubleTo15Fixed16 (int /*<<< orphan*/ ,double) ; 
 double cmsD50X ; 
 double cmsD50Y ; 
 double cmsD50Z ; 
 double fabs (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static
cmsInt32Number CheckD50Roundtrip(void)
{
    cmsFloat64Number cmsD50X_2 =  0.96420288;
    cmsFloat64Number cmsD50Y_2 =  1.0;
    cmsFloat64Number cmsD50Z_2 = 0.82490540;

    cmsS15Fixed16Number xe = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50X);
    cmsS15Fixed16Number ye = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50Y);
    cmsS15Fixed16Number ze = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50Z);

    cmsFloat64Number x =  _cms15Fixed16toDouble(DbgThread(), xe);
    cmsFloat64Number y =  _cms15Fixed16toDouble(DbgThread(), ye);
    cmsFloat64Number z =  _cms15Fixed16toDouble(DbgThread(), ze);

    double dx = fabs(cmsD50X - x);
    double dy = fabs(cmsD50Y - y);
    double dz = fabs(cmsD50Z - z);

    double euc = sqrt(dx*dx + dy*dy + dz* dz);

    if (euc > 1E-5) {

        Fail("D50 roundtrip |err| > (%f) ", euc);
        return 0;
    }

    xe = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50X_2);
    ye = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50Y_2);
    ze = _cmsDoubleTo15Fixed16(DbgThread(), cmsD50Z_2);

    x =  _cms15Fixed16toDouble(DbgThread(), xe);
    y =  _cms15Fixed16toDouble(DbgThread(), ye);
    z =  _cms15Fixed16toDouble(DbgThread(), ze);

    dx = fabs(cmsD50X_2 - x);
    dy = fabs(cmsD50Y_2 - y);
    dz = fabs(cmsD50Z_2 - z);

    euc = sqrt(dx*dx + dy*dy + dz* dz);

    if (euc > 1E-5) {

        Fail("D50 roundtrip |err| > (%f) ", euc);
        return 0;
    }


    return 1;
}