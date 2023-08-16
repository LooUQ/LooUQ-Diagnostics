/******************************************************************************
 *  \file lqdiag.h
 *  \author Greg Terrell
 *  \license MIT License
 *
 *  Copyright (c) 2023 LooUQ Incorporated.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************
 * LooUQ Diagnostics 
 * - Debug logging via Segger RTT or native platform serial output.
 * - ASSERT signalling (incl ASSERT_W) with application notification and
 *   platform specific diagnostic information capture
 * 
 *****************************************************************************/

#ifndef __LQPRNT_H__
#define __LQPRNT_H__

/* PRINTF macro support
 * ============================================================================================= */

#ifndef DBGBUFFER_SZ
     #define DBGBUFFER_SZ 120
#endif


// configure diagnostic logging output
#if defined(ENABLE_DIAGPRINT)
    #ifndef _TERMINAL
        #define _TERMINAL
        asm(".global _printf_float");       // forces build to link in float support for printf
        #define SERIAL_DBG                  // enable serial port output using devl host platform serial
        #define DIAGPRINT_SERIAL
    #endif

    #ifndef PRNT_DEFAULT
        #define PRNT_DEFAULT 13
        #define PRNT_INFO 15
        #define PRNT_WARN 17
        #define PRNT_ERROR 16

        #define PRNT_CYAN 10
        #define PRNT_MAGENTA 11
        #define PRNT_WHITE 12
        #define PRNT_GRAY 13
        #define PRNT_BLUE 14
        #define PRNT_GREEN 15
        #define PRNT_RED 16
        #define PRNT_YELLOW 17

        #define PRNT_dCYAN 20
        #define PRNT_dMAGENTA 21
        #define PRNT_dBLUE 24
        #define PRNT_dGREEN 25
        #define PRNT_dRED 26
        #define PRNT_dYELLOW 27
    #endif

    #if !defined(PRINTDBG)
        #define DPRINT(c_, f_, ...) dbg_print((f_), ##__VA_ARGS__)         // dbg_print is the serial port output, color info from macro is dropped
    #endif
    #if defined(ENABLE_DIAGPRINT_VERBOSE)
        #define DPRINT_V(c_, f_, ...) dbg_print((f_), ##__VA_ARGS__)          // dbg_print is the serial port output, color info from macro is dropped
    #endif

#else // No PRINT() expansion, statements in source ignored
    #define DPRINT(c_, f_, ...)
    #define DPRINT_V(c_, f_, ...)
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void dbg_print(const char *msg, ...);

#ifdef __cplusplus
}
#endif // __cplusplus



/* ASSERT/ASSERT_W Capture
 * ============================================================================================= */
#if defined(ENABLE_ASSERTS)
    #if defined(ARDUINO_ARCH_SAMD)
    #elif defined(ARDUINO_ARCH_ESP32)
    #endif
#else
    #define ASSERT(exp)  (0)
    #define ASSERT_W(exp, faultTxt)  (0)
#endif


#endif // __LQPRNT_H__

