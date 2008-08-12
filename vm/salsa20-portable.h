/* salsa20-portable.h */

/*
 * WARNING: the conversions defined below are implemented as macros,
 * and should be used carefully. They should NOT be used with
 * parameters which perform some action. E.g., the following two lines
 * are not equivalent:
 * 
 *  1) ++x; y = ROTL32(x, n); 
 *  2) y = ROTL32(++x, n);
 */

/*
 * *** Please do not edit this file. ***
 *
 * The default macros can be overridden for specific architectures by
 * editing 'salsa20-machine.h'.
 */

#ifndef SALSA20_PORTABLE
#define SALSA20_PORTABLE

#include "salsa20-config.h"

/* ------------------------------------------------------------------------- */

/*
 * The following types are defined (if available):
 *
 * u8:  unsigned integer type, at least 8 bits
 * u16: unsigned integer type, at least 16 bits
 * u32: unsigned integer type, at least 32 bits
 * u64: unsigned integer type, at least 64 bits
 *
 * s8, s16, s32, s64 -> signed counterparts of u8, u16, u32, u64
 *
 * The selection of minimum-width integer types is taken care of by
 * 'salsa20-config.h'. Note: to enable 64-bit types on 32-bit
 * compilers, it might be necessary to switch from ISO C90 mode to ISO
 * C99 mode (e.g., gcc -std=c99).
 */

#ifdef I8T
typedef signed I8T s8;
typedef unsigned I8T u8;
#endif

#ifdef I16T
typedef signed I16T s16;
typedef unsigned I16T u16;
#endif

#ifdef I32T
typedef signed I32T s32;
typedef unsigned I32T u32;
#endif

#ifdef I64T
typedef signed I64T s64;
typedef unsigned I64T u64;
#endif

/*
 * The following macros are used to obtain exact-width results.
 */

#define U8V(v) ((u8)(v) & U8C(0xFF))
#define U16V(v) ((u16)(v) & U16C(0xFFFF))
#define U32V(v) ((u32)(v) & U32C(0xFFFFFFFF))
#define U64V(v) ((u64)(v) & U64C(0xFFFFFFFFFFFFFFFF))

/* ------------------------------------------------------------------------- */

/*
 * The following macros return words with their bits rotated over n
 * positions to the left/right.
 */

#define SALSA20_DEFAULT_ROT

#define ROTL8(v, n) \
  (U8V((v) << (n)) | ((v) >> (8 - (n))))

#define ROTL16(v, n) \
  (U16V((v) << (n)) | ((v) >> (16 - (n))))

#define ROTL32(v, n) \
  (U32V((v) << (n)) | ((v) >> (32 - (n))))

#define ROTL64(v, n) \
  (U64V((v) << (n)) | ((v) >> (64 - (n))))

#define ROTR8(v, n) ROTL8(v, 8 - (n))
#define ROTR16(v, n) ROTL16(v, 16 - (n))
#define ROTR32(v, n) ROTL32(v, 32 - (n))
#define ROTR64(v, n) ROTL64(v, 64 - (n))

#include "salsa20-machine.h"

/* ------------------------------------------------------------------------- */

/*
 * The following macros return a word with bytes in reverse order.
 */

#define SALSA20_DEFAULT_SWAP

#define SWAP16(v) \
  ROTL16(v, 8)

#define SWAP32(v) \
  ((ROTL32(v,  8) & U32C(0x00FF00FF)) | \
   (ROTL32(v, 24) & U32C(0xFF00FF00)))

#ifdef SALSA20_NATIVE64
#define SWAP64(v) \
  ((ROTL64(v,  8) & U64C(0x000000FF000000FF)) | \
   (ROTL64(v, 24) & U64C(0x0000FF000000FF00)) | \
   (ROTL64(v, 40) & U64C(0x00FF000000FF0000)) | \
   (ROTL64(v, 56) & U64C(0xFF000000FF000000)))
#else
#define SWAP64(v) \
  (((u64)SWAP32(U32V(v)) << 32) | (u64)SWAP32(U32V(v >> 32)))
#endif

#include "salsa20-machine.h"

#define SALSA20_DEFAULT_WTOW

#ifdef SALSA20_LITTLE_ENDIAN
#define U16TO16_LITTLE(v) (v)
#define U32TO32_LITTLE(v) (v)
#define U64TO64_LITTLE(v) (v)

#define U16TO16_BIG(v) SWAP16(v)
#define U32TO32_BIG(v) SWAP32(v)
#define U64TO64_BIG(v) SWAP64(v)
#endif

#ifdef SALSA20_BIG_ENDIAN
#define U16TO16_LITTLE(v) SWAP16(v)
#define U32TO32_LITTLE(v) SWAP32(v)
#define U64TO64_LITTLE(v) SWAP64(v)

#define U16TO16_BIG(v) (v)
#define U32TO32_BIG(v) (v)
#define U64TO64_BIG(v) (v)
#endif

#include "salsa20-machine.h"

/*
 * The following macros load words from an array of bytes with
 * different types of endianness, and vice versa.
 */

#define SALSA20_DEFAULT_BTOW

#if (!defined(SALSA20_UNKNOWN) && defined(SALSA20_I8T_IS_BYTE))

#define U8TO16_LITTLE(p) U16TO16_LITTLE(((u16*)(p))[0])
#define U8TO32_LITTLE(p) U32TO32_LITTLE(((u32*)(p))[0])
#define U8TO64_LITTLE(p) U64TO64_LITTLE(((u64*)(p))[0])

#define U8TO16_BIG(p) U16TO16_BIG(((u16*)(p))[0])
#define U8TO32_BIG(p) U32TO32_BIG(((u32*)(p))[0])
#define U8TO64_BIG(p) U64TO64_BIG(((u64*)(p))[0])

#define U16TO8_LITTLE(p, v) (((u16*)(p))[0] = U16TO16_LITTLE(v))
#define U32TO8_LITTLE(p, v) (((u32*)(p))[0] = U32TO32_LITTLE(v))
#define U64TO8_LITTLE(p, v) (((u64*)(p))[0] = U64TO64_LITTLE(v))

#define U16TO8_BIG(p, v) (((u16*)(p))[0] = U16TO16_BIG(v))
#define U32TO8_BIG(p, v) (((u32*)(p))[0] = U32TO32_BIG(v))
#define U64TO8_BIG(p, v) (((u64*)(p))[0] = U64TO64_BIG(v))

#else

#define U8TO16_LITTLE(p) \
  (((u16)((p)[0])      ) | \
   ((u16)((p)[1]) <<  8))

#define U8TO32_LITTLE(p) \
  (((u32)((p)[0])      ) | \
   ((u32)((p)[1]) <<  8) | \
   ((u32)((p)[2]) << 16) | \
   ((u32)((p)[3]) << 24))

#ifdef SALSA20_NATIVE64
#define U8TO64_LITTLE(p) \
  (((u64)((p)[0])      ) | \
   ((u64)((p)[1]) <<  8) | \
   ((u64)((p)[2]) << 16) | \
   ((u64)((p)[3]) << 24) | \
   ((u64)((p)[4]) << 32) | \
   ((u64)((p)[5]) << 40) | \
   ((u64)((p)[6]) << 48) | \
   ((u64)((p)[7]) << 56))
#else
#define U8TO64_LITTLE(p) \
  ((u64)U8TO32_LITTLE(p) | ((u64)U8TO32_LITTLE((p) + 4) << 32))
#endif

#define U8TO16_BIG(p) \
  (((u16)((p)[0]) <<  8) | \
   ((u16)((p)[1])      ))

#define U8TO32_BIG(p) \
  (((u32)((p)[0]) << 24) | \
   ((u32)((p)[1]) << 16) | \
   ((u32)((p)[2]) <<  8) | \
   ((u32)((p)[3])      ))

#ifdef SALSA20_NATIVE64
#define U8TO64_BIG(p) \
  (((u64)((p)[0]) << 56) | \
   ((u64)((p)[1]) << 48) | \
   ((u64)((p)[2]) << 40) | \
   ((u64)((p)[3]) << 32) | \
   ((u64)((p)[4]) << 24) | \
   ((u64)((p)[5]) << 16) | \
   ((u64)((p)[6]) <<  8) | \
   ((u64)((p)[7])      ))
#else
#define U8TO64_BIG(p) \
  (((u64)U8TO32_BIG(p) << 32) | (u64)U8TO32_BIG((p) + 4))
#endif

#define U16TO8_LITTLE(p, v) \
  do { \
    (p)[0] = U8V((v)      ); \
    (p)[1] = U8V((v) >>  8); \
  } while (0)

#define U32TO8_LITTLE(p, v) \
  do { \
    (p)[0] = U8V((v)      ); \
    (p)[1] = U8V((v) >>  8); \
    (p)[2] = U8V((v) >> 16); \
    (p)[3] = U8V((v) >> 24); \
  } while (0)

#ifdef SALSA20_NATIVE64
#define U64TO8_LITTLE(p, v) \
  do { \
    (p)[0] = U8V((v)      ); \
    (p)[1] = U8V((v) >>  8); \
    (p)[2] = U8V((v) >> 16); \
    (p)[3] = U8V((v) >> 24); \
    (p)[4] = U8V((v) >> 32); \
    (p)[5] = U8V((v) >> 40); \
    (p)[6] = U8V((v) >> 48); \
    (p)[7] = U8V((v) >> 56); \
  } while (0)
#else
#define U64TO8_LITTLE(p, v) \
  do { \
    U32TO8_LITTLE((p),     U32V((v)      )); \
    U32TO8_LITTLE((p) + 4, U32V((v) >> 32)); \
  } while (0)
#endif

#define U16TO8_BIG(p, v) \
  do { \
    (p)[0] = U8V((v)      ); \
    (p)[1] = U8V((v) >>  8); \
  } while (0)

#define U32TO8_BIG(p, v) \
  do { \
    (p)[0] = U8V((v) >> 24); \
    (p)[1] = U8V((v) >> 16); \
    (p)[2] = U8V((v) >>  8); \
    (p)[3] = U8V((v)      ); \
  } while (0)

#ifdef SALSA20_NATIVE64
#define U64TO8_BIG(p, v) \
  do { \
    (p)[0] = U8V((v) >> 56); \
    (p)[1] = U8V((v) >> 48); \
    (p)[2] = U8V((v) >> 40); \
    (p)[3] = U8V((v) >> 32); \
    (p)[4] = U8V((v) >> 24); \
    (p)[5] = U8V((v) >> 16); \
    (p)[6] = U8V((v) >>  8); \
    (p)[7] = U8V((v)      ); \
  } while (0)
#else
#define U64TO8_BIG(p, v) \
  do { \
    U32TO8_BIG((p),     U32V((v) >> 32)); \
    U32TO8_BIG((p) + 4, U32V((v)      )); \
  } while (0)
#endif

#endif

#include "salsa20-machine.h"

/* ------------------------------------------------------------------------- */

#endif
