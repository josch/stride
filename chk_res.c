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


#include "stride.h"

int CheckRes(char *Res)
{
  register int ResTypeCnt;
  int ResTypeNumber = 45;
  static char *Rsd[MAX_ResType] = {
    "ACE", "ALA", "ARG", "ASN", "ASP", "ASX", "CYS", "GLN", "GLU", "GLX", "GLY", "HIS", "ILE", 
    "LEU", "LYS", "MET", "PRO", "PHE", "SER", "THR", "TRP", "TYR", "VAL", "FOR", "UNK", "HOH",
    /* Residues found empirically in the protein files */
/*  1gp1   1gp1   1hne   1tmn   2mcg   5hvp   6cha   1bbo   1ctg   act1   act1   aom1   rom7 */
    "SEC", "ALM", "MSU", "CLT", "PCA", "STA", "EXC", "ABU", "HYP", "HMS", "ASS", "OCT", "CYH",
/*  sod0  7adh   2psg   tim1   tim2   2pia */
    "MN", "INI", "PO3", "SUL", "WAT", "FMN"
    };

  for( ResTypeCnt=0; ResTypeCnt<ResTypeNumber; ResTypeCnt++ )
      if( !strcmp(Res,Rsd[ResTypeCnt]) )
	 return(SUCCESS);

  return(FAILURE);
}
      
