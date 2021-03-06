/*
 * main.h
 *
 * Created: Sat 21 Mar 2020 10:44:50 AM CET
 * Author : hhh
 */

#ifndef MAIN_H
#define MAIN_H

#define STRLEN 256

enum conservativeVariables {
	RHO, MX, MY, E
};
enum primitiveVariables {
	VX = 1, VY, P
};
enum directions {
	X, Y
};
enum boundaryConditionType {
	SLIPWALL = 1, WALL, INFLOW, OUTFLOW, CHARACTERISTIC, EXACTSOL,
	PERIODIC, PRESSURE_OUT
};
enum cartesianMeshSides {
	BOTTOM, RIGHT, TOP, LEFT
};
enum meshType {
	UNSTRUCTURED, CARTESIAN
};
enum variableConversion {
	PVAR_TO_CVAR, CVAR_TO_PVAR
};
enum fluxFunction {
	GOD = 1, ROE, HLL, HLLE, HLLC, LXF, STW, CEN, AUSMD, AUSMDV, VANLEER
};
enum timestepping {
	GLOBAL_STEP, LOCAL_STEP
};
enum limiterFunction {
	BARTHJESPERSEN = 1, VENKATAKRISHNAN
};
enum equationTypes {
	EULER_EQ, NAVIER_STOKES_EQ
};
enum boundaryConditionParameter {
	MEAN_VALUES, EDGE_VALUES
};
enum generalParameters {
	NDIM = 2, NVAR = 4, NBC = 20
};
enum ioFormat {
	CGNS = 1, CURVE, DAT
};
enum clcdResiduals {
	CL = 4, CD
};

#endif
