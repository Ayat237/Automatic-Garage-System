/*
===================================================================================================
* Auther : Ayat Mohamed MOhamed
* Object : MACROS(BIT MATH)
* BIT_MATH.h
===================================================================================================
*/
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

// set any bit in any register
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

// clear any bit in any register
#define CLEAR_BIT(REG,BIT) (REG&=~(1<<BIT))

// toggle any bit in any register
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

// get (read) any bit in any register
#define GET_BIT(REG,BIT) (REG&(1<<BIT))

#endif
/*
 -------------------------------
| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 |
 -------------------------------
*/
