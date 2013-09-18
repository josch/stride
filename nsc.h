/*
 * Copyright (C) 1994 Frank Eisenhaber <franke at bii.a-star.edu.sg>
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
 *
 *  references :
 *  1.F.Eisenhaber, P.Lijnzaad, P.Argos, M.Scharf
 *    "The Double Cubic Lattice Method: Efficient Approaches to
 *    Numerical Integration of Surface Area and Volume and to Dot
 *    Surface Contouring of Molecular Assemblies"
 *    Journal of Computational Chemistry (1994) submitted
 *  2.F.Eisenhaber, P.Argos
 *    "Improved Strategy in Analytic Surface Calculation for Molecular
 *    Systems: Handling of Singularities and Computational Efficiency"
 *    Journal of Computational Chemistry (1993) v.14, N11, pp-1272-1280
 *
 */

#define FLAG_DOTS       01
#define FLAG_VOLUME     02
#define FLAG_ATOM_AREA  04

#define NSC nsc_dclm

extern int NSC(
  double * ,	/* atom coordinates xyz0, xyz1, ... */
  double * ,	/* atom radii r0, r1, r2, ... */
  int ,         /* number of atoms */
  int ,		/* number of dots per fully accessible sphere */
  int ,		/* flag : dots, volume and/or area per atom */
  double * ,	/* 1 output: overall area */
  double ** ,   /* 2 output: pointer to list of areas per atom */
  double * ,	/* 3 output: overall volume */
  double ** ,	/* 4 output: pointer to list of surface dots x0, y0, z0, ... */
  int *		/* 5 output: number of surface dots */
  );

/* 
    User notes :
The input requirements :
  The arrays with atom coordinates and radii are thought to start
  with index 0, i.e., places 0, 1, and 2 are the x-, y-, and z-
  coordinates of the zero-th atom and place 0 in the other array
  is its radius.
  The user can define any number of dots. The program selects a
  dot density that is the lowest possible with at least the required
  number of dots. The points are distributed in accordance with the
  icosahedron-based or the dodecahedron-based method as described in
  ref. 1.

The output requirements are :
  1 and 3 :  pointer to an existing double
  2 and 4 :  pointer to an existing pointer to double
             NSC allocates memory for an array
  5       :  pointer to an existing integer

The subroutine NSC makes use of variant 2 described in reference 1.
By selecting the necessary output via flags, the requirements for
cpu-time and computer memory can be adapted to the actual needs.

Example : flag = FLAG_VOLUME | FLAG_ATOM_AREA | FLAG_DOTS
          The routine calculates the area, volume and the dot surface.
          This variant is not recommended because normally the dot surface
          is needed for low point density (e.g.42) at which area and volume 
          are inaccurate. The sign "|" is used as binary AND !

          flag = FLAG_VOLUME | FLAG_ATOM_AREA
          In this case the large arrays for storing the surface dots
          are not allocated. A large point number of the fully accessible
          sphere can be selected. Good accuracy is already achieved with
          600-700 points per sphere (accuracy of about 1.5 square Angstrem
          per atomic sphere).
          Output pointers 4 and 5 may be NULL.

          flag = FLAG_DOTS
          Only the dot surface is produced.
          Output pointers 2 and 3 may be NULL.

The output pointer 1 cannot be set to NULL in any circumstances. The
overall area value is returned in every mode.

All files calling NSC should include nsc.h !!

*/
