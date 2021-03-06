/*
 * source.c
 *
 * Created: Wed 01 Apr 2020 12:25:11 PM CEST
 * Author : hhh
 */

#include <math.h>

#include "main.h"
#include "equation.h"
#include "mesh.h"

/*
 * evaluate source
 */
void evalSource(int iSource, double x[NDIM], double time, double source[NVAR])
{
	switch (iSource) {
	case 1: {
		double freq = 1.0;
		double amp = 0.1;
		double om = pi * freq;
		double a = 2.0 * pi;

		double tmp1 = cos(om * (x[X] + x[Y]) - a * time);
		double tmp2 = sin(2.0 * (om * (x[X] + x[Y]) - a * time));
		double tmp3 = sin(om * (x[X] + x[Y]) - a * time);
		source[RHO] = (- a + 2.0 * om) * tmp1;
		source[VX]  = (- a + om * (gamma * 3.0 - 1.0)) * tmp1
			+ amp * om * gamma1 * tmp2;
		source[VY]  = source[VX];
		source[E]   = ((2.0 + gamma * 6.0) * om - 4.0 * a) * tmp1
			+ amp * (2.0 * om * gamma - a) * tmp2
			+ 2.0 * mu * gamma * om * om / Pr * tmp3;

		source[RHO] *= amp;
		source[VX]  *= amp;
		source[VY]  *= amp;
		source[E]   *= amp;

		break;
	}
	default:
		source[RHO] = 0.0;
		source[VX]  = 0.0;
		source[VY]  = 0.0;
		source[E]   = 0.0;
	}
}

/*
 * source terms
 */
void calcSource(double time)
{
	if (doCalcSource) {
		#pragma omp parallel for
		for (long iElem = 0; iElem < nElems; ++iElem) {
			elem_t *aElem = elem[iElem];
			aElem->source[RHO] = 0.0;
			aElem->source[VX]  = 0.0;
			aElem->source[VY]  = 0.0;
			aElem->source[E]   = 0.0;

			double src[NVAR];
			for (int iGP = 0; iGP < aElem->nGP; ++iGP) {
				evalSource(sourceFunc, aElem->xGP[iGP], time, src);
				aElem->source[RHO] += src[RHO] * aElem->wGP[iGP];
				aElem->source[VX]  += src[VX]  * aElem->wGP[iGP];
				aElem->source[VY]  += src[VY]  * aElem->wGP[iGP];
				aElem->source[E]   += src[E]   * aElem->wGP[iGP];
			}
		}
	}
}
