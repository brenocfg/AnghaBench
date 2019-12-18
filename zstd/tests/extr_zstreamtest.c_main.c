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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int e_api ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int FUZ_COMPRESSIBILITY_DEFAULT ; 
 int FUZ_usage (char const* const) ; 
 int SEC_TO_MICRO ; 
 int XXH32 (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ZSTD_VERSION_STRING ; 
#define  advanced_api 130 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int basicUnitTests (int /*<<< orphan*/ ,double) ; 
 int fuzzerTests (int,int,int,double,int) ; 
 int fuzzerTests_MT (int,int,int,double,int) ; 
 int fuzzerTests_newAPI (int,int,int,double,int) ; 
 int g_clockTime ; 
 int /*<<< orphan*/  g_displayLevel ; 
 int getchar () ; 
#define  mt_api 129 
 int nbTestsDefault ; 
#define  simple_api 128 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, const char** argv)
{
    U32 seed = 0;
    int seedset = 0;
    int nbTests = nbTestsDefault;
    int testNb = 0;
    int proba = FUZ_COMPRESSIBILITY_DEFAULT;
    int result = 0;
    int mainPause = 0;
    int bigTests = (sizeof(size_t) == 8);
    e_api selected_api = simple_api;
    const char* const programName = argv[0];
    int argNb;

    /* Check command line */
    for(argNb=1; argNb<argc; argNb++) {
        const char* argument = argv[argNb];
        assert(argument != NULL);

        /* Parsing commands. Aggregated commands are allowed */
        if (argument[0]=='-') {

            if (!strcmp(argument, "--mt")) { selected_api=mt_api; testNb += !testNb; continue; }
            if (!strcmp(argument, "--newapi")) { selected_api=advanced_api; testNb += !testNb; continue; }
            if (!strcmp(argument, "--no-big-tests")) { bigTests=0; continue; }

            argument++;
            while (*argument!=0) {
                switch(*argument)
                {
                case 'h':
                    return FUZ_usage(programName);

                case 'v':
                    argument++;
                    g_displayLevel++;
                    break;

                case 'q':
                    argument++;
                    g_displayLevel--;
                    break;

                case 'p': /* pause at the end */
                    argument++;
                    mainPause = 1;
                    break;

                case 'i':   /* limit tests by nb of iterations (default) */
                    argument++;
                    nbTests=0; g_clockTime=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        nbTests *= 10;
                        nbTests += *argument - '0';
                        argument++;
                    }
                    break;

                case 'T':   /* limit tests by time */
                    argument++;
                    nbTests=0; g_clockTime=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        g_clockTime *= 10;
                        g_clockTime += *argument - '0';
                        argument++;
                    }
                    if (*argument=='m') {    /* -T1m == -T60 */
                        g_clockTime *=60, argument++;
                        if (*argument=='n') argument++; /* -T1mn == -T60 */
                    } else if (*argument=='s') argument++; /* -T10s == -T10 */
                    g_clockTime *= SEC_TO_MICRO;
                    break;

                case 's':   /* manually select seed */
                    argument++;
                    seedset=1;
                    seed=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        seed *= 10;
                        seed += *argument - '0';
                        argument++;
                    }
                    break;

                case 't':   /* select starting test number */
                    argument++;
                    testNb=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        testNb *= 10;
                        testNb += *argument - '0';
                        argument++;
                    }
                    break;

                case 'P':   /* compressibility % */
                    argument++;
                    proba=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        proba *= 10;
                        proba += *argument - '0';
                        argument++;
                    }
                    if (proba<0) proba=0;
                    if (proba>100) proba=100;
                    break;

                default:
                    return FUZ_usage(programName);
                }
    }   }   }   /* for(argNb=1; argNb<argc; argNb++) */

    /* Get Seed */
    DISPLAY("Starting zstream tester (%i-bits, %s)\n", (int)(sizeof(size_t)*8), ZSTD_VERSION_STRING);

    if (!seedset) {
        time_t const t = time(NULL);
        U32 const h = XXH32(&t, sizeof(t), 1);
        seed = h % 10000;
    }

    DISPLAY("Seed = %u\n", (unsigned)seed);
    if (proba!=FUZ_COMPRESSIBILITY_DEFAULT) DISPLAY("Compressibility : %i%%\n", proba);

    if (nbTests<=0) nbTests=1;

    if (testNb==0) {
        result = basicUnitTests(0, ((double)proba) / 100);  /* constant seed for predictability */
    }

    if (!result) {
        switch(selected_api)
        {
        case simple_api :
            result = fuzzerTests(seed, nbTests, testNb, ((double)proba) / 100, bigTests);
            break;
        case mt_api :
            result = fuzzerTests_MT(seed, nbTests, testNb, ((double)proba) / 100, bigTests);
            break;
        case advanced_api :
            result = fuzzerTests_newAPI(seed, nbTests, testNb, ((double)proba) / 100, bigTests);
            break;
        default :
            assert(0);   /* impossible */
        }
    }

    if (mainPause) {
        int unused;
        DISPLAY("Press Enter \n");
        unused = getchar();
        (void)unused;
    }
    return result;
}