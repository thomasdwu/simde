/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2020      Evan Nemerson <evan@nemerson.com>
 *   2020      Himanshi Mathur <himanshi18037@iiitd.ac.in>
 */

#define SIMDE_TEST_X86_AVX512_INSN cmp

#include <test/x86/avx512/test-avx512.h>
#include <simde/x86/avx512/set.h>
#include <simde/x86/avx512/cmp.h>
#include <simde/x86/avx512/mov.h>
#include <simde/x86/avx512/set1.h>

#if !defined(SIMDE_NATIVE_ALIASES_TESTING) && !defined(SIMDE_FAST_MATH)
// TODO: SIMDE_FAST_MATH can be tested, but only for tests cases with no
// NAN in the parameters or results

static int
test_simde_mm512_cmp_ps_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  static const struct {
    const simde_float32 a[16];
    const simde_float32 b[16];
    const simde__mmask16 r;
  } test_vec[] = {
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -492.75), SIMDE_FLOAT32_C(  -438.29),
        SIMDE_FLOAT32_C(  -582.04), SIMDE_FLOAT32_C(   854.65), SIMDE_FLOAT32_C(   155.54), SIMDE_FLOAT32_C(   896.11),
        SIMDE_FLOAT32_C(  -984.17), SIMDE_FLOAT32_C(  -151.52), SIMDE_FLOAT32_C(  -333.42), SIMDE_FLOAT32_C(  -650.38),
        SIMDE_FLOAT32_C(   -87.56), SIMDE_FLOAT32_C(  -583.12), SIMDE_FLOAT32_C(  -508.18), SIMDE_FLOAT32_C(    10.09) },
      { SIMDE_FLOAT32_C(  -433.49),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   431.70),
        SIMDE_FLOAT32_C(  -582.04), SIMDE_FLOAT32_C(  -629.54), SIMDE_FLOAT32_C(  -116.35), SIMDE_FLOAT32_C(  -824.24),
        SIMDE_FLOAT32_C(  -984.17), SIMDE_FLOAT32_C(  -139.40), SIMDE_FLOAT32_C(  -333.42), SIMDE_FLOAT32_C(   866.10),
        SIMDE_FLOAT32_C(   -87.56), SIMDE_FLOAT32_C(  -583.12), SIMDE_FLOAT32_C(  -722.62), SIMDE_FLOAT32_C(    10.09) },
      UINT16_C(46352) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -360.72), SIMDE_FLOAT32_C(   883.16),
        SIMDE_FLOAT32_C(  -175.11), SIMDE_FLOAT32_C(  -344.89), SIMDE_FLOAT32_C(  -268.35), SIMDE_FLOAT32_C(   491.46),
        SIMDE_FLOAT32_C(     4.73), SIMDE_FLOAT32_C(   644.09), SIMDE_FLOAT32_C(   908.34), SIMDE_FLOAT32_C(   496.55),
        SIMDE_FLOAT32_C(  -345.82), SIMDE_FLOAT32_C(  -412.75), SIMDE_FLOAT32_C(   601.72), SIMDE_FLOAT32_C(  -536.93) },
      { SIMDE_FLOAT32_C(  -981.05),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -97.40),
        SIMDE_FLOAT32_C(  -175.11), SIMDE_FLOAT32_C(  -920.53), SIMDE_FLOAT32_C(  -268.35), SIMDE_FLOAT32_C(   491.46),
        SIMDE_FLOAT32_C(     4.73), SIMDE_FLOAT32_C(   644.09), SIMDE_FLOAT32_C(   908.34), SIMDE_FLOAT32_C(  -777.04),
        SIMDE_FLOAT32_C(   528.52), SIMDE_FLOAT32_C(   439.99), SIMDE_FLOAT32_C(   601.72), SIMDE_FLOAT32_C(  -536.93) },
      UINT16_C(12288) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -698.03), SIMDE_FLOAT32_C(  -129.05),
        SIMDE_FLOAT32_C(  -314.88), SIMDE_FLOAT32_C(   306.70), SIMDE_FLOAT32_C(  -484.96), SIMDE_FLOAT32_C(  -406.54),
        SIMDE_FLOAT32_C(  -196.75), SIMDE_FLOAT32_C(   169.22), SIMDE_FLOAT32_C(   180.71), SIMDE_FLOAT32_C(  -595.03),
        SIMDE_FLOAT32_C(   632.29), SIMDE_FLOAT32_C(   199.66), SIMDE_FLOAT32_C(   321.33), SIMDE_FLOAT32_C(  -534.18) },
      { SIMDE_FLOAT32_C(  -860.70),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -129.05),
        SIMDE_FLOAT32_C(  -314.88), SIMDE_FLOAT32_C(   306.70), SIMDE_FLOAT32_C(   228.07), SIMDE_FLOAT32_C(    91.07),
        SIMDE_FLOAT32_C(  -286.18), SIMDE_FLOAT32_C(   169.22), SIMDE_FLOAT32_C(   180.71), SIMDE_FLOAT32_C(  -595.03),
        SIMDE_FLOAT32_C(    12.74), SIMDE_FLOAT32_C(   199.66), SIMDE_FLOAT32_C(   321.33), SIMDE_FLOAT32_C(   152.04) },
      UINT16_C(61176) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -23.06), SIMDE_FLOAT32_C(  -461.97),
        SIMDE_FLOAT32_C(   372.08), SIMDE_FLOAT32_C(   780.19), SIMDE_FLOAT32_C(   707.25), SIMDE_FLOAT32_C(  -447.21),
        SIMDE_FLOAT32_C(  -814.84), SIMDE_FLOAT32_C(   339.53), SIMDE_FLOAT32_C(   752.45), SIMDE_FLOAT32_C(   506.49),
        SIMDE_FLOAT32_C(   805.35), SIMDE_FLOAT32_C(   854.71), SIMDE_FLOAT32_C(   919.95), SIMDE_FLOAT32_C(  -649.37) },
      { SIMDE_FLOAT32_C(  -977.01),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -461.97),
        SIMDE_FLOAT32_C(   372.08), SIMDE_FLOAT32_C(   780.19), SIMDE_FLOAT32_C(   704.84), SIMDE_FLOAT32_C(   703.98),
        SIMDE_FLOAT32_C(   276.72), SIMDE_FLOAT32_C(   339.53), SIMDE_FLOAT32_C(   752.45), SIMDE_FLOAT32_C(   506.49),
        SIMDE_FLOAT32_C(   869.62), SIMDE_FLOAT32_C(  -302.69), SIMDE_FLOAT32_C(   919.95), SIMDE_FLOAT32_C(   892.61) },
      UINT16_C(    7) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    72.37), SIMDE_FLOAT32_C(  -862.11),
        SIMDE_FLOAT32_C(   400.81), SIMDE_FLOAT32_C(   257.54), SIMDE_FLOAT32_C(   477.42), SIMDE_FLOAT32_C(   153.26),
        SIMDE_FLOAT32_C(  -235.97), SIMDE_FLOAT32_C(   282.77), SIMDE_FLOAT32_C(     7.97), SIMDE_FLOAT32_C(  -316.02),
        SIMDE_FLOAT32_C(   633.40), SIMDE_FLOAT32_C(  -271.85), SIMDE_FLOAT32_C(  -234.18), SIMDE_FLOAT32_C(  -525.10) },
      { SIMDE_FLOAT32_C(  -569.36),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -862.11),
        SIMDE_FLOAT32_C(   642.71), SIMDE_FLOAT32_C(   257.54), SIMDE_FLOAT32_C(  -901.18), SIMDE_FLOAT32_C(  -753.48),
        SIMDE_FLOAT32_C(   951.92), SIMDE_FLOAT32_C(   968.44), SIMDE_FLOAT32_C(   -56.17), SIMDE_FLOAT32_C(  -316.02),
        SIMDE_FLOAT32_C(   633.40), SIMDE_FLOAT32_C(  -580.24), SIMDE_FLOAT32_C(   559.34), SIMDE_FLOAT32_C(  -525.10) },
      UINT16_C(26583) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   889.25), SIMDE_FLOAT32_C(   907.00),
        SIMDE_FLOAT32_C(   821.84), SIMDE_FLOAT32_C(  -346.72), SIMDE_FLOAT32_C(   189.77), SIMDE_FLOAT32_C(  -170.19),
        SIMDE_FLOAT32_C(   337.26), SIMDE_FLOAT32_C(  -176.83), SIMDE_FLOAT32_C(   557.96), SIMDE_FLOAT32_C(  -896.92),
        SIMDE_FLOAT32_C(   298.07), SIMDE_FLOAT32_C(   234.35), SIMDE_FLOAT32_C(  -958.19), SIMDE_FLOAT32_C(   328.27) },
      { SIMDE_FLOAT32_C(  -570.42),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -285.59),
        SIMDE_FLOAT32_C(   931.04), SIMDE_FLOAT32_C(  -412.88), SIMDE_FLOAT32_C(  -317.16), SIMDE_FLOAT32_C(  -170.19),
        SIMDE_FLOAT32_C(   337.26), SIMDE_FLOAT32_C(  -456.11), SIMDE_FLOAT32_C(   557.96), SIMDE_FLOAT32_C(  -586.38),
        SIMDE_FLOAT32_C(   298.07), SIMDE_FLOAT32_C(   234.35), SIMDE_FLOAT32_C(  -958.19), SIMDE_FLOAT32_C(   328.27) },
      UINT16_C(63471) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   587.85), SIMDE_FLOAT32_C(  -638.08),
        SIMDE_FLOAT32_C(   882.64), SIMDE_FLOAT32_C(   -74.89), SIMDE_FLOAT32_C(   185.09), SIMDE_FLOAT32_C(   440.60),
        SIMDE_FLOAT32_C(    28.19), SIMDE_FLOAT32_C(  -516.84), SIMDE_FLOAT32_C(  -325.05), SIMDE_FLOAT32_C(    69.99),
        SIMDE_FLOAT32_C(   811.43), SIMDE_FLOAT32_C(   290.54), SIMDE_FLOAT32_C(  -245.49), SIMDE_FLOAT32_C(  -553.37) },
      { SIMDE_FLOAT32_C(   172.16),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -312.22),
        SIMDE_FLOAT32_C(   882.64), SIMDE_FLOAT32_C(   -74.89), SIMDE_FLOAT32_C(   231.67), SIMDE_FLOAT32_C(   440.60),
        SIMDE_FLOAT32_C(  -698.35), SIMDE_FLOAT32_C(  -932.75), SIMDE_FLOAT32_C(  -325.05), SIMDE_FLOAT32_C(   346.97),
        SIMDE_FLOAT32_C(   332.41), SIMDE_FLOAT32_C(  -351.53), SIMDE_FLOAT32_C(  -245.49), SIMDE_FLOAT32_C(  -495.43) },
      UINT16_C(13063) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -205.49), SIMDE_FLOAT32_C(  -948.42),
        SIMDE_FLOAT32_C(    24.54), SIMDE_FLOAT32_C(   822.70), SIMDE_FLOAT32_C(  -465.26), SIMDE_FLOAT32_C(   699.49),
        SIMDE_FLOAT32_C(  -107.31), SIMDE_FLOAT32_C(  -653.83), SIMDE_FLOAT32_C(    -9.98), SIMDE_FLOAT32_C(   647.21),
        SIMDE_FLOAT32_C(  -207.19), SIMDE_FLOAT32_C(    -5.03), SIMDE_FLOAT32_C(  -667.24), SIMDE_FLOAT32_C(   826.56) },
      { SIMDE_FLOAT32_C(  -133.51),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -85.57),
        SIMDE_FLOAT32_C(    24.54), SIMDE_FLOAT32_C(  -983.76), SIMDE_FLOAT32_C(   -18.32), SIMDE_FLOAT32_C(   699.49),
        SIMDE_FLOAT32_C(   363.22), SIMDE_FLOAT32_C(  -653.83), SIMDE_FLOAT32_C(  -185.79), SIMDE_FLOAT32_C(   647.21),
        SIMDE_FLOAT32_C(  -181.34), SIMDE_FLOAT32_C(  -484.49), SIMDE_FLOAT32_C(   514.17), SIMDE_FLOAT32_C(   685.14) },
      UINT16_C(65528) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -868.62), SIMDE_FLOAT32_C(  -728.54),
        SIMDE_FLOAT32_C(  -176.52), SIMDE_FLOAT32_C(    24.08), SIMDE_FLOAT32_C(  -382.37), SIMDE_FLOAT32_C(   813.50),
        SIMDE_FLOAT32_C(  -328.72), SIMDE_FLOAT32_C(   410.44), SIMDE_FLOAT32_C(  -191.53), SIMDE_FLOAT32_C(     4.04),
        SIMDE_FLOAT32_C(   237.00), SIMDE_FLOAT32_C(  -508.78), SIMDE_FLOAT32_C(  -102.77), SIMDE_FLOAT32_C(   -48.41) },
      { SIMDE_FLOAT32_C(   736.73),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -612.67),
        SIMDE_FLOAT32_C(  -176.52), SIMDE_FLOAT32_C(  -668.95), SIMDE_FLOAT32_C(  -382.37), SIMDE_FLOAT32_C(   813.50),
        SIMDE_FLOAT32_C(   975.82), SIMDE_FLOAT32_C(   410.44), SIMDE_FLOAT32_C(  -191.53), SIMDE_FLOAT32_C(     4.04),
        SIMDE_FLOAT32_C(   237.00), SIMDE_FLOAT32_C(  -508.78), SIMDE_FLOAT32_C(  -102.77), SIMDE_FLOAT32_C(   -48.41) },
      UINT16_C(65239) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -45.88), SIMDE_FLOAT32_C(   831.04),
        SIMDE_FLOAT32_C(     1.37), SIMDE_FLOAT32_C(   625.40), SIMDE_FLOAT32_C(   241.48), SIMDE_FLOAT32_C(   809.84),
        SIMDE_FLOAT32_C(  -370.55), SIMDE_FLOAT32_C(  -521.52), SIMDE_FLOAT32_C(  -698.94), SIMDE_FLOAT32_C(   526.68),
        SIMDE_FLOAT32_C(   430.07), SIMDE_FLOAT32_C(   706.71), SIMDE_FLOAT32_C(   172.17), SIMDE_FLOAT32_C(  -602.09) },
      { SIMDE_FLOAT32_C(   213.41),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -204.55),
        SIMDE_FLOAT32_C(     1.37), SIMDE_FLOAT32_C(  -295.23), SIMDE_FLOAT32_C(   241.48), SIMDE_FLOAT32_C(  -250.22),
        SIMDE_FLOAT32_C(  -805.24), SIMDE_FLOAT32_C(   520.74), SIMDE_FLOAT32_C(  -698.94), SIMDE_FLOAT32_C(   993.42),
        SIMDE_FLOAT32_C(  -537.32), SIMDE_FLOAT32_C(  -645.42), SIMDE_FLOAT32_C(   172.17), SIMDE_FLOAT32_C(  -602.09) },
      UINT16_C( 2567) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -497.00), SIMDE_FLOAT32_C(  -251.40),
        SIMDE_FLOAT32_C(  -646.33), SIMDE_FLOAT32_C(   132.44), SIMDE_FLOAT32_C(   227.08), SIMDE_FLOAT32_C(  -345.27),
        SIMDE_FLOAT32_C(  -340.88), SIMDE_FLOAT32_C(  -342.84), SIMDE_FLOAT32_C(  -638.56), SIMDE_FLOAT32_C(   831.28),
        SIMDE_FLOAT32_C(    55.07), SIMDE_FLOAT32_C(  -544.52), SIMDE_FLOAT32_C(  -185.32), SIMDE_FLOAT32_C(   784.02) },
      { SIMDE_FLOAT32_C(   250.93),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -251.40),
        SIMDE_FLOAT32_C(  -646.33), SIMDE_FLOAT32_C(  -316.44), SIMDE_FLOAT32_C(    87.19), SIMDE_FLOAT32_C(  -345.27),
        SIMDE_FLOAT32_C(  -323.02), SIMDE_FLOAT32_C(   549.87), SIMDE_FLOAT32_C(  -638.56), SIMDE_FLOAT32_C(   831.28),
        SIMDE_FLOAT32_C(    55.07), SIMDE_FLOAT32_C(  -544.52), SIMDE_FLOAT32_C(  -185.32), SIMDE_FLOAT32_C(   784.02) },
      UINT16_C(65439) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   113.48), SIMDE_FLOAT32_C(  -291.23),
        SIMDE_FLOAT32_C(  -387.26), SIMDE_FLOAT32_C(   772.60), SIMDE_FLOAT32_C(   365.92), SIMDE_FLOAT32_C(   -25.82),
        SIMDE_FLOAT32_C(   603.89), SIMDE_FLOAT32_C(  -579.01), SIMDE_FLOAT32_C(   429.66), SIMDE_FLOAT32_C(  -581.44),
        SIMDE_FLOAT32_C(  -794.99), SIMDE_FLOAT32_C(  -319.41), SIMDE_FLOAT32_C(  -157.93), SIMDE_FLOAT32_C(  -306.19) },
      { SIMDE_FLOAT32_C(   481.68),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -291.23),
        SIMDE_FLOAT32_C(  -387.26), SIMDE_FLOAT32_C(  -945.65), SIMDE_FLOAT32_C(  -115.91), SIMDE_FLOAT32_C(   -25.82),
        SIMDE_FLOAT32_C(  -345.20), SIMDE_FLOAT32_C(  -579.01), SIMDE_FLOAT32_C(   757.39), SIMDE_FLOAT32_C(  -867.15),
        SIMDE_FLOAT32_C(  -156.87), SIMDE_FLOAT32_C(   361.73), SIMDE_FLOAT32_C(  -886.11), SIMDE_FLOAT32_C(  -306.19) },
      UINT16_C(    0) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    -0.03), SIMDE_FLOAT32_C(  -600.50),
        SIMDE_FLOAT32_C(   -93.35), SIMDE_FLOAT32_C(  -396.14), SIMDE_FLOAT32_C(  -179.51), SIMDE_FLOAT32_C(  -663.69),
        SIMDE_FLOAT32_C(    22.42), SIMDE_FLOAT32_C(    25.50), SIMDE_FLOAT32_C(    16.90), SIMDE_FLOAT32_C(   864.49),
        SIMDE_FLOAT32_C(   719.32), SIMDE_FLOAT32_C(   263.94), SIMDE_FLOAT32_C(   879.85), SIMDE_FLOAT32_C(    96.69) },
      { SIMDE_FLOAT32_C(    33.57),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -600.50),
        SIMDE_FLOAT32_C(   755.57), SIMDE_FLOAT32_C(   805.84), SIMDE_FLOAT32_C(   592.31), SIMDE_FLOAT32_C(  -663.69),
        SIMDE_FLOAT32_C(   938.69), SIMDE_FLOAT32_C(  -564.57), SIMDE_FLOAT32_C(    16.90), SIMDE_FLOAT32_C(  -947.42),
        SIMDE_FLOAT32_C(  -239.76), SIMDE_FLOAT32_C(   263.94), SIMDE_FLOAT32_C(   279.95), SIMDE_FLOAT32_C(   793.82) },
      UINT16_C(56176) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -116.23), SIMDE_FLOAT32_C(    13.81),
        SIMDE_FLOAT32_C(   369.86), SIMDE_FLOAT32_C(   906.19), SIMDE_FLOAT32_C(  -960.69), SIMDE_FLOAT32_C(  -613.24),
        SIMDE_FLOAT32_C(   770.68), SIMDE_FLOAT32_C(   758.63), SIMDE_FLOAT32_C(   650.70), SIMDE_FLOAT32_C(   650.54),
        SIMDE_FLOAT32_C(  -144.69), SIMDE_FLOAT32_C(  -751.14), SIMDE_FLOAT32_C(  -290.78), SIMDE_FLOAT32_C(  -993.65) },
      { SIMDE_FLOAT32_C(  -806.68),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   323.43),
        SIMDE_FLOAT32_C(   369.86), SIMDE_FLOAT32_C(   750.88), SIMDE_FLOAT32_C(   758.87), SIMDE_FLOAT32_C(  -613.24),
        SIMDE_FLOAT32_C(   803.46), SIMDE_FLOAT32_C(   758.63), SIMDE_FLOAT32_C(    46.88), SIMDE_FLOAT32_C(    83.41),
        SIMDE_FLOAT32_C(  -687.07), SIMDE_FLOAT32_C(   173.78), SIMDE_FLOAT32_C(   363.33), SIMDE_FLOAT32_C(  -493.76) },
      UINT16_C( 7856) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -846.71), SIMDE_FLOAT32_C(   559.36),
        SIMDE_FLOAT32_C(   963.95), SIMDE_FLOAT32_C(   923.98), SIMDE_FLOAT32_C(   317.98), SIMDE_FLOAT32_C(   614.64),
        SIMDE_FLOAT32_C(   574.51), SIMDE_FLOAT32_C(  -826.70), SIMDE_FLOAT32_C(   863.51), SIMDE_FLOAT32_C(  -716.26),
        SIMDE_FLOAT32_C(  -820.36), SIMDE_FLOAT32_C(   594.63), SIMDE_FLOAT32_C(  -251.47), SIMDE_FLOAT32_C(   991.84) },
      { SIMDE_FLOAT32_C(   -81.93),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -323.06),
        SIMDE_FLOAT32_C(   578.75), SIMDE_FLOAT32_C(   923.98), SIMDE_FLOAT32_C(   196.05), SIMDE_FLOAT32_C(  -374.36),
        SIMDE_FLOAT32_C(  -370.41), SIMDE_FLOAT32_C(   508.97), SIMDE_FLOAT32_C(   863.51), SIMDE_FLOAT32_C(   992.91),
        SIMDE_FLOAT32_C(  -820.36), SIMDE_FLOAT32_C(   594.63), SIMDE_FLOAT32_C(  -251.47), SIMDE_FLOAT32_C(   991.84) },
      UINT16_C(  472) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -682.72), SIMDE_FLOAT32_C(  -587.39),
        SIMDE_FLOAT32_C(   162.51), SIMDE_FLOAT32_C(   891.79), SIMDE_FLOAT32_C(  -414.09), SIMDE_FLOAT32_C(    26.02),
        SIMDE_FLOAT32_C(  -824.47), SIMDE_FLOAT32_C(  -234.45), SIMDE_FLOAT32_C(  -379.34), SIMDE_FLOAT32_C(   -75.94),
        SIMDE_FLOAT32_C(  -242.61), SIMDE_FLOAT32_C(   538.73), SIMDE_FLOAT32_C(   650.36), SIMDE_FLOAT32_C(  -499.89) },
      { SIMDE_FLOAT32_C(    94.63),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   411.71),
        SIMDE_FLOAT32_C(   854.75), SIMDE_FLOAT32_C(  -324.13), SIMDE_FLOAT32_C(  -414.09), SIMDE_FLOAT32_C(   654.16),
        SIMDE_FLOAT32_C(  -331.22), SIMDE_FLOAT32_C(   -64.10), SIMDE_FLOAT32_C(  -379.34), SIMDE_FLOAT32_C(   -91.21),
        SIMDE_FLOAT32_C(  -528.83), SIMDE_FLOAT32_C(   538.73), SIMDE_FLOAT32_C(   302.10), SIMDE_FLOAT32_C(   565.79) },
           UINT16_MAX },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   511.17), SIMDE_FLOAT32_C(  -435.69),
        SIMDE_FLOAT32_C(   -18.77), SIMDE_FLOAT32_C(   686.70), SIMDE_FLOAT32_C(   329.86), SIMDE_FLOAT32_C(   601.89),
        SIMDE_FLOAT32_C(  -389.24), SIMDE_FLOAT32_C(  -912.75), SIMDE_FLOAT32_C(   140.62), SIMDE_FLOAT32_C(  -738.88),
        SIMDE_FLOAT32_C(  -412.65), SIMDE_FLOAT32_C(   356.28), SIMDE_FLOAT32_C(   490.24), SIMDE_FLOAT32_C(  -366.36) },
      { SIMDE_FLOAT32_C(   978.40),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -435.69),
        SIMDE_FLOAT32_C(    -0.85), SIMDE_FLOAT32_C(   686.70), SIMDE_FLOAT32_C(  -375.43), SIMDE_FLOAT32_C(  -339.95),
        SIMDE_FLOAT32_C(  -389.24), SIMDE_FLOAT32_C(  -912.75), SIMDE_FLOAT32_C(   904.88), SIMDE_FLOAT32_C(  -738.88),
        SIMDE_FLOAT32_C(  -338.47), SIMDE_FLOAT32_C(   356.28), SIMDE_FLOAT32_C(   490.24), SIMDE_FLOAT32_C(  -366.36) },
      UINT16_C(60200) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(     6.43), SIMDE_FLOAT32_C(  -465.89),
        SIMDE_FLOAT32_C(   235.91), SIMDE_FLOAT32_C(   617.19), SIMDE_FLOAT32_C(  -378.65), SIMDE_FLOAT32_C(  -623.48),
        SIMDE_FLOAT32_C(   878.32), SIMDE_FLOAT32_C(   208.71), SIMDE_FLOAT32_C(   732.80), SIMDE_FLOAT32_C(   368.55),
        SIMDE_FLOAT32_C(   842.35), SIMDE_FLOAT32_C(  -499.21), SIMDE_FLOAT32_C(  -286.46), SIMDE_FLOAT32_C(   151.86) },
      { SIMDE_FLOAT32_C(  -810.55),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -185.98),
        SIMDE_FLOAT32_C(   235.91), SIMDE_FLOAT32_C(   617.19), SIMDE_FLOAT32_C(   909.76), SIMDE_FLOAT32_C(  -623.48),
        SIMDE_FLOAT32_C(  -793.58), SIMDE_FLOAT32_C(   208.71), SIMDE_FLOAT32_C(   732.80), SIMDE_FLOAT32_C(  -985.03),
        SIMDE_FLOAT32_C(   842.35), SIMDE_FLOAT32_C(  -499.21), SIMDE_FLOAT32_C(  -286.46), SIMDE_FLOAT32_C(  -584.53) },
      UINT16_C(   72) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   958.32), SIMDE_FLOAT32_C(   570.93),
        SIMDE_FLOAT32_C(  -125.57), SIMDE_FLOAT32_C(   836.63), SIMDE_FLOAT32_C(  -220.36), SIMDE_FLOAT32_C(  -392.77),
        SIMDE_FLOAT32_C(   205.19), SIMDE_FLOAT32_C(  -378.01), SIMDE_FLOAT32_C(   108.02), SIMDE_FLOAT32_C(   918.73),
        SIMDE_FLOAT32_C(   773.85), SIMDE_FLOAT32_C(   297.47), SIMDE_FLOAT32_C(   631.42), SIMDE_FLOAT32_C(   -96.00) },
      { SIMDE_FLOAT32_C(  -888.51),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   570.93),
        SIMDE_FLOAT32_C(  -125.57), SIMDE_FLOAT32_C(   127.66), SIMDE_FLOAT32_C(  -407.46), SIMDE_FLOAT32_C(  -392.77),
        SIMDE_FLOAT32_C(   205.19), SIMDE_FLOAT32_C(  -378.01), SIMDE_FLOAT32_C(  -115.05), SIMDE_FLOAT32_C(   918.73),
        SIMDE_FLOAT32_C(   773.85), SIMDE_FLOAT32_C(   297.47), SIMDE_FLOAT32_C(   631.42), SIMDE_FLOAT32_C(   168.81) },
      UINT16_C(64408) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -386.59), SIMDE_FLOAT32_C(   519.38),
        SIMDE_FLOAT32_C(  -873.48), SIMDE_FLOAT32_C(   818.60), SIMDE_FLOAT32_C(  -858.63), SIMDE_FLOAT32_C(   234.54),
        SIMDE_FLOAT32_C(   737.33), SIMDE_FLOAT32_C(   915.22), SIMDE_FLOAT32_C(  -467.99), SIMDE_FLOAT32_C(   368.74),
        SIMDE_FLOAT32_C(  -180.78), SIMDE_FLOAT32_C(  -356.50), SIMDE_FLOAT32_C(   372.90), SIMDE_FLOAT32_C(   740.45) },
      { SIMDE_FLOAT32_C(  -335.25),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   257.29),
        SIMDE_FLOAT32_C(  -873.48), SIMDE_FLOAT32_C(   818.60), SIMDE_FLOAT32_C(  -858.63), SIMDE_FLOAT32_C(   796.60),
        SIMDE_FLOAT32_C(  -511.93), SIMDE_FLOAT32_C(   280.28), SIMDE_FLOAT32_C(   943.55), SIMDE_FLOAT32_C(   368.74),
        SIMDE_FLOAT32_C(  -180.78), SIMDE_FLOAT32_C(  -356.50), SIMDE_FLOAT32_C(   372.90), SIMDE_FLOAT32_C(   188.83) },
      UINT16_C(    7) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -484.68), SIMDE_FLOAT32_C(  -150.43),
        SIMDE_FLOAT32_C(   468.75), SIMDE_FLOAT32_C(  -747.35), SIMDE_FLOAT32_C(  -235.22), SIMDE_FLOAT32_C(  -999.25),
        SIMDE_FLOAT32_C(   621.39), SIMDE_FLOAT32_C(   584.00), SIMDE_FLOAT32_C(  -355.74), SIMDE_FLOAT32_C(    -5.71),
        SIMDE_FLOAT32_C(   324.45), SIMDE_FLOAT32_C(   309.01), SIMDE_FLOAT32_C(  -351.04), SIMDE_FLOAT32_C(  -807.44) },
      { SIMDE_FLOAT32_C(  -291.80),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -150.43),
        SIMDE_FLOAT32_C(   357.20), SIMDE_FLOAT32_C(  -747.35), SIMDE_FLOAT32_C(  -235.22), SIMDE_FLOAT32_C(   300.75),
        SIMDE_FLOAT32_C(   997.90), SIMDE_FLOAT32_C(   356.72), SIMDE_FLOAT32_C(   889.15), SIMDE_FLOAT32_C(    -5.71),
        SIMDE_FLOAT32_C(   324.45), SIMDE_FLOAT32_C(   996.84), SIMDE_FLOAT32_C(  -351.04), SIMDE_FLOAT32_C(  -807.44) },
      UINT16_C(10135) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   545.90), SIMDE_FLOAT32_C(  -131.90),
        SIMDE_FLOAT32_C(   700.55), SIMDE_FLOAT32_C(   167.29), SIMDE_FLOAT32_C(  -547.90), SIMDE_FLOAT32_C(  -655.19),
        SIMDE_FLOAT32_C(  -838.42), SIMDE_FLOAT32_C(   776.56), SIMDE_FLOAT32_C(   653.81), SIMDE_FLOAT32_C(  -189.46),
        SIMDE_FLOAT32_C(   969.12), SIMDE_FLOAT32_C(  -779.89), SIMDE_FLOAT32_C(  -628.85), SIMDE_FLOAT32_C(  -827.58) },
      { SIMDE_FLOAT32_C(  -896.68),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -131.90),
        SIMDE_FLOAT32_C(    29.10), SIMDE_FLOAT32_C(   167.29), SIMDE_FLOAT32_C(  -547.90), SIMDE_FLOAT32_C(   -81.75),
        SIMDE_FLOAT32_C(  -838.42), SIMDE_FLOAT32_C(  -342.64), SIMDE_FLOAT32_C(   -84.91), SIMDE_FLOAT32_C(  -189.46),
        SIMDE_FLOAT32_C(   969.12), SIMDE_FLOAT32_C(   146.14), SIMDE_FLOAT32_C(    14.11), SIMDE_FLOAT32_C(  -985.57) },
      UINT16_C(40831) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   727.30), SIMDE_FLOAT32_C(   334.64),
        SIMDE_FLOAT32_C(  -108.71), SIMDE_FLOAT32_C(   888.88), SIMDE_FLOAT32_C(   111.20), SIMDE_FLOAT32_C(  -454.90),
        SIMDE_FLOAT32_C(  -300.58), SIMDE_FLOAT32_C(    80.32), SIMDE_FLOAT32_C(  -234.78), SIMDE_FLOAT32_C(    70.57),
        SIMDE_FLOAT32_C(   252.74), SIMDE_FLOAT32_C(  -387.32), SIMDE_FLOAT32_C(  -201.08), SIMDE_FLOAT32_C(  -883.47) },
      { SIMDE_FLOAT32_C(   367.78),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   479.60),
        SIMDE_FLOAT32_C(  -253.73), SIMDE_FLOAT32_C(   888.88), SIMDE_FLOAT32_C(   111.20), SIMDE_FLOAT32_C(  -454.90),
        SIMDE_FLOAT32_C(  -300.58), SIMDE_FLOAT32_C(  -951.92), SIMDE_FLOAT32_C(  -192.50), SIMDE_FLOAT32_C(  -343.90),
        SIMDE_FLOAT32_C(   252.74), SIMDE_FLOAT32_C(  -387.32), SIMDE_FLOAT32_C(  -201.08), SIMDE_FLOAT32_C(  -883.47) },
      UINT16_C( 2583) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -167.70), SIMDE_FLOAT32_C(   390.88),
        SIMDE_FLOAT32_C(   636.32), SIMDE_FLOAT32_C(   531.72), SIMDE_FLOAT32_C(  -528.80), SIMDE_FLOAT32_C(  -598.46),
        SIMDE_FLOAT32_C(  -397.71), SIMDE_FLOAT32_C(   723.94), SIMDE_FLOAT32_C(    14.22), SIMDE_FLOAT32_C(   401.21),
        SIMDE_FLOAT32_C(   840.47), SIMDE_FLOAT32_C(  -618.00), SIMDE_FLOAT32_C(   229.23), SIMDE_FLOAT32_C(  -181.30) },
      { SIMDE_FLOAT32_C(   861.60),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   998.57),
        SIMDE_FLOAT32_C(   636.86), SIMDE_FLOAT32_C(   531.72), SIMDE_FLOAT32_C(  -528.80), SIMDE_FLOAT32_C(  -555.63),
        SIMDE_FLOAT32_C(  -397.71), SIMDE_FLOAT32_C(  -890.85), SIMDE_FLOAT32_C(  -902.19), SIMDE_FLOAT32_C(  -745.95),
        SIMDE_FLOAT32_C(   840.47), SIMDE_FLOAT32_C(  -702.27), SIMDE_FLOAT32_C(   229.23), SIMDE_FLOAT32_C(  -181.30) },
      UINT16_C(65528) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   561.47), SIMDE_FLOAT32_C(   195.97),
        SIMDE_FLOAT32_C(   426.80), SIMDE_FLOAT32_C(  -836.24), SIMDE_FLOAT32_C(   -80.09), SIMDE_FLOAT32_C(  -558.97),
        SIMDE_FLOAT32_C(   564.97), SIMDE_FLOAT32_C(  -239.62), SIMDE_FLOAT32_C(  -176.97), SIMDE_FLOAT32_C(  -205.81),
        SIMDE_FLOAT32_C(   579.08), SIMDE_FLOAT32_C(  -315.37), SIMDE_FLOAT32_C(  -230.31), SIMDE_FLOAT32_C(  -681.08) },
      { SIMDE_FLOAT32_C(  -316.80),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -270.16),
        SIMDE_FLOAT32_C(  -149.08), SIMDE_FLOAT32_C(  -836.24), SIMDE_FLOAT32_C(  -161.00), SIMDE_FLOAT32_C(   -51.27),
        SIMDE_FLOAT32_C(   992.75), SIMDE_FLOAT32_C(  -239.62), SIMDE_FLOAT32_C(  -176.97), SIMDE_FLOAT32_C(  -205.81),
        SIMDE_FLOAT32_C(   579.08), SIMDE_FLOAT32_C(  -364.60), SIMDE_FLOAT32_C(  -230.31), SIMDE_FLOAT32_C(  -681.08) },
      UINT16_C(56871) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -54.80), SIMDE_FLOAT32_C(  -932.26),
        SIMDE_FLOAT32_C(   528.50), SIMDE_FLOAT32_C(  -489.84), SIMDE_FLOAT32_C(  -171.88), SIMDE_FLOAT32_C(  -648.48),
        SIMDE_FLOAT32_C(   304.36), SIMDE_FLOAT32_C(  -592.80), SIMDE_FLOAT32_C(    36.16), SIMDE_FLOAT32_C(  -925.95),
        SIMDE_FLOAT32_C(  -273.88), SIMDE_FLOAT32_C(   719.36), SIMDE_FLOAT32_C(  -519.40), SIMDE_FLOAT32_C(   426.88) },
      { SIMDE_FLOAT32_C(  -550.80),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -932.26),
        SIMDE_FLOAT32_C(   528.50), SIMDE_FLOAT32_C(  -489.84), SIMDE_FLOAT32_C(   181.40), SIMDE_FLOAT32_C(   526.71),
        SIMDE_FLOAT32_C(  -651.46), SIMDE_FLOAT32_C(  -592.80), SIMDE_FLOAT32_C(  -837.89), SIMDE_FLOAT32_C(   568.50),
        SIMDE_FLOAT32_C(  -273.88), SIMDE_FLOAT32_C(   822.78), SIMDE_FLOAT32_C(  -650.06), SIMDE_FLOAT32_C(   508.17) },
      UINT16_C(43207) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   805.30), SIMDE_FLOAT32_C(  -595.98),
        SIMDE_FLOAT32_C(  -209.73), SIMDE_FLOAT32_C(   109.66), SIMDE_FLOAT32_C(  -188.79), SIMDE_FLOAT32_C(   826.42),
        SIMDE_FLOAT32_C(   183.71), SIMDE_FLOAT32_C(   537.34), SIMDE_FLOAT32_C(   545.78), SIMDE_FLOAT32_C(   664.31),
        SIMDE_FLOAT32_C(   -35.78), SIMDE_FLOAT32_C(   994.98), SIMDE_FLOAT32_C(    -4.17), SIMDE_FLOAT32_C(  -870.20) },
      { SIMDE_FLOAT32_C(   575.90),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -595.98),
        SIMDE_FLOAT32_C(  -209.73), SIMDE_FLOAT32_C(   109.66), SIMDE_FLOAT32_C(  -188.79), SIMDE_FLOAT32_C(   826.42),
        SIMDE_FLOAT32_C(   183.71), SIMDE_FLOAT32_C(   537.34), SIMDE_FLOAT32_C(   545.78), SIMDE_FLOAT32_C(   555.11),
        SIMDE_FLOAT32_C(  -258.43), SIMDE_FLOAT32_C(   697.92), SIMDE_FLOAT32_C(    -4.17), SIMDE_FLOAT32_C(  -682.53) },
      UINT16_C(51199) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   765.20), SIMDE_FLOAT32_C(   532.70),
        SIMDE_FLOAT32_C(  -246.65), SIMDE_FLOAT32_C(   -51.09), SIMDE_FLOAT32_C(    70.04), SIMDE_FLOAT32_C(  -700.87),
        SIMDE_FLOAT32_C(  -386.79), SIMDE_FLOAT32_C(  -965.74), SIMDE_FLOAT32_C(  -705.88), SIMDE_FLOAT32_C(   609.04),
        SIMDE_FLOAT32_C(  -835.94), SIMDE_FLOAT32_C(   577.30), SIMDE_FLOAT32_C(  -114.88), SIMDE_FLOAT32_C(   452.19) },
      { SIMDE_FLOAT32_C(  -958.12),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   -85.05),
        SIMDE_FLOAT32_C(  -347.19), SIMDE_FLOAT32_C(   -51.09), SIMDE_FLOAT32_C(    70.04), SIMDE_FLOAT32_C(   440.48),
        SIMDE_FLOAT32_C(  -386.79), SIMDE_FLOAT32_C(  -110.08), SIMDE_FLOAT32_C(   138.40), SIMDE_FLOAT32_C(  -300.61),
        SIMDE_FLOAT32_C(   207.39), SIMDE_FLOAT32_C(   275.06), SIMDE_FLOAT32_C(  -114.88), SIMDE_FLOAT32_C(   452.19) },
      UINT16_C(    0) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -930.96), SIMDE_FLOAT32_C(  -468.38),
        SIMDE_FLOAT32_C(   254.48), SIMDE_FLOAT32_C(  -317.74), SIMDE_FLOAT32_C(  -434.12), SIMDE_FLOAT32_C(   548.60),
        SIMDE_FLOAT32_C(  -708.70), SIMDE_FLOAT32_C(  -270.06), SIMDE_FLOAT32_C(   125.90), SIMDE_FLOAT32_C(   176.42),
        SIMDE_FLOAT32_C(  -817.87), SIMDE_FLOAT32_C(   167.78), SIMDE_FLOAT32_C(  -135.67), SIMDE_FLOAT32_C(   271.00) },
      { SIMDE_FLOAT32_C(   461.58),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -468.38),
        SIMDE_FLOAT32_C(   -42.38), SIMDE_FLOAT32_C(   414.18), SIMDE_FLOAT32_C(   121.01), SIMDE_FLOAT32_C(   548.60),
        SIMDE_FLOAT32_C(  -886.43), SIMDE_FLOAT32_C(  -671.60), SIMDE_FLOAT32_C(   371.08), SIMDE_FLOAT32_C(   468.51),
        SIMDE_FLOAT32_C(  -742.72), SIMDE_FLOAT32_C(   573.07), SIMDE_FLOAT32_C(  -135.67), SIMDE_FLOAT32_C(   718.86) },
      UINT16_C(49008) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   339.94), SIMDE_FLOAT32_C(  -183.64),
        SIMDE_FLOAT32_C(   331.50), SIMDE_FLOAT32_C(   631.24), SIMDE_FLOAT32_C(   546.30), SIMDE_FLOAT32_C(  -542.60),
        SIMDE_FLOAT32_C(  -192.33), SIMDE_FLOAT32_C(   728.44), SIMDE_FLOAT32_C(   625.18), SIMDE_FLOAT32_C(   672.00),
        SIMDE_FLOAT32_C(    -0.57), SIMDE_FLOAT32_C(   707.92), SIMDE_FLOAT32_C(   189.14), SIMDE_FLOAT32_C(  -435.53) },
      { SIMDE_FLOAT32_C(  -749.52),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(    60.01),
        SIMDE_FLOAT32_C(   331.50), SIMDE_FLOAT32_C(   631.24), SIMDE_FLOAT32_C(   388.41), SIMDE_FLOAT32_C(  -542.60),
        SIMDE_FLOAT32_C(   560.74), SIMDE_FLOAT32_C(   728.44), SIMDE_FLOAT32_C(   186.93), SIMDE_FLOAT32_C(   672.00),
        SIMDE_FLOAT32_C(   364.55), SIMDE_FLOAT32_C(   707.92), SIMDE_FLOAT32_C(   189.14), SIMDE_FLOAT32_C(   615.03) },
      UINT16_C(28400) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   778.26), SIMDE_FLOAT32_C(   977.70),
        SIMDE_FLOAT32_C(   287.15), SIMDE_FLOAT32_C(  -414.08), SIMDE_FLOAT32_C(   706.14), SIMDE_FLOAT32_C(   -87.67),
        SIMDE_FLOAT32_C(  -742.08), SIMDE_FLOAT32_C(  -294.43), SIMDE_FLOAT32_C(  -379.75), SIMDE_FLOAT32_C(   447.06),
        SIMDE_FLOAT32_C(   270.04), SIMDE_FLOAT32_C(  -440.75), SIMDE_FLOAT32_C(   593.82), SIMDE_FLOAT32_C(   248.70) },
      { SIMDE_FLOAT32_C(   619.26),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   977.70),
        SIMDE_FLOAT32_C(   450.45), SIMDE_FLOAT32_C(  -414.08), SIMDE_FLOAT32_C(   706.14), SIMDE_FLOAT32_C(   -87.67),
        SIMDE_FLOAT32_C(  -742.08), SIMDE_FLOAT32_C(  -294.43), SIMDE_FLOAT32_C(  -647.28), SIMDE_FLOAT32_C(   858.12),
        SIMDE_FLOAT32_C(   270.04), SIMDE_FLOAT32_C(   850.97), SIMDE_FLOAT32_C(   593.82), SIMDE_FLOAT32_C(   248.70) },
      UINT16_C( 1024) },
    { {            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(  -630.69), SIMDE_FLOAT32_C(   748.16),
        SIMDE_FLOAT32_C(  -119.80), SIMDE_FLOAT32_C(  -372.76), SIMDE_FLOAT32_C(  -546.27), SIMDE_FLOAT32_C(   500.45),
        SIMDE_FLOAT32_C(  -925.71), SIMDE_FLOAT32_C(   723.77), SIMDE_FLOAT32_C(  -940.30), SIMDE_FLOAT32_C(   668.11),
        SIMDE_FLOAT32_C(   -27.53), SIMDE_FLOAT32_C(   678.96), SIMDE_FLOAT32_C(   504.70), SIMDE_FLOAT32_C(  -686.60) },
      { SIMDE_FLOAT32_C(  -313.38),            SIMDE_MATH_NANF,            SIMDE_MATH_NANF, SIMDE_FLOAT32_C(   748.16),
        SIMDE_FLOAT32_C(  -119.80), SIMDE_FLOAT32_C(  -733.89), SIMDE_FLOAT32_C(  -546.27), SIMDE_FLOAT32_C(   945.25),
        SIMDE_FLOAT32_C(  -875.77), SIMDE_FLOAT32_C(    -9.20), SIMDE_FLOAT32_C(   796.22), SIMDE_FLOAT32_C(  -870.63),
        SIMDE_FLOAT32_C(    55.13), SIMDE_FLOAT32_C(   678.96), SIMDE_FLOAT32_C(   912.76), SIMDE_FLOAT32_C(  -686.60) },
           UINT16_MAX }
  };

  simde__m512 a, b;
  simde__mmask16 r;

  a = simde_mm512_loadu_ps(test_vec[0].a);
  b = simde_mm512_loadu_ps(test_vec[0].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask16(r, test_vec[0].r);

  a = simde_mm512_loadu_ps(test_vec[1].a);
  b = simde_mm512_loadu_ps(test_vec[1].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask16(r, test_vec[1].r);

  a = simde_mm512_loadu_ps(test_vec[2].a);
  b = simde_mm512_loadu_ps(test_vec[2].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask16(r, test_vec[2].r);

  a = simde_mm512_loadu_ps(test_vec[3].a);
  b = simde_mm512_loadu_ps(test_vec[3].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask16(r, test_vec[3].r);

  a = simde_mm512_loadu_ps(test_vec[4].a);
  b = simde_mm512_loadu_ps(test_vec[4].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask16(r, test_vec[4].r);

  a = simde_mm512_loadu_ps(test_vec[5].a);
  b = simde_mm512_loadu_ps(test_vec[5].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask16(r, test_vec[5].r);

  a = simde_mm512_loadu_ps(test_vec[6].a);
  b = simde_mm512_loadu_ps(test_vec[6].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask16(r, test_vec[6].r);

  a = simde_mm512_loadu_ps(test_vec[7].a);
  b = simde_mm512_loadu_ps(test_vec[7].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask16(r, test_vec[7].r);

  a = simde_mm512_loadu_ps(test_vec[8].a);
  b = simde_mm512_loadu_ps(test_vec[8].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask16(r, test_vec[8].r);

  a = simde_mm512_loadu_ps(test_vec[9].a);
  b = simde_mm512_loadu_ps(test_vec[9].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask16(r, test_vec[9].r);

  a = simde_mm512_loadu_ps(test_vec[10].a);
  b = simde_mm512_loadu_ps(test_vec[10].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask16(r, test_vec[10].r);

  a = simde_mm512_loadu_ps(test_vec[11].a);
  b = simde_mm512_loadu_ps(test_vec[11].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask16(r, test_vec[11].r);

  a = simde_mm512_loadu_ps(test_vec[12].a);
  b = simde_mm512_loadu_ps(test_vec[12].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask16(r, test_vec[12].r);

  a = simde_mm512_loadu_ps(test_vec[13].a);
  b = simde_mm512_loadu_ps(test_vec[13].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask16(r, test_vec[13].r);

  a = simde_mm512_loadu_ps(test_vec[14].a);
  b = simde_mm512_loadu_ps(test_vec[14].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask16(r, test_vec[14].r);

  a = simde_mm512_loadu_ps(test_vec[15].a);
  b = simde_mm512_loadu_ps(test_vec[15].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask16(r, test_vec[15].r);

  a = simde_mm512_loadu_ps(test_vec[16].a);
  b = simde_mm512_loadu_ps(test_vec[16].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask16(r, test_vec[16].r);

  a = simde_mm512_loadu_ps(test_vec[17].a);
  b = simde_mm512_loadu_ps(test_vec[17].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask16(r, test_vec[17].r);

  a = simde_mm512_loadu_ps(test_vec[18].a);
  b = simde_mm512_loadu_ps(test_vec[18].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask16(r, test_vec[18].r);

  a = simde_mm512_loadu_ps(test_vec[19].a);
  b = simde_mm512_loadu_ps(test_vec[19].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask16(r, test_vec[19].r);

  a = simde_mm512_loadu_ps(test_vec[20].a);
  b = simde_mm512_loadu_ps(test_vec[20].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask16(r, test_vec[20].r);

  a = simde_mm512_loadu_ps(test_vec[21].a);
  b = simde_mm512_loadu_ps(test_vec[21].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask16(r, test_vec[21].r);

  a = simde_mm512_loadu_ps(test_vec[22].a);
  b = simde_mm512_loadu_ps(test_vec[22].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask16(r, test_vec[22].r);

  a = simde_mm512_loadu_ps(test_vec[23].a);
  b = simde_mm512_loadu_ps(test_vec[23].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask16(r, test_vec[23].r);

  a = simde_mm512_loadu_ps(test_vec[24].a);
  b = simde_mm512_loadu_ps(test_vec[24].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask16(r, test_vec[24].r);

  a = simde_mm512_loadu_ps(test_vec[25].a);
  b = simde_mm512_loadu_ps(test_vec[25].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask16(r, test_vec[25].r);

  a = simde_mm512_loadu_ps(test_vec[26].a);
  b = simde_mm512_loadu_ps(test_vec[26].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask16(r, test_vec[26].r);

  a = simde_mm512_loadu_ps(test_vec[27].a);
  b = simde_mm512_loadu_ps(test_vec[27].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask16(r, test_vec[27].r);

  a = simde_mm512_loadu_ps(test_vec[28].a);
  b = simde_mm512_loadu_ps(test_vec[28].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask16(r, test_vec[28].r);

  a = simde_mm512_loadu_ps(test_vec[29].a);
  b = simde_mm512_loadu_ps(test_vec[29].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask16(r, test_vec[29].r);

  a = simde_mm512_loadu_ps(test_vec[30].a);
  b = simde_mm512_loadu_ps(test_vec[30].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask16(r, test_vec[30].r);

  a = simde_mm512_loadu_ps(test_vec[31].a);
  b = simde_mm512_loadu_ps(test_vec[31].b);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask16(r, test_vec[31].r);

  return 0;
#else
  fputc('\n', stdout);

  const simde__m512 nanv = simde_mm512_set1_ps(SIMDE_MATH_NANF);

  simde__m512 a, b;
  simde__mmask16 r;

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LT_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LE_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLT_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLE_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGE_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGT_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GE_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GT_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_ORD_S);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_EQ_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_test_x86_random_f32x16(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
  b = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, simde_test_codegen_random_i16()), b);
  a = simde_mm512_mask_mov_ps(a, HEDLEY_STATIC_CAST(simde__mmask16, 3), nanv);
  b = simde_mm512_mask_mov_ps(b, HEDLEY_STATIC_CAST(simde__mmask16, 6), nanv);
  r = simde_mm512_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_test_x86_write_f32x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f32x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask16(2, r, SIMDE_TEST_VEC_POS_LAST);

  return 1;
#endif
}

static int
test_simde_mm256_cmp_ps_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  simde__m256 a, b;
  simde__mmask8 e, r;

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -521.70), SIMDE_FLOAT32_C(   208.95), SIMDE_FLOAT32_C(  -892.52), SIMDE_FLOAT32_C(   822.05),
                         SIMDE_FLOAT32_C(  -914.87), SIMDE_FLOAT32_C(   926.51), SIMDE_FLOAT32_C(  -568.65), SIMDE_FLOAT32_C(  -377.10));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   846.31), SIMDE_FLOAT32_C(  -287.77), SIMDE_FLOAT32_C(  -505.72), SIMDE_FLOAT32_C(  -231.66),
                         SIMDE_FLOAT32_C(   589.02), SIMDE_FLOAT32_C(  -703.08), SIMDE_FLOAT32_C(  -955.43), SIMDE_FLOAT32_C(   989.02));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -285.67), SIMDE_FLOAT32_C(  -694.44), SIMDE_FLOAT32_C(  -819.49), SIMDE_FLOAT32_C(   958.85),
                         SIMDE_FLOAT32_C(  -277.57), SIMDE_FLOAT32_C(   148.21), SIMDE_FLOAT32_C(   209.64), SIMDE_FLOAT32_C(  -545.40));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   646.39), SIMDE_FLOAT32_C(   361.60), SIMDE_FLOAT32_C(   -15.47), SIMDE_FLOAT32_C(    23.49),
                         SIMDE_FLOAT32_C(    66.16), SIMDE_FLOAT32_C(   788.78), SIMDE_FLOAT32_C(   421.77), SIMDE_FLOAT32_C(  -189.56));
  e = UINT8_C(239);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   384.60), SIMDE_FLOAT32_C(   716.23), SIMDE_FLOAT32_C(   -59.52), SIMDE_FLOAT32_C(   395.59),
                         SIMDE_FLOAT32_C(   237.94), SIMDE_FLOAT32_C(   731.52), SIMDE_FLOAT32_C(   288.10), SIMDE_FLOAT32_C(   415.88));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   -37.96), SIMDE_FLOAT32_C(   599.69), SIMDE_FLOAT32_C(   685.85), SIMDE_FLOAT32_C(  -492.56),
                         SIMDE_FLOAT32_C(   753.39), SIMDE_FLOAT32_C(   -26.38), SIMDE_FLOAT32_C(  -986.84), SIMDE_FLOAT32_C(   -14.96));
  e = UINT8_C( 40);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   738.86), SIMDE_FLOAT32_C(   568.67), SIMDE_FLOAT32_C(   990.03), SIMDE_FLOAT32_C(   -71.58),
                         SIMDE_FLOAT32_C(  -145.66), SIMDE_FLOAT32_C(   684.47), SIMDE_FLOAT32_C(  -252.09), SIMDE_FLOAT32_C(  -104.51));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   757.87), SIMDE_FLOAT32_C(  -918.31), SIMDE_FLOAT32_C(  -833.39), SIMDE_FLOAT32_C(  -658.02),
                         SIMDE_FLOAT32_C(  -564.70), SIMDE_FLOAT32_C(  -194.98), SIMDE_FLOAT32_C(   357.45), SIMDE_FLOAT32_C(   411.80));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   738.73), SIMDE_FLOAT32_C(  -765.09), SIMDE_FLOAT32_C(  -287.96), SIMDE_FLOAT32_C(  -246.32),
                         SIMDE_FLOAT32_C(  -149.69), SIMDE_FLOAT32_C(    -4.20), SIMDE_FLOAT32_C(   813.21), SIMDE_FLOAT32_C(   454.72));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   789.87), SIMDE_FLOAT32_C(  -805.33), SIMDE_FLOAT32_C(    91.81), SIMDE_FLOAT32_C(  -105.62),
                         SIMDE_FLOAT32_C(   232.63), SIMDE_FLOAT32_C(   492.12), SIMDE_FLOAT32_C(   208.53), SIMDE_FLOAT32_C(  -274.80));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   280.98), SIMDE_FLOAT32_C(  -493.00), SIMDE_FLOAT32_C(  -787.12), SIMDE_FLOAT32_C(   869.18),
                         SIMDE_FLOAT32_C(  -231.86), SIMDE_FLOAT32_C(  -355.79), SIMDE_FLOAT32_C(   879.15), SIMDE_FLOAT32_C(   839.72));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   -66.65), SIMDE_FLOAT32_C(   670.17), SIMDE_FLOAT32_C(   797.96), SIMDE_FLOAT32_C(   478.63),
                         SIMDE_FLOAT32_C(   912.31), SIMDE_FLOAT32_C(   716.28), SIMDE_FLOAT32_C(   312.02), SIMDE_FLOAT32_C(   570.33));
  e = UINT8_C(147);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -896.79), SIMDE_FLOAT32_C(  -896.41), SIMDE_FLOAT32_C(  -981.44), SIMDE_FLOAT32_C(   378.01),
                         SIMDE_FLOAT32_C(  -635.14), SIMDE_FLOAT32_C(   783.65), SIMDE_FLOAT32_C(  -334.02), SIMDE_FLOAT32_C(   611.17));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -472.77), SIMDE_FLOAT32_C(   911.34), SIMDE_FLOAT32_C(   530.52), SIMDE_FLOAT32_C(  -312.49),
                         SIMDE_FLOAT32_C(  -878.53), SIMDE_FLOAT32_C(   335.84), SIMDE_FLOAT32_C(   595.70), SIMDE_FLOAT32_C(   227.09));
  e = UINT8_C( 29);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -661.25), SIMDE_FLOAT32_C(  -440.17), SIMDE_FLOAT32_C(   802.38), SIMDE_FLOAT32_C(  -231.58),
                         SIMDE_FLOAT32_C(   278.84), SIMDE_FLOAT32_C(   295.37), SIMDE_FLOAT32_C(  -444.45), SIMDE_FLOAT32_C(   409.66));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   685.24), SIMDE_FLOAT32_C(   526.37), SIMDE_FLOAT32_C(   921.23), SIMDE_FLOAT32_C(  -925.93),
                         SIMDE_FLOAT32_C(  -406.98), SIMDE_FLOAT32_C(  -748.94), SIMDE_FLOAT32_C(  -723.90), SIMDE_FLOAT32_C(   114.39));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -444.32), SIMDE_FLOAT32_C(  -931.57), SIMDE_FLOAT32_C(  -846.31), SIMDE_FLOAT32_C(   328.59),
                         SIMDE_FLOAT32_C(   965.22), SIMDE_FLOAT32_C(  -949.90), SIMDE_FLOAT32_C(   310.02), SIMDE_FLOAT32_C(  -412.80));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -655.55), SIMDE_FLOAT32_C(   -35.87), SIMDE_FLOAT32_C(  -411.51), SIMDE_FLOAT32_C(   -65.21),
                         SIMDE_FLOAT32_C(  -563.10), SIMDE_FLOAT32_C(  -322.85), SIMDE_FLOAT32_C(   404.27), SIMDE_FLOAT32_C(   749.39));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   176.28), SIMDE_FLOAT32_C(  -748.79), SIMDE_FLOAT32_C(  -816.88), SIMDE_FLOAT32_C(  -938.12),
                         SIMDE_FLOAT32_C(   912.46), SIMDE_FLOAT32_C(   623.29), SIMDE_FLOAT32_C(  -740.49), SIMDE_FLOAT32_C(   144.04));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(    10.70), SIMDE_FLOAT32_C(  -781.47), SIMDE_FLOAT32_C(   295.67), SIMDE_FLOAT32_C(  -576.51),
                         SIMDE_FLOAT32_C(  -466.71), SIMDE_FLOAT32_C(   769.30), SIMDE_FLOAT32_C(  -497.74), SIMDE_FLOAT32_C(  -540.78));
  e = UINT8_C( 54);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -828.30), SIMDE_FLOAT32_C(  -510.04), SIMDE_FLOAT32_C(    44.34), SIMDE_FLOAT32_C(  -577.69),
                         SIMDE_FLOAT32_C(   934.28), SIMDE_FLOAT32_C(   -24.09), SIMDE_FLOAT32_C(  -731.37), SIMDE_FLOAT32_C(  -394.31));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -100.36), SIMDE_FLOAT32_C(   727.85), SIMDE_FLOAT32_C(   572.74), SIMDE_FLOAT32_C(   755.60),
                         SIMDE_FLOAT32_C(   383.39), SIMDE_FLOAT32_C(  -391.40), SIMDE_FLOAT32_C(   167.11), SIMDE_FLOAT32_C(  -551.39));
  e = UINT8_C(242);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   993.48), SIMDE_FLOAT32_C(    70.41), SIMDE_FLOAT32_C(    63.31), SIMDE_FLOAT32_C(   534.26),
                         SIMDE_FLOAT32_C(   894.13), SIMDE_FLOAT32_C(  -187.90), SIMDE_FLOAT32_C(   351.14), SIMDE_FLOAT32_C(   832.25));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -258.93), SIMDE_FLOAT32_C(    -0.24), SIMDE_FLOAT32_C(  -254.70), SIMDE_FLOAT32_C(  -864.62),
                         SIMDE_FLOAT32_C(   989.07), SIMDE_FLOAT32_C(  -473.23), SIMDE_FLOAT32_C(  -160.29), SIMDE_FLOAT32_C(   565.58));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   468.62), SIMDE_FLOAT32_C(   607.95), SIMDE_FLOAT32_C(   165.31), SIMDE_FLOAT32_C(    20.01),
                         SIMDE_FLOAT32_C(   436.25), SIMDE_FLOAT32_C(  -324.65), SIMDE_FLOAT32_C(   975.68), SIMDE_FLOAT32_C(    13.93));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   621.54), SIMDE_FLOAT32_C(   -12.34), SIMDE_FLOAT32_C(  -420.14), SIMDE_FLOAT32_C(   789.29),
                         SIMDE_FLOAT32_C(  -911.98), SIMDE_FLOAT32_C(  -147.98), SIMDE_FLOAT32_C(  -783.45), SIMDE_FLOAT32_C(  -667.58));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -571.34), SIMDE_FLOAT32_C(   458.74), SIMDE_FLOAT32_C(  -413.92), SIMDE_FLOAT32_C(  -136.92),
                         SIMDE_FLOAT32_C(   465.26), SIMDE_FLOAT32_C(   515.67), SIMDE_FLOAT32_C(   799.77), SIMDE_FLOAT32_C(   931.00));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   744.75), SIMDE_FLOAT32_C(  -697.77), SIMDE_FLOAT32_C(   417.49), SIMDE_FLOAT32_C(  -269.18),
                         SIMDE_FLOAT32_C(   561.16), SIMDE_FLOAT32_C(  -582.28), SIMDE_FLOAT32_C(   985.51), SIMDE_FLOAT32_C(   425.78));
  e = UINT8_C( 85);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -524.68), SIMDE_FLOAT32_C(   881.80), SIMDE_FLOAT32_C(  -211.06), SIMDE_FLOAT32_C(  -857.10),
                         SIMDE_FLOAT32_C(  -586.82), SIMDE_FLOAT32_C(   180.99), SIMDE_FLOAT32_C(   -22.41), SIMDE_FLOAT32_C(   393.17));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   244.68), SIMDE_FLOAT32_C(  -583.68), SIMDE_FLOAT32_C(   551.01), SIMDE_FLOAT32_C(   313.68),
                         SIMDE_FLOAT32_C(  -205.22), SIMDE_FLOAT32_C(  -436.66), SIMDE_FLOAT32_C(  -266.18), SIMDE_FLOAT32_C(     5.49));
  e = UINT8_C( 71);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   943.85), SIMDE_FLOAT32_C(  -357.49), SIMDE_FLOAT32_C(  -831.32), SIMDE_FLOAT32_C(  -481.93),
                         SIMDE_FLOAT32_C(  -786.15), SIMDE_FLOAT32_C(  -290.06), SIMDE_FLOAT32_C(   931.99), SIMDE_FLOAT32_C(   350.78));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   870.89), SIMDE_FLOAT32_C(  -370.24), SIMDE_FLOAT32_C(   807.25), SIMDE_FLOAT32_C(  -522.28),
                         SIMDE_FLOAT32_C(  -114.99), SIMDE_FLOAT32_C(   505.02), SIMDE_FLOAT32_C(    60.23), SIMDE_FLOAT32_C(  -845.81));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   605.19), SIMDE_FLOAT32_C(   403.06), SIMDE_FLOAT32_C(  -834.13), SIMDE_FLOAT32_C(  -400.31),
                         SIMDE_FLOAT32_C(   -72.27), SIMDE_FLOAT32_C(  -715.93), SIMDE_FLOAT32_C(   810.75), SIMDE_FLOAT32_C(  -215.16));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -131.82), SIMDE_FLOAT32_C(   458.04), SIMDE_FLOAT32_C(  -183.71), SIMDE_FLOAT32_C(   517.41),
                         SIMDE_FLOAT32_C(  -786.64), SIMDE_FLOAT32_C(  -600.03), SIMDE_FLOAT32_C(   966.40), SIMDE_FLOAT32_C(  -100.31));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -509.15), SIMDE_FLOAT32_C(   210.20), SIMDE_FLOAT32_C(   724.55), SIMDE_FLOAT32_C(  -663.34),
                         SIMDE_FLOAT32_C(   266.35), SIMDE_FLOAT32_C(    82.04), SIMDE_FLOAT32_C(  -832.02), SIMDE_FLOAT32_C(  -251.72));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   307.30), SIMDE_FLOAT32_C(   133.40), SIMDE_FLOAT32_C(  -994.38), SIMDE_FLOAT32_C(  -477.53),
                         SIMDE_FLOAT32_C(   262.51), SIMDE_FLOAT32_C(   375.86), SIMDE_FLOAT32_C(  -284.78), SIMDE_FLOAT32_C(  -215.22));
  e = UINT8_C(151);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -516.98), SIMDE_FLOAT32_C(  -978.75), SIMDE_FLOAT32_C(   638.09), SIMDE_FLOAT32_C(   583.33),
                         SIMDE_FLOAT32_C(  -583.93), SIMDE_FLOAT32_C(  -764.96), SIMDE_FLOAT32_C(   417.47), SIMDE_FLOAT32_C(   816.37));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   985.79), SIMDE_FLOAT32_C(   990.09), SIMDE_FLOAT32_C(  -845.58), SIMDE_FLOAT32_C(   237.51),
                         SIMDE_FLOAT32_C(   121.90), SIMDE_FLOAT32_C(  -303.62), SIMDE_FLOAT32_C(  -578.78), SIMDE_FLOAT32_C(   604.49));
  e = UINT8_C(204);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   581.46), SIMDE_FLOAT32_C(   149.92), SIMDE_FLOAT32_C(  -537.65), SIMDE_FLOAT32_C(  -203.32),
                         SIMDE_FLOAT32_C(  -340.94), SIMDE_FLOAT32_C(   252.14), SIMDE_FLOAT32_C(    72.13), SIMDE_FLOAT32_C(  -677.60));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -652.22), SIMDE_FLOAT32_C(     7.34), SIMDE_FLOAT32_C(   977.37), SIMDE_FLOAT32_C(  -468.59),
                         SIMDE_FLOAT32_C(   700.03), SIMDE_FLOAT32_C(  -156.03), SIMDE_FLOAT32_C(  -474.22), SIMDE_FLOAT32_C(   177.57));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -515.03), SIMDE_FLOAT32_C(   461.19), SIMDE_FLOAT32_C(  -214.90), SIMDE_FLOAT32_C(  -119.53),
                         SIMDE_FLOAT32_C(   -21.83), SIMDE_FLOAT32_C(  -236.15), SIMDE_FLOAT32_C(   242.38), SIMDE_FLOAT32_C(   394.83));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -365.60), SIMDE_FLOAT32_C(  -570.38), SIMDE_FLOAT32_C(   596.96), SIMDE_FLOAT32_C(  -688.00),
                         SIMDE_FLOAT32_C(  -556.17), SIMDE_FLOAT32_C(   606.87), SIMDE_FLOAT32_C(  -842.43), SIMDE_FLOAT32_C(   206.32));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   321.68), SIMDE_FLOAT32_C(    47.23), SIMDE_FLOAT32_C(  -556.61), SIMDE_FLOAT32_C(  -855.88),
                         SIMDE_FLOAT32_C(   465.77), SIMDE_FLOAT32_C(   293.47), SIMDE_FLOAT32_C(   681.77), SIMDE_FLOAT32_C(  -330.91));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   263.40), SIMDE_FLOAT32_C(   848.36), SIMDE_FLOAT32_C(  -970.94), SIMDE_FLOAT32_C(   868.56),
                         SIMDE_FLOAT32_C(   500.58), SIMDE_FLOAT32_C(    21.72), SIMDE_FLOAT32_C(   891.20), SIMDE_FLOAT32_C(   -30.83));
  e = UINT8_C(164);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -396.38), SIMDE_FLOAT32_C(  -363.13), SIMDE_FLOAT32_C(   702.76), SIMDE_FLOAT32_C(   397.30),
                         SIMDE_FLOAT32_C(  -848.09), SIMDE_FLOAT32_C(  -758.43), SIMDE_FLOAT32_C(  -387.80), SIMDE_FLOAT32_C(   271.43));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -490.21), SIMDE_FLOAT32_C(  -193.27), SIMDE_FLOAT32_C(   477.07), SIMDE_FLOAT32_C(   840.70),
                         SIMDE_FLOAT32_C(  -827.67), SIMDE_FLOAT32_C(    47.45), SIMDE_FLOAT32_C(  -756.26), SIMDE_FLOAT32_C(   860.33));
  e = UINT8_C(162);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   512.75), SIMDE_FLOAT32_C(  -375.36), SIMDE_FLOAT32_C(    22.78), SIMDE_FLOAT32_C(  -456.42),
                         SIMDE_FLOAT32_C(   302.96), SIMDE_FLOAT32_C(   975.56), SIMDE_FLOAT32_C(  -899.81), SIMDE_FLOAT32_C(   158.84));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   -53.14), SIMDE_FLOAT32_C(  -954.06), SIMDE_FLOAT32_C(  -138.32), SIMDE_FLOAT32_C(   675.42),
                         SIMDE_FLOAT32_C(  -217.45), SIMDE_FLOAT32_C(    13.33), SIMDE_FLOAT32_C(   646.36), SIMDE_FLOAT32_C(   -86.02));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   850.60), SIMDE_FLOAT32_C(   474.80), SIMDE_FLOAT32_C(   735.64), SIMDE_FLOAT32_C(   990.27),
                         SIMDE_FLOAT32_C(  -128.82), SIMDE_FLOAT32_C(    98.76), SIMDE_FLOAT32_C(  -712.49), SIMDE_FLOAT32_C(   473.88));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   158.16), SIMDE_FLOAT32_C(  -670.12), SIMDE_FLOAT32_C(  -170.35), SIMDE_FLOAT32_C(   999.32),
                         SIMDE_FLOAT32_C(   820.08), SIMDE_FLOAT32_C(  -977.08), SIMDE_FLOAT32_C(  -477.75), SIMDE_FLOAT32_C(   979.38));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -757.80), SIMDE_FLOAT32_C(   -13.83), SIMDE_FLOAT32_C(    85.77), SIMDE_FLOAT32_C(   328.22),
                         SIMDE_FLOAT32_C(   473.42), SIMDE_FLOAT32_C(  -538.88), SIMDE_FLOAT32_C(  -694.57), SIMDE_FLOAT32_C(   -70.16));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -664.94), SIMDE_FLOAT32_C(   354.41), SIMDE_FLOAT32_C(    70.69), SIMDE_FLOAT32_C(  -138.82),
                         SIMDE_FLOAT32_C(  -592.45), SIMDE_FLOAT32_C(    24.74), SIMDE_FLOAT32_C(   999.49), SIMDE_FLOAT32_C(  -267.87));
  e = UINT8_C(198);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -831.82), SIMDE_FLOAT32_C(   199.06), SIMDE_FLOAT32_C(  -318.95), SIMDE_FLOAT32_C(  -811.20),
                         SIMDE_FLOAT32_C(   348.47), SIMDE_FLOAT32_C(   206.24), SIMDE_FLOAT32_C(  -546.83), SIMDE_FLOAT32_C(   358.20));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   -18.53), SIMDE_FLOAT32_C(  -639.22), SIMDE_FLOAT32_C(  -681.86), SIMDE_FLOAT32_C(  -948.37),
                         SIMDE_FLOAT32_C(   202.62), SIMDE_FLOAT32_C(   988.27), SIMDE_FLOAT32_C(   221.98), SIMDE_FLOAT32_C(   203.30));
  e = UINT8_C(134);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -360.20), SIMDE_FLOAT32_C(  -806.01), SIMDE_FLOAT32_C(   441.06), SIMDE_FLOAT32_C(   907.67),
                         SIMDE_FLOAT32_C(   951.79), SIMDE_FLOAT32_C(  -545.11), SIMDE_FLOAT32_C(  -178.10), SIMDE_FLOAT32_C(  -376.43));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   647.62), SIMDE_FLOAT32_C(  -363.20), SIMDE_FLOAT32_C(  -598.24), SIMDE_FLOAT32_C(  -710.58),
                         SIMDE_FLOAT32_C(  -698.26), SIMDE_FLOAT32_C(    47.35), SIMDE_FLOAT32_C(   218.73), SIMDE_FLOAT32_C(   440.56));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   727.38), SIMDE_FLOAT32_C(   211.91), SIMDE_FLOAT32_C(  -804.86), SIMDE_FLOAT32_C(  -475.91),
                         SIMDE_FLOAT32_C(    43.73), SIMDE_FLOAT32_C(    -3.92), SIMDE_FLOAT32_C(   843.04), SIMDE_FLOAT32_C(  -145.07));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -858.11), SIMDE_FLOAT32_C(  -549.77), SIMDE_FLOAT32_C(   290.78), SIMDE_FLOAT32_C(   518.32),
                         SIMDE_FLOAT32_C(   468.76), SIMDE_FLOAT32_C(   -70.00), SIMDE_FLOAT32_C(   200.18), SIMDE_FLOAT32_C(   417.13));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   786.75), SIMDE_FLOAT32_C(  -339.84), SIMDE_FLOAT32_C(  -712.33), SIMDE_FLOAT32_C(  -653.81),
                         SIMDE_FLOAT32_C(  -979.64), SIMDE_FLOAT32_C(  -906.32), SIMDE_FLOAT32_C(   -94.88), SIMDE_FLOAT32_C(  -887.31));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   -35.80), SIMDE_FLOAT32_C(   443.44), SIMDE_FLOAT32_C(  -274.72), SIMDE_FLOAT32_C(  -890.73),
                         SIMDE_FLOAT32_C(   795.82), SIMDE_FLOAT32_C(  -911.52), SIMDE_FLOAT32_C(   707.51), SIMDE_FLOAT32_C(   506.40));
  e = UINT8_C(148);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -948.21), SIMDE_FLOAT32_C(  -180.21), SIMDE_FLOAT32_C(   219.84), SIMDE_FLOAT32_C(  -365.33),
                         SIMDE_FLOAT32_C(    92.40), SIMDE_FLOAT32_C(  -992.07), SIMDE_FLOAT32_C(  -560.48), SIMDE_FLOAT32_C(  -431.68));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(   153.26), SIMDE_FLOAT32_C(  -919.77), SIMDE_FLOAT32_C(   970.78), SIMDE_FLOAT32_C(    40.57),
                         SIMDE_FLOAT32_C(   938.34), SIMDE_FLOAT32_C(   520.55), SIMDE_FLOAT32_C(   749.79), SIMDE_FLOAT32_C(  -579.98));
  e = UINT8_C( 65);
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_ps(SIMDE_FLOAT32_C(   967.99), SIMDE_FLOAT32_C(     8.83), SIMDE_FLOAT32_C(   833.78), SIMDE_FLOAT32_C(  -538.41),
                         SIMDE_FLOAT32_C(   222.09), SIMDE_FLOAT32_C(   173.62), SIMDE_FLOAT32_C(  -826.08), SIMDE_FLOAT32_C(  -124.10));
  b = simde_mm256_set_ps(SIMDE_FLOAT32_C(  -609.09), SIMDE_FLOAT32_C(  -385.23), SIMDE_FLOAT32_C(   207.26), SIMDE_FLOAT32_C(   822.59),
                         SIMDE_FLOAT32_C(   650.57), SIMDE_FLOAT32_C(   763.82), SIMDE_FLOAT32_C(    97.31), SIMDE_FLOAT32_C(   541.30));
  e = UINT8_MAX;
  r = simde_mm256_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask8(r, e);

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 32 ; i++) {
    simde__m256 a = simde_test_x86_random_f32x8(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m256 b = simde_test_x86_random_f32x8(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    int imm8 = i;
    simde__mmask8 r;
    SIMDE_CONSTIFY_32_(simde_mm256_cmp_ps_mask, r, (HEDLEY_UNREACHABLE(), 0), imm8, a, b);

    simde_test_x86_write_f32x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_codegen_write_i32(2, imm8, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_cmp_ps_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  simde__m128 a, b;
  simde__mmask8 e, r;

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   609.48), SIMDE_FLOAT32_C(   744.95), SIMDE_FLOAT32_C(  -768.13), SIMDE_FLOAT32_C(   -64.79));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   772.67), SIMDE_FLOAT32_C(   132.73), SIMDE_FLOAT32_C(  -998.15), SIMDE_FLOAT32_C(   759.27));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   248.79), SIMDE_FLOAT32_C(   147.05), SIMDE_FLOAT32_C(   -94.71), SIMDE_FLOAT32_C(  -435.42));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -898.17), SIMDE_FLOAT32_C(  -302.87), SIMDE_FLOAT32_C(   621.93), SIMDE_FLOAT32_C(   462.90));
  e = UINT8_C(  3);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   805.59), SIMDE_FLOAT32_C(   659.02), SIMDE_FLOAT32_C(   192.48), SIMDE_FLOAT32_C(  -313.67));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -516.88), SIMDE_FLOAT32_C(   851.69), SIMDE_FLOAT32_C(   929.84), SIMDE_FLOAT32_C(   859.03));
  e = UINT8_C(  7);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   671.23), SIMDE_FLOAT32_C(   440.78), SIMDE_FLOAT32_C(   396.17), SIMDE_FLOAT32_C(  -933.28));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   -73.11), SIMDE_FLOAT32_C(  -829.33), SIMDE_FLOAT32_C(  -379.83), SIMDE_FLOAT32_C(   991.67));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -388.69), SIMDE_FLOAT32_C(  -463.63), SIMDE_FLOAT32_C(   915.63), SIMDE_FLOAT32_C(  -147.97));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -517.95), SIMDE_FLOAT32_C(  -616.02), SIMDE_FLOAT32_C(   669.10), SIMDE_FLOAT32_C(   917.47));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -962.71), SIMDE_FLOAT32_C(   730.84), SIMDE_FLOAT32_C(   531.03), SIMDE_FLOAT32_C(  -425.61));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   839.29), SIMDE_FLOAT32_C(  -860.88), SIMDE_FLOAT32_C(  -572.03), SIMDE_FLOAT32_C(   152.96));
  e = UINT8_C(  6);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   479.48), SIMDE_FLOAT32_C(   644.89), SIMDE_FLOAT32_C(   798.14), SIMDE_FLOAT32_C(   620.45));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   794.70), SIMDE_FLOAT32_C(   962.60), SIMDE_FLOAT32_C(   496.58), SIMDE_FLOAT32_C(   727.97));
  e = UINT8_C(  2);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -115.58), SIMDE_FLOAT32_C(   465.93), SIMDE_FLOAT32_C(   403.39), SIMDE_FLOAT32_C(  -107.25));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -124.42), SIMDE_FLOAT32_C(   811.31), SIMDE_FLOAT32_C(   636.61), SIMDE_FLOAT32_C(  -976.45));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   469.70), SIMDE_FLOAT32_C(   486.89), SIMDE_FLOAT32_C(  -652.32), SIMDE_FLOAT32_C(   552.23));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -408.83), SIMDE_FLOAT32_C(   951.75), SIMDE_FLOAT32_C(   870.87), SIMDE_FLOAT32_C(  -983.22));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -445.14), SIMDE_FLOAT32_C(  -371.55), SIMDE_FLOAT32_C(   682.59), SIMDE_FLOAT32_C(   401.90));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   731.01), SIMDE_FLOAT32_C(  -605.85), SIMDE_FLOAT32_C(  -232.43), SIMDE_FLOAT32_C(  -889.44));
  e = UINT8_C(  8);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -706.31), SIMDE_FLOAT32_C(   210.49), SIMDE_FLOAT32_C(  -960.96), SIMDE_FLOAT32_C(  -434.29));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -571.64), SIMDE_FLOAT32_C(  -911.62), SIMDE_FLOAT32_C(   173.09), SIMDE_FLOAT32_C(   535.62));
  e = UINT8_C( 11);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -399.97), SIMDE_FLOAT32_C(   312.78), SIMDE_FLOAT32_C(   554.32), SIMDE_FLOAT32_C(  -423.52));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -256.85), SIMDE_FLOAT32_C(   475.61), SIMDE_FLOAT32_C(   124.09), SIMDE_FLOAT32_C(   190.92));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   488.55), SIMDE_FLOAT32_C(  -787.14), SIMDE_FLOAT32_C(   -37.50), SIMDE_FLOAT32_C(   471.77));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -764.73), SIMDE_FLOAT32_C(  -920.29), SIMDE_FLOAT32_C(  -835.39), SIMDE_FLOAT32_C(  -166.63));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   957.77), SIMDE_FLOAT32_C(  -209.87), SIMDE_FLOAT32_C(  -291.83), SIMDE_FLOAT32_C(   847.21));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -958.55), SIMDE_FLOAT32_C(   688.78), SIMDE_FLOAT32_C(   184.29), SIMDE_FLOAT32_C(   475.74));
  e = UINT8_C(  9);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -241.05), SIMDE_FLOAT32_C(  -664.86), SIMDE_FLOAT32_C(  -100.72), SIMDE_FLOAT32_C(   223.33));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -351.15), SIMDE_FLOAT32_C(   187.31), SIMDE_FLOAT32_C(  -576.47), SIMDE_FLOAT32_C(  -927.63));
  e = UINT8_C( 11);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   168.76), SIMDE_FLOAT32_C(   248.88), SIMDE_FLOAT32_C(  -499.91), SIMDE_FLOAT32_C(   977.84));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(    95.95), SIMDE_FLOAT32_C(   911.92), SIMDE_FLOAT32_C(  -275.50), SIMDE_FLOAT32_C(   624.18));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -479.63), SIMDE_FLOAT32_C(  -415.51), SIMDE_FLOAT32_C(  -875.22), SIMDE_FLOAT32_C(   687.00));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -863.41), SIMDE_FLOAT32_C(  -244.36), SIMDE_FLOAT32_C(  -335.79), SIMDE_FLOAT32_C(  -710.61));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -151.88), SIMDE_FLOAT32_C(  -905.64), SIMDE_FLOAT32_C(   545.78), SIMDE_FLOAT32_C(   372.38));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   953.40), SIMDE_FLOAT32_C(  -110.43), SIMDE_FLOAT32_C(   783.15), SIMDE_FLOAT32_C(  -269.93));
  e = UINT8_C( 14);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -245.20), SIMDE_FLOAT32_C(  -287.66), SIMDE_FLOAT32_C(   224.71), SIMDE_FLOAT32_C(  -317.58));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   626.08), SIMDE_FLOAT32_C(   403.65), SIMDE_FLOAT32_C(   899.65), SIMDE_FLOAT32_C(   648.24));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -976.07), SIMDE_FLOAT32_C(  -205.16), SIMDE_FLOAT32_C(  -347.47), SIMDE_FLOAT32_C(  -600.25));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(    64.03), SIMDE_FLOAT32_C(   119.88), SIMDE_FLOAT32_C(  -293.24), SIMDE_FLOAT32_C(   377.03));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   120.92), SIMDE_FLOAT32_C(   584.40), SIMDE_FLOAT32_C(   704.37), SIMDE_FLOAT32_C(  -168.46));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   740.95), SIMDE_FLOAT32_C(   257.52), SIMDE_FLOAT32_C(  -659.95), SIMDE_FLOAT32_C(  -631.42));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -384.11), SIMDE_FLOAT32_C(  -410.93), SIMDE_FLOAT32_C(   351.88), SIMDE_FLOAT32_C(   885.83));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   817.45), SIMDE_FLOAT32_C(  -430.71), SIMDE_FLOAT32_C(   478.64), SIMDE_FLOAT32_C(   135.03));
  e = UINT8_C(  5);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -648.41), SIMDE_FLOAT32_C(  -427.75), SIMDE_FLOAT32_C(   281.63), SIMDE_FLOAT32_C(  -296.65));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   581.03), SIMDE_FLOAT32_C(   977.67), SIMDE_FLOAT32_C(   975.90), SIMDE_FLOAT32_C(   181.29));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -994.54), SIMDE_FLOAT32_C(   604.96), SIMDE_FLOAT32_C(  -227.48), SIMDE_FLOAT32_C(  -371.57));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -689.19), SIMDE_FLOAT32_C(    69.49), SIMDE_FLOAT32_C(  -275.17), SIMDE_FLOAT32_C(   479.28));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -202.22), SIMDE_FLOAT32_C(   431.74), SIMDE_FLOAT32_C(  -346.11), SIMDE_FLOAT32_C(  -570.80));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -120.23), SIMDE_FLOAT32_C(  -461.27), SIMDE_FLOAT32_C(  -310.75), SIMDE_FLOAT32_C(    -6.06));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   176.16), SIMDE_FLOAT32_C(   495.66), SIMDE_FLOAT32_C(   127.80), SIMDE_FLOAT32_C(  -958.87));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   309.80), SIMDE_FLOAT32_C(    -6.39), SIMDE_FLOAT32_C(  -935.05), SIMDE_FLOAT32_C(  -393.55));
  e = UINT8_C(  9);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -472.13), SIMDE_FLOAT32_C(   661.39), SIMDE_FLOAT32_C(   565.86), SIMDE_FLOAT32_C(   346.58));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -829.81), SIMDE_FLOAT32_C(  -891.10), SIMDE_FLOAT32_C(   639.07), SIMDE_FLOAT32_C(   541.76));
  e = UINT8_C(  3);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   890.86), SIMDE_FLOAT32_C(  -824.36), SIMDE_FLOAT32_C(   713.86), SIMDE_FLOAT32_C(  -588.42));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -132.11), SIMDE_FLOAT32_C(  -798.33), SIMDE_FLOAT32_C(   245.13), SIMDE_FLOAT32_C(  -561.31));
  e = UINT8_C(  0);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(  -107.03), SIMDE_FLOAT32_C(   665.67), SIMDE_FLOAT32_C(   633.41), SIMDE_FLOAT32_C(   899.03));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -636.20), SIMDE_FLOAT32_C(   772.74), SIMDE_FLOAT32_C(  -795.59), SIMDE_FLOAT32_C(  -677.34));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   938.66), SIMDE_FLOAT32_C(   539.96), SIMDE_FLOAT32_C(   268.40), SIMDE_FLOAT32_C(   332.21));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(  -320.07), SIMDE_FLOAT32_C(   248.46), SIMDE_FLOAT32_C(  -466.43), SIMDE_FLOAT32_C(   333.35));
  e = UINT8_C( 14);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   641.18), SIMDE_FLOAT32_C(   207.80), SIMDE_FLOAT32_C(   -90.15), SIMDE_FLOAT32_C(  -900.57));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   -39.50), SIMDE_FLOAT32_C(   811.37), SIMDE_FLOAT32_C(   316.69), SIMDE_FLOAT32_C(  -451.08));
  e = UINT8_C(  8);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_ps(SIMDE_FLOAT32_C(   469.24), SIMDE_FLOAT32_C(  -148.64), SIMDE_FLOAT32_C(   987.01), SIMDE_FLOAT32_C(    30.55));
  b = simde_mm_set_ps(SIMDE_FLOAT32_C(   131.18), SIMDE_FLOAT32_C(  -662.87), SIMDE_FLOAT32_C(    53.03), SIMDE_FLOAT32_C(   232.15));
  e = UINT8_C( 15);
  r = simde_mm_cmp_ps_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask8(r, e);

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 32 ; i++) {
    simde__m128 a = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m128 b = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    int imm8 = i;
    simde__mmask8 r;
    SIMDE_CONSTIFY_32_(simde_mm_cmp_ps_mask, r, (HEDLEY_UNREACHABLE(), 0), imm8, a, b);

    simde_test_x86_write_f32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_codegen_write_i32(2, imm8, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm512_cmp_pd_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  static const struct {
    const simde_float64 a[8];
    const simde_float64 b[8];
    const simde__mmask8 r;
  } test_vec[] = {
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   971.38), SIMDE_FLOAT64_C(   318.70),
        SIMDE_FLOAT64_C(   169.28), SIMDE_FLOAT64_C(  -796.15), SIMDE_FLOAT64_C(   451.06), SIMDE_FLOAT64_C(  -435.12) },
      { SIMDE_FLOAT64_C(   683.13),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   318.70),
        SIMDE_FLOAT64_C(  -564.36), SIMDE_FLOAT64_C(   733.28), SIMDE_FLOAT64_C(   451.06), SIMDE_FLOAT64_C(  -435.12) },
      UINT8_C(200) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -305.32), SIMDE_FLOAT64_C(   832.38),
        SIMDE_FLOAT64_C(   981.02), SIMDE_FLOAT64_C(  -160.50), SIMDE_FLOAT64_C(  -949.28), SIMDE_FLOAT64_C(  -629.24) },
      { SIMDE_FLOAT64_C(  -115.84),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   832.38),
        SIMDE_FLOAT64_C(   981.02), SIMDE_FLOAT64_C(  -160.50), SIMDE_FLOAT64_C(   494.24), SIMDE_FLOAT64_C(   465.62) },
      UINT8_C(192) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   909.54), SIMDE_FLOAT64_C(  -736.00),
        SIMDE_FLOAT64_C(   199.77), SIMDE_FLOAT64_C(    25.69), SIMDE_FLOAT64_C(  -918.86), SIMDE_FLOAT64_C(   445.08) },
      { SIMDE_FLOAT64_C(    18.15),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -736.00),
        SIMDE_FLOAT64_C(   199.77), SIMDE_FLOAT64_C(    25.69), SIMDE_FLOAT64_C(   414.09), SIMDE_FLOAT64_C(  -168.83) },
      UINT8_C(120) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   115.76), SIMDE_FLOAT64_C(   297.19),
        SIMDE_FLOAT64_C(   182.95), SIMDE_FLOAT64_C(   999.92), SIMDE_FLOAT64_C(  -793.92), SIMDE_FLOAT64_C(   244.87) },
      { SIMDE_FLOAT64_C(   246.47),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   297.19),
        SIMDE_FLOAT64_C(   182.95), SIMDE_FLOAT64_C(   999.92), SIMDE_FLOAT64_C(  -793.92), SIMDE_FLOAT64_C(   244.87) },
      UINT8_C(  7) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   620.11), SIMDE_FLOAT64_C(  -536.66),
        SIMDE_FLOAT64_C(   379.23), SIMDE_FLOAT64_C(  -361.74), SIMDE_FLOAT64_C(   -19.88), SIMDE_FLOAT64_C(  -442.41) },
      { SIMDE_FLOAT64_C(  -617.80),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   546.32),
        SIMDE_FLOAT64_C(  -710.33), SIMDE_FLOAT64_C(  -361.74), SIMDE_FLOAT64_C(  -207.21), SIMDE_FLOAT64_C(   101.87) },
      UINT8_C(223) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   531.11), SIMDE_FLOAT64_C(  -703.94),
        SIMDE_FLOAT64_C(   529.69), SIMDE_FLOAT64_C(   342.14), SIMDE_FLOAT64_C(   -70.08), SIMDE_FLOAT64_C(  -491.13) },
      { SIMDE_FLOAT64_C(  -910.02),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -234.39),
        SIMDE_FLOAT64_C(   763.77), SIMDE_FLOAT64_C(   342.14), SIMDE_FLOAT64_C(   147.82), SIMDE_FLOAT64_C(   697.92) },
      UINT8_C( 39) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -953.47), SIMDE_FLOAT64_C(  -408.73),
        SIMDE_FLOAT64_C(   634.74), SIMDE_FLOAT64_C(  -821.24), SIMDE_FLOAT64_C(  -950.23), SIMDE_FLOAT64_C(   773.91) },
      { SIMDE_FLOAT64_C(   611.16),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -408.73),
        SIMDE_FLOAT64_C(   634.74), SIMDE_FLOAT64_C(   720.53), SIMDE_FLOAT64_C(  -392.15), SIMDE_FLOAT64_C(   726.12) },
      UINT8_C(135) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -406.22), SIMDE_FLOAT64_C(   833.83),
        SIMDE_FLOAT64_C(   764.68), SIMDE_FLOAT64_C(   241.19), SIMDE_FLOAT64_C(  -136.78), SIMDE_FLOAT64_C(   -41.57) },
      { SIMDE_FLOAT64_C(   -96.09),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   833.83),
        SIMDE_FLOAT64_C(   764.68), SIMDE_FLOAT64_C(   241.19), SIMDE_FLOAT64_C(  -136.78), SIMDE_FLOAT64_C(   -41.57) },
      UINT8_C(248) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -619.84), SIMDE_FLOAT64_C(   406.81),
        SIMDE_FLOAT64_C(  -189.28), SIMDE_FLOAT64_C(  -894.75), SIMDE_FLOAT64_C(   746.25), SIMDE_FLOAT64_C(     0.07) },
      { SIMDE_FLOAT64_C(   357.05),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   230.97),
        SIMDE_FLOAT64_C(   -86.33), SIMDE_FLOAT64_C(  -894.75), SIMDE_FLOAT64_C(  -865.12), SIMDE_FLOAT64_C(     0.07) },
      UINT8_C(167) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   807.21), SIMDE_FLOAT64_C(  -168.08),
        SIMDE_FLOAT64_C(  -107.40), SIMDE_FLOAT64_C(   814.01), SIMDE_FLOAT64_C(   458.92), SIMDE_FLOAT64_C(   639.19) },
      { SIMDE_FLOAT64_C(   968.70),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -168.08),
        SIMDE_FLOAT64_C(   185.90), SIMDE_FLOAT64_C(   814.01), SIMDE_FLOAT64_C(   458.92), SIMDE_FLOAT64_C(  -777.29) },
      UINT8_C( 23) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -519.12), SIMDE_FLOAT64_C(  -755.49),
        SIMDE_FLOAT64_C(  -966.51), SIMDE_FLOAT64_C(   103.99), SIMDE_FLOAT64_C(   432.06), SIMDE_FLOAT64_C(  -245.91) },
      { SIMDE_FLOAT64_C(  -501.73),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -530.16),
        SIMDE_FLOAT64_C(  -484.78), SIMDE_FLOAT64_C(   103.99), SIMDE_FLOAT64_C(   432.06), SIMDE_FLOAT64_C(  -245.91) },
         UINT8_MAX },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   -86.42), SIMDE_FLOAT64_C(  -270.62),
        SIMDE_FLOAT64_C(   -18.83), SIMDE_FLOAT64_C(   882.21), SIMDE_FLOAT64_C(  -486.79), SIMDE_FLOAT64_C(  -224.76) },
      { SIMDE_FLOAT64_C(   270.46),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -291.93),
        SIMDE_FLOAT64_C(   921.81), SIMDE_FLOAT64_C(   146.33), SIMDE_FLOAT64_C(   206.33), SIMDE_FLOAT64_C(   -44.76) },
      UINT8_C(  0) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -268.80), SIMDE_FLOAT64_C(  -117.09),
        SIMDE_FLOAT64_C(   742.83), SIMDE_FLOAT64_C(    66.16), SIMDE_FLOAT64_C(   228.64), SIMDE_FLOAT64_C(  -530.84) },
      { SIMDE_FLOAT64_C(   450.85),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -117.09),
        SIMDE_FLOAT64_C(  -806.76), SIMDE_FLOAT64_C(    66.16), SIMDE_FLOAT64_C(   228.64), SIMDE_FLOAT64_C(  -530.84) },
      UINT8_C( 16) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   656.88), SIMDE_FLOAT64_C(  -512.41),
        SIMDE_FLOAT64_C(   291.63), SIMDE_FLOAT64_C(   273.49), SIMDE_FLOAT64_C(  -813.30), SIMDE_FLOAT64_C(  -937.66) },
      { SIMDE_FLOAT64_C(   974.38),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -512.41),
        SIMDE_FLOAT64_C(    63.76), SIMDE_FLOAT64_C(   273.49), SIMDE_FLOAT64_C(  -813.30), SIMDE_FLOAT64_C(  -937.66) },
      UINT8_C(248) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -366.75), SIMDE_FLOAT64_C(  -249.71),
        SIMDE_FLOAT64_C(  -735.51), SIMDE_FLOAT64_C(  -830.75), SIMDE_FLOAT64_C(  -505.85), SIMDE_FLOAT64_C(  -973.99) },
      { SIMDE_FLOAT64_C(   521.64),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -249.71),
        SIMDE_FLOAT64_C(  -777.38), SIMDE_FLOAT64_C(  -830.75), SIMDE_FLOAT64_C(  -505.85), SIMDE_FLOAT64_C(  -973.99) },
      UINT8_C( 16) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   592.13), SIMDE_FLOAT64_C(  -962.54),
        SIMDE_FLOAT64_C(  -907.01), SIMDE_FLOAT64_C(   573.68), SIMDE_FLOAT64_C(  -854.03), SIMDE_FLOAT64_C(   301.66) },
      { SIMDE_FLOAT64_C(   850.76),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -962.54),
        SIMDE_FLOAT64_C(  -907.01), SIMDE_FLOAT64_C(   704.63), SIMDE_FLOAT64_C(  -854.03), SIMDE_FLOAT64_C(    57.54) },
         UINT8_MAX },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -492.87), SIMDE_FLOAT64_C(  -833.61),
        SIMDE_FLOAT64_C(   348.03), SIMDE_FLOAT64_C(  -349.08), SIMDE_FLOAT64_C(  -146.21), SIMDE_FLOAT64_C(  -764.87) },
      { SIMDE_FLOAT64_C(   672.24),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   402.87),
        SIMDE_FLOAT64_C(   348.03), SIMDE_FLOAT64_C(  -349.08), SIMDE_FLOAT64_C(  -146.21), SIMDE_FLOAT64_C(   846.07) },
      UINT8_C(112) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -618.67), SIMDE_FLOAT64_C(   437.06),
        SIMDE_FLOAT64_C(   240.71), SIMDE_FLOAT64_C(   142.91), SIMDE_FLOAT64_C(  -353.22), SIMDE_FLOAT64_C(   378.25) },
      { SIMDE_FLOAT64_C(  -456.78),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   437.06),
        SIMDE_FLOAT64_C(   -33.46), SIMDE_FLOAT64_C(   142.91), SIMDE_FLOAT64_C(  -353.22), SIMDE_FLOAT64_C(  -711.43) },
      UINT8_C(  0) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -421.19), SIMDE_FLOAT64_C(  -842.41),
        SIMDE_FLOAT64_C(   871.73), SIMDE_FLOAT64_C(  -381.48), SIMDE_FLOAT64_C(   233.99), SIMDE_FLOAT64_C(  -231.39) },
      { SIMDE_FLOAT64_C(  -978.61),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -842.41),
        SIMDE_FLOAT64_C(   871.73), SIMDE_FLOAT64_C(  -208.21), SIMDE_FLOAT64_C(   233.99), SIMDE_FLOAT64_C(  -165.46) },
      UINT8_C(248) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -683.97), SIMDE_FLOAT64_C(  -350.05),
        SIMDE_FLOAT64_C(   453.51), SIMDE_FLOAT64_C(  -140.76), SIMDE_FLOAT64_C(  -441.05), SIMDE_FLOAT64_C(  -463.61) },
      { SIMDE_FLOAT64_C(  -996.84),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -350.05),
        SIMDE_FLOAT64_C(   453.51), SIMDE_FLOAT64_C(   885.04), SIMDE_FLOAT64_C(  -441.05), SIMDE_FLOAT64_C(  -463.61) },
      UINT8_C(  7) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(    82.37), SIMDE_FLOAT64_C(  -842.79),
        SIMDE_FLOAT64_C(  -909.01), SIMDE_FLOAT64_C(   103.76), SIMDE_FLOAT64_C(   206.62), SIMDE_FLOAT64_C(  -924.87) },
      { SIMDE_FLOAT64_C(   -76.79),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -842.79),
        SIMDE_FLOAT64_C(   -63.35), SIMDE_FLOAT64_C(  -959.96), SIMDE_FLOAT64_C(   -51.94), SIMDE_FLOAT64_C(    11.90) },
      UINT8_C(247) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   215.31), SIMDE_FLOAT64_C(  -843.05),
        SIMDE_FLOAT64_C(     1.80), SIMDE_FLOAT64_C(   539.72), SIMDE_FLOAT64_C(   682.44), SIMDE_FLOAT64_C(   -41.04) },
      { SIMDE_FLOAT64_C(     1.54),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -843.05),
        SIMDE_FLOAT64_C(   -52.86), SIMDE_FLOAT64_C(   307.85), SIMDE_FLOAT64_C(  -309.63), SIMDE_FLOAT64_C(   -41.04) },
         UINT8_MAX },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   493.99), SIMDE_FLOAT64_C(  -945.81),
        SIMDE_FLOAT64_C(  -564.35), SIMDE_FLOAT64_C(   872.77), SIMDE_FLOAT64_C(  -843.70), SIMDE_FLOAT64_C(   302.56) },
      { SIMDE_FLOAT64_C(  -152.43),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -945.81),
        SIMDE_FLOAT64_C(  -564.35), SIMDE_FLOAT64_C(   698.66), SIMDE_FLOAT64_C(  -843.70), SIMDE_FLOAT64_C(  -429.75) },
      UINT8_C(167) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -546.31), SIMDE_FLOAT64_C(   203.11),
        SIMDE_FLOAT64_C(  -468.99), SIMDE_FLOAT64_C(   455.23), SIMDE_FLOAT64_C(  -300.40), SIMDE_FLOAT64_C(   375.01) },
      { SIMDE_FLOAT64_C(   520.68),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   203.11),
        SIMDE_FLOAT64_C(   916.26), SIMDE_FLOAT64_C(    73.09), SIMDE_FLOAT64_C(  -300.40), SIMDE_FLOAT64_C(  -723.22) },
      UINT8_C(248) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -560.14), SIMDE_FLOAT64_C(   -29.18),
        SIMDE_FLOAT64_C(  -985.01), SIMDE_FLOAT64_C(   257.53), SIMDE_FLOAT64_C(  -936.23), SIMDE_FLOAT64_C(   357.59) },
      { SIMDE_FLOAT64_C(  -185.48),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -613.02),
        SIMDE_FLOAT64_C(  -985.01), SIMDE_FLOAT64_C(   970.22), SIMDE_FLOAT64_C(   907.65), SIMDE_FLOAT64_C(   357.59) },
      UINT8_C(151) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   879.14), SIMDE_FLOAT64_C(   810.37),
        SIMDE_FLOAT64_C(  -783.06), SIMDE_FLOAT64_C(   101.52), SIMDE_FLOAT64_C(   457.11), SIMDE_FLOAT64_C(  -100.19) },
      { SIMDE_FLOAT64_C(    14.28),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   774.61),
        SIMDE_FLOAT64_C(   650.15), SIMDE_FLOAT64_C(   101.52), SIMDE_FLOAT64_C(   457.11), SIMDE_FLOAT64_C(  -100.19) },
      UINT8_C( 23) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -762.63), SIMDE_FLOAT64_C(   623.72),
        SIMDE_FLOAT64_C(   735.15), SIMDE_FLOAT64_C(   260.62), SIMDE_FLOAT64_C(   792.33), SIMDE_FLOAT64_C(  -208.60) },
      { SIMDE_FLOAT64_C(   559.95),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   623.72),
        SIMDE_FLOAT64_C(  -157.88), SIMDE_FLOAT64_C(   260.62), SIMDE_FLOAT64_C(   792.33), SIMDE_FLOAT64_C(  -208.60) },
      UINT8_C(239) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -833.81), SIMDE_FLOAT64_C(   933.49),
        SIMDE_FLOAT64_C(  -199.20), SIMDE_FLOAT64_C(   180.47), SIMDE_FLOAT64_C(   306.86), SIMDE_FLOAT64_C(  -226.30) },
      { SIMDE_FLOAT64_C(   -44.92),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   933.49),
        SIMDE_FLOAT64_C(   319.59), SIMDE_FLOAT64_C(  -706.47), SIMDE_FLOAT64_C(   306.86), SIMDE_FLOAT64_C(   697.16) },
      UINT8_C(  0) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   791.52), SIMDE_FLOAT64_C(  -479.80),
        SIMDE_FLOAT64_C(  -776.29), SIMDE_FLOAT64_C(   439.12), SIMDE_FLOAT64_C(    51.40), SIMDE_FLOAT64_C(   -14.66) },
      { SIMDE_FLOAT64_C(    -5.64),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   660.38),
        SIMDE_FLOAT64_C(  -776.29), SIMDE_FLOAT64_C(   235.54), SIMDE_FLOAT64_C(  -863.24), SIMDE_FLOAT64_C(   -14.66) },
      UINT8_C(104) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -417.79), SIMDE_FLOAT64_C(   377.11),
        SIMDE_FLOAT64_C(    53.06), SIMDE_FLOAT64_C(   537.28), SIMDE_FLOAT64_C(  -665.88), SIMDE_FLOAT64_C(  -633.25) },
      { SIMDE_FLOAT64_C(    81.49),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   377.11),
        SIMDE_FLOAT64_C(    53.06), SIMDE_FLOAT64_C(   537.28), SIMDE_FLOAT64_C(  -665.88), SIMDE_FLOAT64_C(  -633.25) },
      UINT8_C(248) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(  -578.18), SIMDE_FLOAT64_C(  -514.88),
        SIMDE_FLOAT64_C(   992.23), SIMDE_FLOAT64_C(   416.19), SIMDE_FLOAT64_C(  -621.37), SIMDE_FLOAT64_C(  -836.90) },
      { SIMDE_FLOAT64_C(   433.72),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   213.32),
        SIMDE_FLOAT64_C(   434.75), SIMDE_FLOAT64_C(   416.19), SIMDE_FLOAT64_C(  -621.37), SIMDE_FLOAT64_C(  -836.90) },
      UINT8_C( 16) },
    { {             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(   -80.13), SIMDE_FLOAT64_C(    -5.20),
        SIMDE_FLOAT64_C(   133.92), SIMDE_FLOAT64_C(  -998.64), SIMDE_FLOAT64_C(  -351.49), SIMDE_FLOAT64_C(   794.21) },
      { SIMDE_FLOAT64_C(  -813.00),             SIMDE_MATH_NAN,             SIMDE_MATH_NAN, SIMDE_FLOAT64_C(    -5.20),
        SIMDE_FLOAT64_C(  -217.42), SIMDE_FLOAT64_C(   968.11), SIMDE_FLOAT64_C(  -465.77), SIMDE_FLOAT64_C(   789.48) },
         UINT8_MAX }
  };

  simde__m512d a, b;
  simde__mmask8 r;

  a = simde_mm512_loadu_pd(test_vec[0].a);
  b = simde_mm512_loadu_pd(test_vec[0].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask8(r, test_vec[0].r);

  a = simde_mm512_loadu_pd(test_vec[1].a);
  b = simde_mm512_loadu_pd(test_vec[1].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask8(r, test_vec[1].r);

  a = simde_mm512_loadu_pd(test_vec[2].a);
  b = simde_mm512_loadu_pd(test_vec[2].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask8(r, test_vec[2].r);

  a = simde_mm512_loadu_pd(test_vec[3].a);
  b = simde_mm512_loadu_pd(test_vec[3].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask8(r, test_vec[3].r);

  a = simde_mm512_loadu_pd(test_vec[4].a);
  b = simde_mm512_loadu_pd(test_vec[4].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask8(r, test_vec[4].r);

  a = simde_mm512_loadu_pd(test_vec[5].a);
  b = simde_mm512_loadu_pd(test_vec[5].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask8(r, test_vec[5].r);

  a = simde_mm512_loadu_pd(test_vec[6].a);
  b = simde_mm512_loadu_pd(test_vec[6].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask8(r, test_vec[6].r);

  a = simde_mm512_loadu_pd(test_vec[7].a);
  b = simde_mm512_loadu_pd(test_vec[7].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask8(r, test_vec[7].r);

  a = simde_mm512_loadu_pd(test_vec[8].a);
  b = simde_mm512_loadu_pd(test_vec[8].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask8(r, test_vec[8].r);

  a = simde_mm512_loadu_pd(test_vec[9].a);
  b = simde_mm512_loadu_pd(test_vec[9].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask8(r, test_vec[9].r);

  a = simde_mm512_loadu_pd(test_vec[10].a);
  b = simde_mm512_loadu_pd(test_vec[10].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask8(r, test_vec[10].r);

  a = simde_mm512_loadu_pd(test_vec[11].a);
  b = simde_mm512_loadu_pd(test_vec[11].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask8(r, test_vec[11].r);

  a = simde_mm512_loadu_pd(test_vec[12].a);
  b = simde_mm512_loadu_pd(test_vec[12].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask8(r, test_vec[12].r);

  a = simde_mm512_loadu_pd(test_vec[13].a);
  b = simde_mm512_loadu_pd(test_vec[13].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask8(r, test_vec[13].r);

  a = simde_mm512_loadu_pd(test_vec[14].a);
  b = simde_mm512_loadu_pd(test_vec[14].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask8(r, test_vec[14].r);

  a = simde_mm512_loadu_pd(test_vec[15].a);
  b = simde_mm512_loadu_pd(test_vec[15].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask8(r, test_vec[15].r);

  a = simde_mm512_loadu_pd(test_vec[16].a);
  b = simde_mm512_loadu_pd(test_vec[16].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask8(r, test_vec[16].r);

  a = simde_mm512_loadu_pd(test_vec[17].a);
  b = simde_mm512_loadu_pd(test_vec[17].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask8(r, test_vec[17].r);

  a = simde_mm512_loadu_pd(test_vec[18].a);
  b = simde_mm512_loadu_pd(test_vec[18].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask8(r, test_vec[18].r);

  a = simde_mm512_loadu_pd(test_vec[19].a);
  b = simde_mm512_loadu_pd(test_vec[19].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask8(r, test_vec[19].r);

  a = simde_mm512_loadu_pd(test_vec[20].a);
  b = simde_mm512_loadu_pd(test_vec[20].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask8(r, test_vec[20].r);

  a = simde_mm512_loadu_pd(test_vec[21].a);
  b = simde_mm512_loadu_pd(test_vec[21].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask8(r, test_vec[21].r);

  a = simde_mm512_loadu_pd(test_vec[22].a);
  b = simde_mm512_loadu_pd(test_vec[22].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask8(r, test_vec[22].r);

  a = simde_mm512_loadu_pd(test_vec[23].a);
  b = simde_mm512_loadu_pd(test_vec[23].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask8(r, test_vec[23].r);

  a = simde_mm512_loadu_pd(test_vec[24].a);
  b = simde_mm512_loadu_pd(test_vec[24].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask8(r, test_vec[24].r);

  a = simde_mm512_loadu_pd(test_vec[25].a);
  b = simde_mm512_loadu_pd(test_vec[25].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask8(r, test_vec[25].r);

  a = simde_mm512_loadu_pd(test_vec[26].a);
  b = simde_mm512_loadu_pd(test_vec[26].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask8(r, test_vec[26].r);

  a = simde_mm512_loadu_pd(test_vec[27].a);
  b = simde_mm512_loadu_pd(test_vec[27].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask8(r, test_vec[27].r);

  a = simde_mm512_loadu_pd(test_vec[28].a);
  b = simde_mm512_loadu_pd(test_vec[28].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask8(r, test_vec[28].r);

  a = simde_mm512_loadu_pd(test_vec[29].a);
  b = simde_mm512_loadu_pd(test_vec[29].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask8(r, test_vec[29].r);

  a = simde_mm512_loadu_pd(test_vec[30].a);
  b = simde_mm512_loadu_pd(test_vec[30].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask8(r, test_vec[30].r);

  a = simde_mm512_loadu_pd(test_vec[31].a);
  b = simde_mm512_loadu_pd(test_vec[31].b);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask8(r, test_vec[31].r);

  return 0;
#else
  fputc('\n', stdout);

  const simde__m512d nanv = simde_mm512_set1_pd(SIMDE_MATH_NAN);

  simde__m512d a, b;
  simde__mmask8 r;

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LT_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LE_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLT_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLE_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGE_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGT_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GE_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GT_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_ORD_S);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_EQ_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  a = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_test_x86_random_f64x8(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
  b = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, simde_test_codegen_random_i8()), b);
  a = simde_mm512_mask_mov_pd(a, HEDLEY_STATIC_CAST(simde__mmask8, 3), nanv);
  b = simde_mm512_mask_mov_pd(b, HEDLEY_STATIC_CAST(simde__mmask8, 6), nanv);
  r = simde_mm512_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_test_x86_write_f64x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
  simde_test_x86_write_f64x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
  simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);

  return 1;
#endif
}

static int
test_simde_mm256_cmp_pd_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  simde__m256d a, b;
  simde__mmask8 e, r;

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -361.78), SIMDE_FLOAT64_C(  -782.43), SIMDE_FLOAT64_C(   565.22), SIMDE_FLOAT64_C(  -605.46));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -817.89), SIMDE_FLOAT64_C(   388.46), SIMDE_FLOAT64_C(   192.48), SIMDE_FLOAT64_C(  -823.37));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   449.02), SIMDE_FLOAT64_C(   932.44), SIMDE_FLOAT64_C(  -896.45), SIMDE_FLOAT64_C(  -692.22));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(    84.76), SIMDE_FLOAT64_C(   721.33), SIMDE_FLOAT64_C(  -362.73), SIMDE_FLOAT64_C(    95.31));
  e = UINT8_C(  3);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -934.37), SIMDE_FLOAT64_C(  -274.54), SIMDE_FLOAT64_C(  -432.69), SIMDE_FLOAT64_C(    16.07));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   189.77), SIMDE_FLOAT64_C(   111.61), SIMDE_FLOAT64_C(  -686.48), SIMDE_FLOAT64_C(  -806.43));
  e = UINT8_C( 12);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   800.99), SIMDE_FLOAT64_C(  -702.50), SIMDE_FLOAT64_C(  -566.68), SIMDE_FLOAT64_C(   451.34));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   871.85), SIMDE_FLOAT64_C(   216.92), SIMDE_FLOAT64_C(  -251.00), SIMDE_FLOAT64_C(   477.31));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -509.15), SIMDE_FLOAT64_C(  -489.92), SIMDE_FLOAT64_C(   434.49), SIMDE_FLOAT64_C(  -685.79));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   -65.25), SIMDE_FLOAT64_C(  -327.04), SIMDE_FLOAT64_C(   898.54), SIMDE_FLOAT64_C(  -373.03));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(    97.40), SIMDE_FLOAT64_C(  -616.22), SIMDE_FLOAT64_C(  -394.60), SIMDE_FLOAT64_C(  -997.91));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -741.26), SIMDE_FLOAT64_C(  -817.83), SIMDE_FLOAT64_C(  -894.89), SIMDE_FLOAT64_C(   242.67));
  e = UINT8_C( 14);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -134.02), SIMDE_FLOAT64_C(  -675.63), SIMDE_FLOAT64_C(   -92.37), SIMDE_FLOAT64_C(  -327.58));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -327.52), SIMDE_FLOAT64_C(  -944.25), SIMDE_FLOAT64_C(   435.98), SIMDE_FLOAT64_C(   221.14));
  e = UINT8_C( 12);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   346.61), SIMDE_FLOAT64_C(  -526.53), SIMDE_FLOAT64_C(  -646.75), SIMDE_FLOAT64_C(   869.29));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   416.47), SIMDE_FLOAT64_C(   218.46), SIMDE_FLOAT64_C(   690.39), SIMDE_FLOAT64_C(   102.25));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   751.86), SIMDE_FLOAT64_C(   907.32), SIMDE_FLOAT64_C(   728.54), SIMDE_FLOAT64_C(   124.89));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   629.16), SIMDE_FLOAT64_C(  -313.39), SIMDE_FLOAT64_C(  -419.73), SIMDE_FLOAT64_C(   627.08));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -571.66), SIMDE_FLOAT64_C(  -273.43), SIMDE_FLOAT64_C(    70.39), SIMDE_FLOAT64_C(   185.67));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   847.91), SIMDE_FLOAT64_C(  -312.92), SIMDE_FLOAT64_C(   -91.27), SIMDE_FLOAT64_C(   175.49));
  e = UINT8_C(  8);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(    37.50), SIMDE_FLOAT64_C(  -286.11), SIMDE_FLOAT64_C(    11.45), SIMDE_FLOAT64_C(   816.36));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -683.28), SIMDE_FLOAT64_C(   709.98), SIMDE_FLOAT64_C(  -230.35), SIMDE_FLOAT64_C(  -552.58));
  e = UINT8_C(  4);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -774.85), SIMDE_FLOAT64_C(   663.33), SIMDE_FLOAT64_C(  -816.55), SIMDE_FLOAT64_C(   122.90));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(    -1.27), SIMDE_FLOAT64_C(   641.62), SIMDE_FLOAT64_C(  -118.21), SIMDE_FLOAT64_C(   873.85));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -762.59), SIMDE_FLOAT64_C(  -249.41), SIMDE_FLOAT64_C(   548.94), SIMDE_FLOAT64_C(  -389.67));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   314.88), SIMDE_FLOAT64_C(   866.57), SIMDE_FLOAT64_C(   437.20), SIMDE_FLOAT64_C(  -870.79));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   683.08), SIMDE_FLOAT64_C(   743.22), SIMDE_FLOAT64_C(  -406.86), SIMDE_FLOAT64_C(  -492.41));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   318.23), SIMDE_FLOAT64_C(   530.99), SIMDE_FLOAT64_C(  -569.70), SIMDE_FLOAT64_C(   501.87));
  e = UINT8_C( 14);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   889.17), SIMDE_FLOAT64_C(  -644.27), SIMDE_FLOAT64_C(  -755.12), SIMDE_FLOAT64_C(   441.75));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -862.57), SIMDE_FLOAT64_C(  -794.11), SIMDE_FLOAT64_C(  -934.28), SIMDE_FLOAT64_C(    14.53));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -876.98), SIMDE_FLOAT64_C(  -637.41), SIMDE_FLOAT64_C(   869.21), SIMDE_FLOAT64_C(  -750.83));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   361.33), SIMDE_FLOAT64_C(   121.75), SIMDE_FLOAT64_C(  -995.79), SIMDE_FLOAT64_C(  -249.00));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   682.35), SIMDE_FLOAT64_C(   598.74), SIMDE_FLOAT64_C(   872.34), SIMDE_FLOAT64_C(   553.14));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   817.13), SIMDE_FLOAT64_C(    -2.77), SIMDE_FLOAT64_C(   465.31), SIMDE_FLOAT64_C(   309.54));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   560.32), SIMDE_FLOAT64_C(   500.20), SIMDE_FLOAT64_C(  -259.55), SIMDE_FLOAT64_C(  -941.55));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -387.50), SIMDE_FLOAT64_C(  -121.45), SIMDE_FLOAT64_C(    31.19), SIMDE_FLOAT64_C(   170.76));
  e = UINT8_C(  3);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -709.40), SIMDE_FLOAT64_C(  -498.32), SIMDE_FLOAT64_C(   234.28), SIMDE_FLOAT64_C(   276.07));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   549.17), SIMDE_FLOAT64_C(  -571.97), SIMDE_FLOAT64_C(  -292.44), SIMDE_FLOAT64_C(   300.00));
  e = UINT8_C(  9);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   327.78), SIMDE_FLOAT64_C(   672.18), SIMDE_FLOAT64_C(  -209.38), SIMDE_FLOAT64_C(  -423.22));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -652.03), SIMDE_FLOAT64_C(  -310.88), SIMDE_FLOAT64_C(  -206.06), SIMDE_FLOAT64_C(  -205.17));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   975.82), SIMDE_FLOAT64_C(  -969.67), SIMDE_FLOAT64_C(  -712.14), SIMDE_FLOAT64_C(  -333.72));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   811.62), SIMDE_FLOAT64_C(   792.94), SIMDE_FLOAT64_C(    27.56), SIMDE_FLOAT64_C(   753.17));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   -61.23), SIMDE_FLOAT64_C(   371.94), SIMDE_FLOAT64_C(   293.15), SIMDE_FLOAT64_C(   768.01));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   600.41), SIMDE_FLOAT64_C(   551.28), SIMDE_FLOAT64_C(  -749.51), SIMDE_FLOAT64_C(  -675.66));
  e = UINT8_C(  3);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -215.23), SIMDE_FLOAT64_C(   891.02), SIMDE_FLOAT64_C(  -947.05), SIMDE_FLOAT64_C(   484.78));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   337.30), SIMDE_FLOAT64_C(  -666.06), SIMDE_FLOAT64_C(  -680.95), SIMDE_FLOAT64_C(  -239.48));
  e = UINT8_C(  5);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   904.50), SIMDE_FLOAT64_C(  -334.92), SIMDE_FLOAT64_C(  -993.88), SIMDE_FLOAT64_C(   109.67));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   466.34), SIMDE_FLOAT64_C(  -747.53), SIMDE_FLOAT64_C(   354.20), SIMDE_FLOAT64_C(  -199.94));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   395.23), SIMDE_FLOAT64_C(   442.16), SIMDE_FLOAT64_C(  -717.20), SIMDE_FLOAT64_C(   642.06));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(    78.37), SIMDE_FLOAT64_C(   206.85), SIMDE_FLOAT64_C(   235.10), SIMDE_FLOAT64_C(   310.36));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -147.41), SIMDE_FLOAT64_C(  -982.86), SIMDE_FLOAT64_C(  -421.21), SIMDE_FLOAT64_C(  -471.75));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -685.94), SIMDE_FLOAT64_C(  -547.00), SIMDE_FLOAT64_C(   568.42), SIMDE_FLOAT64_C(  -170.72));
  e = UINT8_C(  7);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -618.11), SIMDE_FLOAT64_C(    98.83), SIMDE_FLOAT64_C(  -655.98), SIMDE_FLOAT64_C(   621.37));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   772.73), SIMDE_FLOAT64_C(   719.18), SIMDE_FLOAT64_C(   432.77), SIMDE_FLOAT64_C(  -336.93));
  e = UINT8_C( 14);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -761.04), SIMDE_FLOAT64_C(   677.23), SIMDE_FLOAT64_C(  -615.74), SIMDE_FLOAT64_C(   438.90));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   380.52), SIMDE_FLOAT64_C(   705.30), SIMDE_FLOAT64_C(   929.70), SIMDE_FLOAT64_C(   738.46));
  e = UINT8_C(  0);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   522.86), SIMDE_FLOAT64_C(  -224.25), SIMDE_FLOAT64_C(   147.45), SIMDE_FLOAT64_C(  -787.50));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   -89.20), SIMDE_FLOAT64_C(  -398.77), SIMDE_FLOAT64_C(   982.60), SIMDE_FLOAT64_C(  -617.45));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   390.67), SIMDE_FLOAT64_C(   763.39), SIMDE_FLOAT64_C(  -381.63), SIMDE_FLOAT64_C(  -438.61));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   808.16), SIMDE_FLOAT64_C(   704.73), SIMDE_FLOAT64_C(  -783.61), SIMDE_FLOAT64_C(  -813.21));
  e = UINT8_C(  7);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   223.47), SIMDE_FLOAT64_C(  -809.95), SIMDE_FLOAT64_C(  -196.44), SIMDE_FLOAT64_C(  -439.59));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(   675.23), SIMDE_FLOAT64_C(    -3.79), SIMDE_FLOAT64_C(   909.23), SIMDE_FLOAT64_C(  -763.67));
  e = UINT8_C(  1);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm256_set_pd(SIMDE_FLOAT64_C(   745.29), SIMDE_FLOAT64_C(   -67.43), SIMDE_FLOAT64_C(   881.20), SIMDE_FLOAT64_C(  -400.21));
  b = simde_mm256_set_pd(SIMDE_FLOAT64_C(  -531.86), SIMDE_FLOAT64_C(   270.12), SIMDE_FLOAT64_C(  -338.86), SIMDE_FLOAT64_C(  -396.43));
  e = UINT8_C( 15);
  r = simde_mm256_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask8(r, e);

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 32 ; i++) {
    simde__m256d a = simde_test_x86_random_f64x4(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m256d b = simde_test_x86_random_f64x4(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    int imm8 = i;
    simde__mmask8 r;
    SIMDE_CONSTIFY_32_(simde_mm256_cmp_pd_mask, r, (HEDLEY_UNREACHABLE(), 0), imm8, a, b);

    simde_test_x86_write_f64x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_codegen_write_i32(2, imm8, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_cmp_pd_mask (SIMDE_MUNIT_TEST_ARGS) {
#if 1
  simde__m128d a, b;
  simde__mmask8 e, r;

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -268.92), SIMDE_FLOAT64_C(   479.50));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   858.92), SIMDE_FLOAT64_C(   796.74));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   179.01), SIMDE_FLOAT64_C(   424.90));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   764.21), SIMDE_FLOAT64_C(   456.52));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_LT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   527.46), SIMDE_FLOAT64_C(   265.30));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   962.27), SIMDE_FLOAT64_C(   934.34));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_LE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -837.53), SIMDE_FLOAT64_C(   652.18));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -597.24), SIMDE_FLOAT64_C(  -275.58));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -812.88), SIMDE_FLOAT64_C(   580.18));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   -89.82), SIMDE_FLOAT64_C(  -178.32));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -714.89), SIMDE_FLOAT64_C(   539.45));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -165.89), SIMDE_FLOAT64_C(   628.17));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NLT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   -58.11), SIMDE_FLOAT64_C(  -458.02));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   947.44), SIMDE_FLOAT64_C(  -465.97));
  e = UINT8_C(  1);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NLE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   343.16), SIMDE_FLOAT64_C(  -778.20));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   701.30), SIMDE_FLOAT64_C(  -788.98));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_ORD_Q);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -992.25), SIMDE_FLOAT64_C(  -925.76));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   499.14), SIMDE_FLOAT64_C(   560.22));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_EQ_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(    16.74), SIMDE_FLOAT64_C(   186.76));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -547.94), SIMDE_FLOAT64_C(   263.35));
  e = UINT8_C(  1);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NGE_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   197.69), SIMDE_FLOAT64_C(  -455.80));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -803.62), SIMDE_FLOAT64_C(  -585.67));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NGT_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   138.75), SIMDE_FLOAT64_C(   360.16));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   -59.66), SIMDE_FLOAT64_C(  -400.86));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   420.82), SIMDE_FLOAT64_C(   325.87));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -134.67), SIMDE_FLOAT64_C(   850.52));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   478.68), SIMDE_FLOAT64_C(   705.93));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -752.09), SIMDE_FLOAT64_C(   699.44));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_GE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -766.53), SIMDE_FLOAT64_C(  -579.43));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -357.63), SIMDE_FLOAT64_C(  -804.65));
  e = UINT8_C(  1);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_GT_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -593.64), SIMDE_FLOAT64_C(   576.63));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   650.88), SIMDE_FLOAT64_C(  -656.34));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   903.88), SIMDE_FLOAT64_C(  -585.88));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   600.88), SIMDE_FLOAT64_C(   150.01));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_EQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -586.64), SIMDE_FLOAT64_C(   -79.38));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   464.82), SIMDE_FLOAT64_C(  -947.06));
  e = UINT8_C(  2);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_LT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -532.73), SIMDE_FLOAT64_C(   611.05));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   -28.79), SIMDE_FLOAT64_C(   661.20));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_LE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -739.66), SIMDE_FLOAT64_C(   606.02));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   -68.11), SIMDE_FLOAT64_C(   911.55));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_UNORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   762.06), SIMDE_FLOAT64_C(   681.16));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   387.09), SIMDE_FLOAT64_C(   797.22));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   496.66), SIMDE_FLOAT64_C(   240.75));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   661.32), SIMDE_FLOAT64_C(   635.00));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NLT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   830.35), SIMDE_FLOAT64_C(   730.12));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   306.75), SIMDE_FLOAT64_C(  -696.31));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NLE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -352.65), SIMDE_FLOAT64_C(  -763.29));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -349.17), SIMDE_FLOAT64_C(   -42.37));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_ORD_S);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -892.36), SIMDE_FLOAT64_C(  -448.77));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   471.85), SIMDE_FLOAT64_C(  -748.29));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_EQ_US);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -695.35), SIMDE_FLOAT64_C(  -478.99));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -867.94), SIMDE_FLOAT64_C(   -63.32));
  e = UINT8_C(  1);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NGE_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -402.12), SIMDE_FLOAT64_C(  -228.09));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -622.07), SIMDE_FLOAT64_C(   103.27));
  e = UINT8_C(  1);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NGT_UQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(    14.82), SIMDE_FLOAT64_C(  -141.78));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -460.62), SIMDE_FLOAT64_C(   309.83));
  e = UINT8_C(  0);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_FALSE_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   107.05), SIMDE_FLOAT64_C(  -223.11));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -982.36), SIMDE_FLOAT64_C(   926.47));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_NEQ_OS);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   561.47), SIMDE_FLOAT64_C(  -396.30));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(  -666.17), SIMDE_FLOAT64_C(   678.95));
  e = UINT8_C(  2);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_GE_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(   982.64), SIMDE_FLOAT64_C(   391.81));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   628.52), SIMDE_FLOAT64_C(   640.58));
  e = UINT8_C(  2);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_GT_OQ);
  simde_assert_equal_mmask8(r, e);

  a = simde_mm_set_pd(SIMDE_FLOAT64_C(  -401.79), SIMDE_FLOAT64_C(  -370.01));
  b = simde_mm_set_pd(SIMDE_FLOAT64_C(   181.22), SIMDE_FLOAT64_C(  -720.65));
  e = UINT8_C(  3);
  r = simde_mm_cmp_pd_mask(a, b, SIMDE_CMP_TRUE_US);
  simde_assert_equal_mmask8(r, e);

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 32 ; i++) {
    simde__m128d a = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m128d b = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    int imm8 = i;
    simde__mmask8 r;
    SIMDE_CONSTIFY_32_(simde_mm_cmp_pd_mask, r, (HEDLEY_UNREACHABLE(), 0), imm8, a, b);

    simde_test_x86_write_f64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_codegen_write_i32(2, imm8, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_mmask8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

#else

/* To avoid a warning about expr < 0 always evaluating to false
 * (-Wtype-limits) because there are no functions to test. */

static int
test_simde_dummy (SIMDE_MUNIT_TEST_ARGS) {
  return 0;
}

#endif /* !defined(SIMDE_NATIVE_ALIASES_TESTING) && !defined(SIMDE_FAST_MATH) */

SIMDE_TEST_FUNC_LIST_BEGIN
  #if !defined(SIMDE_NATIVE_ALIASES_TESTING) && !defined(SIMDE_FAST_MATH)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm512_cmp_ps_mask)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm256_cmp_ps_mask)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm_cmp_ps_mask)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm512_cmp_pd_mask)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm256_cmp_pd_mask)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm_cmp_pd_mask)
  #else
    SIMDE_TEST_FUNC_LIST_ENTRY(dummy)
  #endif
SIMDE_TEST_FUNC_LIST_END

#include <test/x86/avx512/test-avx512-footer.h>
