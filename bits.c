/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 龚彦哲 26303050100
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return (1 << 31);
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2 
 */
int bitXor(int x, int y) {
	return ~((~((~x)&y))&(~(x&(~y))));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x>>31)&((~x)+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
   int Src=(x>>(src<<3))&0xFF;
   int Dst=(~((0xFF)<<(dst<<3)))&x;
   return Dst+(Src<<(dst<<3));
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int N=x>>n;
  int Zero=((~(!n+(~0)))&(~0))+((!n+(~0))&(~((~0)<<(33+(~n)))));
  return N&Zero;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int Chang1=0x0F+(0X0F<<8)+(0X0F<<16)+(0X0F<<24);
  int a=x&(~Chang1);
  int b=x&Chang1;
  int FuHao=~((~0)<<28);
  return (b<<4)+((a>>4)&FuHao);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int Fan=~x;
  int First=Fan&(x+1);
  x=x+First;
  return (~x)&(x+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x^=(x>>16);
  x^=(x>>8);
  x^=(x>>4);
  x^=(x>>2);
  x^=(x>>1);
  return (~x)&1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  n=n&31;
  int N=33+(~n);
  int Remain=(x&((1<<n)+(~0)))<<(N&31);
  return Remain+((x>>n)&(((1<<N)&(!n+(~0)))+(~0)));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int Chang2=~0;
  int Stay=x>>n;
  int Remain=((x+(~(Stay<<n)))<<1)+3;
  int PanDing=Remain+(~(1<<n));
  int FanPanDing=(!PanDing)+Chang2;
  Stay+=(~((((PanDing>>31)&1)+Chang2)))+1+((~FanPanDing)&((Stay&1)+Chang2));
  return Stay<<n;
}  
// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int YiJiYiOu=(x^y)&1;
  int xFuHao=x>>31;
  int yFuHao=y>>31;
  int TongHao=1+(xFuHao^yFuHao);
  int Minus=x+(~y)+1;
  int OnSide=TongHao&((Minus>>31)+1);
  return (x>>1)+(y>>1)+((x&1)&(y&1))+(YiJiYiOu&(xFuHao+1)&((~yFuHao)+1))+(YiJiYiOu&OnSide);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int aFuHao=a>>31;
  int bFuHao=b>>31;
  int xFuHao=x>>31;
  int axTongHao=(aFuHao^xFuHao)+1;
  int xbTongHao=(xFuHao^bFuHao)+1;
  int axMinus=a+(~x)+1;
  int xbMinus=x+(~b)+1;
  int axDaXiao=(aFuHao+1)&((~xFuHao)+1);
  axDaXiao+=axTongHao&((axMinus>>31)+1);
  int xbDaXiao=(xFuHao+1)&((~bFuHao)+1);
  xbDaXiao+=xbTongHao&((xbMinus>>31)+1);
  int axZero=axTongHao&(!axMinus);
  int xbZero=xbTongHao&(!xbMinus);
  return ((~((axDaXiao^xbDaXiao)+(~0)))+1)|axZero|xbZero;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int xX=x>>31;
  int a=x<<1;
  int aA=a>>31;
  int b=x<<2;
  int bB=b>>31;
  int ans=x+b;
  int ansAns=ans>>31;
  int aIf=aA^xX;
  int bIf=bB^xX;
  int ansIf=ansAns^xX;
  int initmin=1<<31;
  int initmax=(~0)+initmin;
  int keyIf=aIf|bIf|ansIf;
  return (ans&(~aIf)&(~bIf)&(~ansIf))+(initmax&(~xX)&keyIf)+(initmin&xX&keyIf);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int xFH=x>>31;
  int yFH=y>>31;
  int zFH=z>>31;
  int xyTH=xFH^yFH;
  int xzTH=xFH^zFH;
  int yzTH=yFH^zFH;
  int xyFH=(x+y)>>31;
  int xzFH=(x+z)>>31;
  int yzFH=(y+z)>>31;
  int sumFH=(x+y+z)>>31;
  int AllTH=xyTH|xzTH|yzTH;
  int Bian1=(xFH^xyFH)|(xFH^xzFH)|(xFH^yzFH)|(xFH^sumFH);
  int ans1=1&(~AllTH)&(~xFH)&Bian1;
  ans1+=(~0)&(~AllTH)&xFH&Bian1;
  int xyTHOnly=AllTH&(~xyTH);
  int xyYH=AllTH&xyTH;
  int Bian2=(~(xzFH^yFH))&(yFH^sumFH)&xyTHOnly;
  int Bian3=(~(xyFH^zFH))&(zFH^sumFH)&xyYH;
  int xyTHSum=1&Bian2&(~yFH);
  xyTHSum+=(~0)&Bian2&yFH;
  int xyYHSum=1&Bian3&(~zFH);
  xyYHSum+=(~0)&Bian3&zFH;
  return ans1+xyTHSum+xyYHSum;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  int wei=uf&0x80000000;
  int ciFang=(uf&0x7F800000)>>23;
  int xiaoShu=uf&0x7FFFFF;
  xiaoShu=xiaoShu<<1;
  int ans;
  if(ciFang==0xFF)
  {
      ans=uf;
  }
  if((ciFang!=0)&&(ciFang!=0xFF))
  {
    int xiaoShuHou2=xiaoShu+(xiaoShu>>1)+0x800000;
    if(((xiaoShuHou2&1)==1)&&((xiaoShuHou2&2)==2))
    {
      xiaoShuHou2++;
    }
    xiaoShuHou2=xiaoShuHou2>>1;
    int jinWei2=xiaoShuHou2&0x800000;
    if(jinWei2==0x800000)
    {
      ciFang++;
      xiaoShuHou2+=0x800000;
      if((xiaoShuHou2&3)==3)
      {
        xiaoShuHou2++;
      }
      xiaoShuHou2=(xiaoShuHou2>>1)&0x7FFFFF;
    }
    else
    {
      xiaoShuHou2=xiaoShuHou2&0x7FFFFF;
    }
    if((ciFang==0xFF))
    {
      xiaoShuHou2=0;
    }
    ans=wei+(ciFang<<23)+xiaoShuHou2;
  }
  if(ciFang==0)
  {
      int xiaoShuHou1=xiaoShu+(xiaoShu>>1);
      if(((xiaoShuHou1&1)==1)&&((xiaoShuHou1&2)==2))
      {
        xiaoShuHou1++;
      }
      xiaoShuHou1=xiaoShuHou1>>1;
      int jinWei1=xiaoShuHou1&0x800000;
      xiaoShuHou1=xiaoShuHou1&0x7FFFFF;
      if(jinWei1==0x800000)
      {
        ciFang++;
      }
      ans=wei+(ciFang<<23)+xiaoShuHou1;
  }
  return ans;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  int One=uf&0x80000000;
  int Eight=(uf&0x7F800000)>>23;
  int TT=uf&0x7FFFFF;
  int fre=0;
  if(Eight==0xFF)
  {
      fre=uf;
  }
  if((Eight>0)&&(Eight<0xFF))
  {
    if(Eight<=125)
    {
        fre=One;
    }
    if(Eight==126)
    {
      if(TT==0)
      {
        fre=One;
      }
      else
      {
        fre=One+0x3F800000;
      }
    }
    if(Eight==127)
    {
      if((TT&0x400000)==0)
      {
        fre=One+(Eight<<23);
      }
      else
      {
        fre=One+0x40000000;
      }
    }
    if(Eight>=150)
    {
      fre=uf;
    }
    if((Eight>=128)&&(Eight<=149))
    {
      int Left=((0x7FFFFF>>(Eight-127))&TT)<<(Eight-127);
      if((Left&0x400000)==0)
      {
        fre=One+(Eight<<23)+TT-((0x7FFFFF>>(Eight-127))&TT);
      }
      else
      {
        if(Left==0x400000)
        {
          if(((TT>>(150-Eight))&1)==0)
          {
            TT=TT-((0x7FFFFF>>(Eight-127))&TT);
          }
          else
          {
            TT=((TT>>(150-Eight))+1)<<(150-Eight);
          }
        }
        else
        {
          TT=((TT>>(150-Eight))+1)<<(150-Eight);
        }
        if(TT==0x800000)
        {
          Eight++;
          TT=0;
        }
        fre=One+(Eight<<23)+TT;
      }
    }
  }
  if(Eight==0)
  {
      fre=One;
  }
  return fre;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  int firstFH=x&0x80000000;
  int twoNine=157;
  int i2f;
  if(x==0)
  {
    i2f=0;
  }
  else if(x==0x80000000)
  {
    i2f=0xCF000000;
  }
  else
  {
    int x0=x>>31;
    int x1=(x^x0)-x0;
    int x2=x1;
    while((x1&0x40000000)!=0x40000000)
    {
      twoNine--;
      x1=x1<<1;
    }
    int Bian7=twoNine<<23;
    if(twoNine>150)
    {
      int Bian4=twoNine-150;
      int Bian6=Bian4-1;
      int xiaoShu=x2&(0x7FFFFF<<Bian4);
      int leftNum=x2&((1<<Bian4)-1);
      if(((leftNum&(1<<Bian6))!=0)&&((((xiaoShu>>Bian4)&1)==1)||(leftNum!=(1<<Bian6))))
      {
        xiaoShu+=(1<<Bian4);
      }
      i2f=firstFH+Bian7+(xiaoShu>>Bian4);
    }
    else
    {
      int Bian5=150-twoNine;
      int xiaoShu=x2&(0x7FFFFF>>Bian5);
      i2f=firstFH+Bian7+(xiaoShu<<Bian5);
    }
  }
  return i2f;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int Chang3=0x55+(0x55<<8)+(0x55<<16)+(0x55<<24);
  int Chang4=0x33+(0x33<<8)+(0x33<<16)+(0x33<<24);
  int Chang5=0x0F+(0x0F<<8)+(0x0F<<16)+(0x0F<<24);
  x=x+(~((x>>1)&Chang3))+1;
  x=((x>>2)&Chang4)+(x&Chang4);
  x=((x>>4)&Chang5)+(x&Chang5);
  x=x+(x>>8);
  return (x+(x>>16))&0xFF;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  int Chang10=0xFF+(0xFF<<8);
  int Chang9=Chang10^(Chang10<<8);
  int Chang8=Chang9^(Chang9<<4);
  int Chang7=Chang8^(Chang8<<2);
  int Chang6=Chang7^(Chang7<<1);
  x=((x&Chang6)<<1)+((x>>1)&Chang6);
  x=((x&Chang7)<<2)+((x>>2)&Chang7);
  x=((x&Chang8)<<4)+((x>>4)&Chang8);
  x=((x&Chang9)<<8)+((x>>8)&Chang9);
  return (x<<16)+((x>>16)&Chang10);
}