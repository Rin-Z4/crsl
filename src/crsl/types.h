#ifndef __CRSL_TYPES_H
#define __CRSL_TYPES_H

#include <limits.h>

/* NOTE:
 * From the C89 standard:
 *   CHAR_BIT - number of bits in a byte (nowadays it's 8 and we will not support less than 8)
 *
 *   SCHAR_MIN  -127 or lower
 *   SCHAR_MAX  +127 or higher
 *   UCHAR_MAX   255 or higher
 *
 *   CHAR_MIN <-- Depends on if `char` is treated as signed or unsigned in an expression
 *   CHAR_MAX ^
 *
 *   SHRT_MIN   -32767 or lower
 *   SHRT_MAX   +32767 or higher
 *   USHRT_MAX   65535 or higher
 *
 *   INT_MIN   -32767 or lower
 *   INT_MAX   +32767 or higher
 *   UINT_MAX   65535 or higher
 *
 *   LONG_MIN  -2147483647 or lower
 *   LONG_MAX  +2147483647 or higher
 *   ULONG_MAX  4294967295 or higher
 *
 *   int is the "natual" integer size for an architecture
 *   char is enough to fit a character
 *   sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long)
 *
 * sizeof(char)  >= 1
 * sizeof(short) >= 2
 * sizeof(int)   >= 2
 * sizeof(long)  >= 4
 *
 * sizeof(x) * CHAR_BIT -> number of bits in type x
 */

typedef   signed char  schar;
typedef unsigned char  uchar;

typedef   signed short sshort;
typedef unsigned short ushort;

typedef   signed int   sint;
typedef unsigned int   uint;

typedef   signed long  slong;
typedef unsigned long  ulong;


/* Run and compile detect_types.c to generate this header */
#include "detected_types.h"
#include <limits.h>

/* NOTE: The "p" stands for "plus" as in at least this amount of bits
 * If CHAR_BITS == 8, then u8p == u8, u16p == u16, etc.
 * This is for compatibility */

/* At least 1 byte */
typedef unsigned char u8p;
typedef   signed char s8p;
#define U8P_MAX UCHAR_MAX
#define S8P_MIN SCHAR_MIN
#define S8P_MAX SCHAR_MAX

/* At least 2 bytes */
#if INT_BYTES == SHORT_BYTES
/* short == int, so choose int as it's the "native" type */
typedef unsigned int u16p;
typedef   signed int s16p;
#define U16P_MAX UINT_MAX
#define S16P_MIN SINT_MIN
#define S16P_MAX SINT_MAX
#else
/* short < int */
typedef unsigned short u16p;
typedef   signed short s16p;
#define U16P_MAX USHRT_MAX
#define S16P_MIN SSHRT_MIN
#define S16P_MAX SSHRT_MAX
#endif

#if INT_BYTES >= 4
/* May be 4 bytes */
typedef unsigned int u32p;
typedef   signed int s32p;
#define U32P_MAX UINT_MAX
#define S32P_MIN SINT_MIN
#define S32P_MAX SINT_MAX
#else
/* Guaranteed at least 4 bytes */
typedef unsigned long u32p;
typedef   signed long s32p;
#define U32P_MAX ULONG_MAX
#define S32P_MIN SLONG_MIN
#define S32P_MAX SLONG_MAX
#endif

/* 8 bytes may not always exist */
#define HAVE_64BIT_INTEGER_TYPE
#if INT_BYTES >= 8
/* first check int as it's the "native" type */
typedef unsigned int u64p;
typedef   signed int s64p;
#define U64P_MAX UINT_MAX
#define S64P_MIN SINT_MIN
#define S64P_MAX SINT_MAX
#elif LONG_BYTES >= 8
/* though usually int will be 4 and long 8 */
typedef unsigned long u64p;
typedef   signed long s64p;
#define U64P_MAX ULONG_MAX
#define S64P_MIN SLONG_MIN
#define S64P_MAX SLONG_MAX
#else
/* no 64 bit type */
#undef HAVE_64BIT_INTEGER_TYPE
#endif


#define  U8_MAX 0xFF
#define  S8_MAX 0x7F
#define  S8_MIN 0x80

#define U16_MAX 0xFFFF
#define S16_MAX 0x7FFF
#define S16_MIN 0x8000

#define U32_MAX 0xFFFFFFFF
#define S32_MAX 0x7FFFFFFF
#define S32_MIN 0x80000000

#ifdef HAVE_64BIT_INTEGER_TYPE
#define U64_MAX 0xFFFFFFFFFFFFFFFF
#define S64_MAX 0x7FFFFFFFFFFFFFFF
#define S64_MIN 0x8000000000000000
#endif


/* bool is the smallest unsigned integer type */
typedef u8p bool_t;

#endif
