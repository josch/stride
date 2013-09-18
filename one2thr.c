/*
 * Copyright (C) 1992-1994 Dmitrij Frishman <d.frishman at wzw.tum.de>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <string.h>
#include <stdio.h>

char *OneToThree(char One)
{

  if( One == 'A' ) return("ALA");
  else if( One == 'R' ) return("ARG");
  else if( One == 'N' ) return("ASN");
  else if( One == 'D' ) return("ASP");
  else if( One == 'B' ) return("ASX");
  else if( One == 'C' ) return("CYS");
  else if( One == 'Q' ) return("GLN");
  else if( One == 'E' ) return("GLU");
  else if( One == 'Z' ) return("GLX");
  else if( One == 'G' ) return("GLY");
  else if( One == 'H' ) return("HIS");
  else if( One == 'I' ) return("ILE");
  else if( One == 'L' ) return("LEU");
  else if( One == 'K' ) return("LYS");
  else if( One == 'M' ) return("MET");
  else if( One == 'P' ) return("PRO");
  else if( One == 'F' ) return("PHE");
  else if( One == 'S' ) return("SER");
  else if( One == 'T' ) return("THR");
  else if( One == 'W' ) return("TRP");
  else if( One == 'Y' ) return("TYR");
  else if( One == 'V' ) return("VAL");
  else if( One == 'X' ) return("UNK");
  else return("***");
}
