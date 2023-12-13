#ifndef APPLESOFT
#define APPLESOFT

#include <stdint.h>

/* Keyword tokens used in tokenized BASIC programs */
/* A #define will put a 16-bit integer into the program and then convert to a uint8_t
 * at runtime */
/* An enum will also use 16-bit integers */
/* The '\x80' literal will will use a signed char. We want unsigned. */
const uint8_t TK_END   = (uint8_t)0x80;
const uint8_t TK_PRINT = (uint8_t)0xBA;

#endif

