#ifndef DTYPES_H
#define DTYPES_H

/*
  This file defines sane integer types for our target platforms. This
  library only runs on machines with the following characteristics:

  - supports integer word sizes of 8, 16, 32, and 64 bits
  - uses unsigned and signed 2's complement representations
  - all pointer types are the same size
  - there is an integer type with the same size as a pointer

  Some features require:
  - IEEE 754 single- and double-precision floating point

  We assume the LP64 convention for 64-bit platforms.
*/

#ifdef WIN32
#define STDCALL __stdcall
# ifdef IMPORT_EXPORTS
#  define DLLEXPORT __declspec(dllimport)
# else
#  define DLLEXPORT __declspec(dllexport)
# endif
#else
#define STDCALL
#define DLLEXPORT __attribute__ ((visibility("default")))
#endif

#ifdef __linux
#include <features.h>
#include <endian.h>
#define LITTLE_ENDIAN  __LITTLE_ENDIAN
#define BIG_ENDIAN     __BIG_ENDIAN
#define PDP_ENDIAN     __PDP_ENDIAN
#define BYTE_ORDER     __BYTE_ORDER
#endif

#ifdef __APPLE__
#include <machine/endian.h>
#define __LITTLE_ENDIAN  LITTLE_ENDIAN
#define __BIG_ENDIAN     BIG_ENDIAN
#define __PDP_ENDIAN     PDP_ENDIAN
#define __BYTE_ORDER     BYTE_ORDER
#endif

#ifdef WIN32
#define __LITTLE_ENDIAN	1234
#define __BIG_ENDIAN	4321
#define __PDP_ENDIAN	3412
#define __BYTE_ORDER       __LITTLE_ENDIAN
#define __FLOAT_WORD_ORDER __LITTLE_ENDIAN
#define LITTLE_ENDIAN  __LITTLE_ENDIAN
#define BIG_ENDIAN     __BIG_ENDIAN
#define PDP_ENDIAN     __PDP_ENDIAN
#define BYTE_ORDER     __BYTE_ORDER
#endif

#if (__STDC_VERSION__ >= 199901L) || defined(__GNUG__)
// argument counting macros for C99
#define VA_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,  \
                 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
                 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
                 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
                 _61,_62,_63,N,...) N
#define VA_RSEQ_N() 63,62,61,60,59,58,57,56,55,54,53,52,51,50, \
                    49,48,47,46,45,44,43,42,41,40,39,38,37,36, \
                    35,34,33,32,31,30,29,28,27,26,25,24,23,22, \
                    21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define VA_NARG_(...) VA_ARG_N(__VA_ARGS__)
#define VA_NARG(...) VA_NARG_(__VA_ARGS__,VA_RSEQ_N())
#endif

#define LLT_ALLOC(n) malloc(n)
#define LLT_REALLOC(p,n) realloc((p),(n))
#define LLT_FREE(x) free(x)

typedef int bool_t;

#if defined(__INTEL_COMPILER) && defined(WIN32)
# define STATIC_INLINE static
# define INLINE
# ifdef __LP64__
typedef unsigned long size_t;
# else
typedef unsigned int size_t;
# endif
#else
# define STATIC_INLINE static inline
# define INLINE inline
#endif

typedef unsigned char  byte_t;   /* 1 byte */
#if defined(WIN32)
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
#ifdef __LP64__
typedef unsigned long u_int64_t;
#else
typedef unsigned long long u_int64_t;
#endif
#ifdef __INTEL_COMPILER
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
#endif
#else
#include <sys/types.h>
#endif

#ifdef __LP64__
#define TOP_BIT 0x8000000000000000
#define NBITS 64
typedef unsigned long uint_t;  // preferred int type on platform
typedef long int_t;
typedef int64_t offset_t;
typedef u_int64_t index_t;
typedef int64_t ptrint_t; // pointer-size int
typedef u_int64_t u_ptrint_t;
#else
#define TOP_BIT 0x80000000
#define NBITS 32
typedef unsigned long uint_t;
typedef long int_t;
typedef int32_t offset_t;
typedef u_int32_t index_t;
typedef int32_t ptrint_t;
typedef u_int32_t u_ptrint_t;
#endif

typedef u_int8_t  uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
typedef u_ptrint_t uptrint_t;

#define LLT_ALIGN(x, sz) (((x) + (sz-1)) & (-sz))

// branch prediction annotations
#ifdef __GNUC__
#define __unlikely(x) __builtin_expect(!!(x), 0)
#define __likely(x)   __builtin_expect(!!(x), 1)
#else
#define __unlikely(x) (x)
#define __likely(x)   (x)
#endif

#define DBL_MAXINT 9007199254740992LL
#define FLT_MAXINT 16777216
#define U64_MAX    18446744073709551615ULL
#define S64_MAX    9223372036854775807LL
#define S64_MIN    (-S64_MAX - 1LL)
#define BIT63      0x8000000000000000LL
#define U32_MAX    4294967295L
#define S32_MAX    2147483647L
#define S32_MIN    (-S32_MAX - 1L)
#define BIT31      0x80000000

#define DBL_EPSILON      2.2204460492503131e-16
#define FLT_EPSILON      1.192092896e-7
#define DBL_MAX          1.7976931348623157e+308
#define DBL_MIN          2.2250738585072014e-308
#define FLT_MAX          3.402823466e+38
#define FLT_MIN          1.175494351e-38
#define LOG2_10          3.3219280948873626
#define rel_zero(a, b) (fabs((a)/(b)) < DBL_EPSILON)
#define sign_bit(r) ((*(int64_t*)&(r)) & BIT63)
#define LABS(n) (((n)^((n)>>(NBITS-1))) - ((n)>>(NBITS-1)))
#define NBABS(n,nb) (((n)^((n)>>((nb)-1))) - ((n)>>((nb)-1)))
#define DFINITE(d) (((*(int64_t*)&(d))&0x7ff0000000000000LL)!=0x7ff0000000000000LL)
#define DNAN(d) ((d)!=(d))

extern double D_PNAN;
extern double D_NNAN;
extern double D_PINF;
extern double D_NINF;
extern float  F_PNAN;
extern float  F_NNAN;
extern float  F_PINF;
extern float  F_NINF;

#endif
