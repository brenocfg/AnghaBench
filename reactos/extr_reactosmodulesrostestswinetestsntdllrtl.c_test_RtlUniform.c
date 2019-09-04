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
typedef  int ULONGLONG ;
typedef  int ULONG ;

/* Variables and functions */
 int MAXLONG ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 
 int pRtlUniform (int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_RtlUniform(void)
{
    ULONGLONG num;
    ULONG seed;
    ULONG seed_bak;
    ULONG expected;
    ULONG result;

    if (!pRtlUniform)
    {
        win_skip("RtlUniform is not available\n");
        return;
    }

/*
 * According to the documentation RtlUniform is using D.H. Lehmer's 1948
 * algorithm. This algorithm is:
 *
 * seed = (seed * const_1 + const_2) % const_3;
 *
 * According to the documentation the random number is distributed over
 * [0..MAXLONG]. Therefore const_3 is MAXLONG + 1:
 *
 * seed = (seed * const_1 + const_2) % (MAXLONG + 1);
 *
 * Because MAXLONG is 0x7fffffff (and MAXLONG + 1 is 0x80000000) the
 * algorithm can be expressed without division as:
 *
 * seed = (seed * const_1 + const_2) & MAXLONG;
 *
 * To find out const_2 we just call RtlUniform with seed set to 0:
 */
    seed = 0;
    expected = 0x7fffffc3;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0)) returns %x, expected %x\n",
        result, expected);
/*
 * The algorithm is now:
 *
 * seed = (seed * const_1 + 0x7fffffc3) & MAXLONG;
 *
 * To find out const_1 we can use:
 *
 * const_1 = RtlUniform(1) - 0x7fffffc3;
 *
 * If that does not work a search loop can try all possible values of
 * const_1 and compare to the result to RtlUniform(1).
 * This way we find out that const_1 is 0xffffffed.
 *
 * For seed = 1 the const_2 is 0x7fffffc4:
 */
    seed = 1;
    expected = seed * 0xffffffed + 0x7fffffc3 + 1;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 1)) returns %x, expected %x\n",
        result, expected);
/*
 * For seed = 2 the const_2 is 0x7fffffc3:
 */
    seed = 2;
    expected = seed * 0xffffffed + 0x7fffffc3;
    result = pRtlUniform(&seed);

/*
 * Windows Vista uses different algorithms, so skip the rest of the tests
 * until that is figured out. Trace output for the failures is about 10.5 MB!
 */

    if (result == 0x7fffff9f) {
        skip("Most likely running on Windows Vista which uses a different algorithm\n");
        return;
    }

    ok(result == expected,
        "RtlUniform(&seed (seed == 2)) returns %x, expected %x\n",
        result, expected);

/*
 * More tests show that if seed is odd the result must be incremented by 1:
 */
    seed = 3;
    expected = seed * 0xffffffed + 0x7fffffc3 + (seed & 1);
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 3)) returns %x, expected %x\n",
        result, expected);

    seed = 0x6bca1aa;
    expected = seed * 0xffffffed + 0x7fffffc3;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0x6bca1aa)) returns %x, expected %x\n",
        result, expected);

    seed = 0x6bca1ab;
    expected = seed * 0xffffffed + 0x7fffffc3 + 1;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0x6bca1ab)) returns %x, expected %x\n",
        result, expected);
/*
 * When seed is 0x6bca1ac there is an exception:
 */
    seed = 0x6bca1ac;
    expected = seed * 0xffffffed + 0x7fffffc3 + 2;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0x6bca1ac)) returns %x, expected %x\n",
        result, expected);
/*
 * Note that up to here const_3 is not used
 * (the highest bit of the result is not set).
 *
 * Starting with 0x6bca1ad: If seed is even the result must be incremented by 1:
 */
    seed = 0x6bca1ad;
    expected = (seed * 0xffffffed + 0x7fffffc3) & MAXLONG;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0x6bca1ad)) returns %x, expected %x\n",
        result, expected);

    seed = 0x6bca1ae;
    expected = (seed * 0xffffffed + 0x7fffffc3 + 1) & MAXLONG;
    result = pRtlUniform(&seed);
    ok(result == expected,
        "RtlUniform(&seed (seed == 0x6bca1ae)) returns %x, expected %x\n",
        result, expected);
/*
 * There are several ranges where for odd or even seed the result must be
 * incremented by 1. You can see this ranges in the following test.
 *
 * For a full test use one of the following loop heads:
 *
 *  for (num = 0; num <= 0xffffffff; num++) {
 *      seed = num;
 *      ...
 *
 *  seed = 0;
 *  for (num = 0; num <= 0xffffffff; num++) {
 *      ...
 */
    seed = 0;
    for (num = 0; num <= 100000; num++) {

	expected = seed * 0xffffffed + 0x7fffffc3;
	if (seed < 0x6bca1ac) {
	    expected = expected + (seed & 1);
	} else if (seed == 0x6bca1ac) {
	    expected = (expected + 2) & MAXLONG;
	} else if (seed < 0xd79435c) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x1435e50b) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x1af286ba) { 
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x21af2869) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x286bca18) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x2f286bc7) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x35e50d77) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x3ca1af26) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x435e50d5) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x4a1af284) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x50d79433) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x579435e2) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x5e50d792) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x650d7941) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x6bca1af0) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x7286bc9f) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x79435e4e) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x7ffffffd) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x86bca1ac) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed == 0x86bca1ac) {
	    expected = (expected + 1) & MAXLONG;
	} else if (seed < 0x8d79435c) {
	    expected = expected + (seed & 1);
	} else if (seed < 0x9435e50b) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0x9af286ba) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xa1af2869) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xa86bca18) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xaf286bc7) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed == 0xaf286bc7) {
	    expected = (expected + 2) & MAXLONG;
	} else if (seed < 0xb5e50d77) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xbca1af26) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xc35e50d5) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xca1af284) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xd0d79433) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xd79435e2) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xde50d792) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xe50d7941) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xebca1af0) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xf286bc9f) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else if (seed < 0xf9435e4e) {
	    expected = expected + (seed & 1);
	} else if (seed < 0xfffffffd) {
	    expected = (expected + (~seed & 1)) & MAXLONG;
	} else {
	    expected = expected + (seed & 1);
	} /* if */
        seed_bak = seed;
        result = pRtlUniform(&seed);
        ok(result == expected,
                "test: 0x%s RtlUniform(&seed (seed == %x)) returns %x, expected %x\n",
                wine_dbgstr_longlong(num), seed_bak, result, expected);
        ok(seed == expected,
                "test: 0x%s RtlUniform(&seed (seed == %x)) sets seed to %x, expected %x\n",
                wine_dbgstr_longlong(num), seed_bak, result, expected);
    } /* for */
/*
 * Further investigation shows: In the different regions the highest bit
 * is set or cleared when even or odd seeds need an increment by 1.
 * This leads to a simplified algorithm:
 *
 * seed = seed * 0xffffffed + 0x7fffffc3;
 * if (seed == 0xffffffff || seed == 0x7ffffffe) {
 *     seed = (seed + 2) & MAXLONG;
 * } else if (seed == 0x7fffffff) {
 *     seed = 0;
 * } else if ((seed & 0x80000000) == 0) {
 *     seed = seed + (~seed & 1);
 * } else {
 *     seed = (seed + (seed & 1)) & MAXLONG;
 * }
 *
 * This is also the algorithm used for RtlUniform of wine (see dlls/ntdll/rtl.c).
 *
 * Now comes the funny part:
 * It took me one weekend, to find the complicated algorithm and one day more,
 * to find the simplified algorithm. Several weeks later I found out: The value
 * MAXLONG (=0x7fffffff) is never returned, neither with the native function
 * nor with the simplified algorithm. In reality the native function and our
 * function return a random number distributed over [0..MAXLONG-1]. Note
 * that this is different from what native documentation states [0..MAXLONG].
 * Expressed with D.H. Lehmer's 1948 algorithm it looks like:
 *
 * seed = (seed * const_1 + const_2) % MAXLONG;
 *
 * Further investigations show that the real algorithm is:
 *
 * seed = (seed * 0x7fffffed + 0x7fffffc3) % MAXLONG;
 *
 * This is checked with the test below:
 */
    seed = 0;
    for (num = 0; num <= 100000; num++) {
	expected = (seed * 0x7fffffed + 0x7fffffc3) % 0x7fffffff;
        seed_bak = seed;
        result = pRtlUniform(&seed);
        ok(result == expected,
                "test: 0x%s RtlUniform(&seed (seed == %x)) returns %x, expected %x\n",
                wine_dbgstr_longlong(num), seed_bak, result, expected);
        ok(seed == expected,
                "test: 0x%s RtlUniform(&seed (seed == %x)) sets seed to %x, expected %x\n",
                wine_dbgstr_longlong(num), seed_bak, result, expected);
    } /* for */
/*
 * More tests show that RtlUniform does not return 0x7ffffffd for seed values
 * in the range [0..MAXLONG-1]. Additionally 2 is returned twice. This shows
 * that there is more than one cycle of generated randon numbers ...
 */
}