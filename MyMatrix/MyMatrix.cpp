//#include <vld.h>

#include <MyMatrix.h>


EXPORT void __stdcall MExtend(int m12x, int m1y, int m2y, double** m1, double** m2, double** m12){
	int x,y;
	for(x=0; x<m12x;x++){
		for(y=0;y<m1y;y++) m12[x][y]=m1[x][y];
		for(y=0;y<m2y;y++) m12[x][m1y+y]=m2[x][y];
	}
}

EXPORT void __stdcall VInit(int Vlen, double* V, double InitVal){
	// Initialize all vector elements with same value
	for (int i = 0; i < Vlen; i++) V[i] = InitVal;
}

EXPORT void __stdcall MInit(int my, int mx, double** M, double InitVal){
	// Initialize all matrix elements with same value
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) M[y][x] = 0;
	}
}

EXPORT void __stdcall MbyV(int my, int mx, double** m, bool Transpose, double*v, double* ov){
	//-- Matrix-vector multiplication, http://mathinsight.org/matrix_vector_multiplication
	int x, y;
	if (Transpose){
		for (y = 0; y<mx; y++){
			ov[y] = 0;
			for (x = 0; x<my; x++){
				ov[y] += v[x]*m[x][y];
			}
		}
	} else{
		for (y = 0; y < my; y++){
			ov[y] = 0;
			for (x = 0; x < mx; x++){
				ov[y] += v[x] * m[y][x];
			}
		}
	}
}

EXPORT void __stdcall  VExtend(int l1, double* v1, int l2, double* v2, double* vsum){
	int x;
	for(x=0;x<l1;x++) vsum[x]=v1[x];
	for(x=0; x<l2;x++) vsum[l1+x]=v2[x];
}

EXPORT void __stdcall  VSplit(double* vsum, int l1, double* v1, int l2, double* v2){
	int x;
	for (x = 0; x<l1; x++) v1[x] = vsum[x];
	for (x = 0; x<l2; x++) v2[x]= vsum[l1 + x];
}

EXPORT void __stdcall VbyS(int Vlen, double* iV, double s, double* oV){
	// Multiplies a Vector by a Scalar
	for (int i = 0; i<Vlen; i++) oV[i] = iV[i] * s;
}

EXPORT void __stdcall VdivS(int Vlen, double* iV, double s, double* oV){
	// Divides a Vector by a Scalar
	for (int i = 0; i<Vlen; i++) oV[i] = iV[i] / s;
}

EXPORT double __stdcall VbyV(int Vlen, double* V1, double* V2){
	// Standard vector multiplication. Vectors have the same length. Returns a scalar
	double ret = 0;
	for (int i = 0; i < Vlen; i++){
		ret += V1[i] * V2[i];
	}
	return ret;
}

EXPORT void __stdcall VbyV2V(int Vlen, double* iV1, double* iV2, double* oV){
	// This simply multiplies vector elements one-by-one
	for (int i = 0; i < Vlen; i++) oV[i] = iV1[i] * iV2[i];
}

EXPORT void __stdcall VCopy(int Vlen, double* V1, double* V2){
	//-- V -> V
	for (int i = 0; i < Vlen; i++)	V2[i] = V1[i];
}

EXPORT void __stdcall VCopy(int Vlen, double* V1, double** V2){
	//-- V -> VP
	for (int i = 0; i < Vlen; i++)	(*V2[i]) = V1[i];
}

EXPORT void __stdcall VCopy(int Vlen, double** V1, double* V2){
	//-- VP -> V
	for (int i = 0; i < Vlen; i++)	V2[i] = (*V1[i]);
}

EXPORT void __stdcall VCopy(int Vlen, double** V1, double** V2){
	//-- VP -> VP
	for (int i = 0; i < Vlen; i++)	(*V2[i]) = (*V1[i]);
}

EXPORT void __stdcall VbyV2M(int Vylen, double* vY, int Vxlen, double* vX, bool transpose, double** oM){
	// This builds a 2x2 matrix by multiplying values in 2 vectors
	for (int y = 0; y < Vylen; y++){
		for (int x = 0; x < Vxlen; x++) {
			if (transpose) {
				oM[x][y] = vX[x] * vY[y];
			} else {
				oM[y][x] = vX[x] * vY[y];
			}
		}
	}
}


EXPORT void __stdcall VplusV(int Vlen, double* V1, double* V2, double* oV){
	// Sum of two vectors , V + V = V
	for (int i = 0; i < Vlen; i++) oV[i] = V1[i] + V2[i];
}

EXPORT void __stdcall VplusV(int Vlen, double* V1, double* V2, double** oV){
	// Sum of two vectors , V + V = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = V1[i] + V2[i];
}

EXPORT void __stdcall VplusV(int Vlen, double* V1, double** V2, double* oV){
	// Sum of two vectors , V + VP = V
	for (int i = 0; i < Vlen; i++) oV[i] = V1[i] + (*V2[i]);
}

EXPORT void __stdcall VplusV(int Vlen, double* V1, double** V2, double** oV){
	// Sum of two vectors , V + VP = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = V1[i] + (*V2[i]);
}

EXPORT void __stdcall VplusV(int Vlen, double** V1, double* V2, double* oV){
	// Sum of two vectors , VP + V = V
	for (int i = 0; i < Vlen; i++) oV[i] = (*V1[i]) + V2[i];
}

EXPORT void __stdcall VplusV(int Vlen, double** V1, double* V2, double** oV){
	// Sum of two vectors , VP + V = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = (*V1[i]) + V2[i];
}

EXPORT void __stdcall VplusV(int Vlen, double** V1, double** V2, double* oV){
	// Sum of two vectors , VP + VP = V
	for (int i = 0; i < Vlen; i++) oV[i] = (*V1[i]) + (*V2[i]);
}

EXPORT void __stdcall VplusV(int Vlen, double** V1, double** V2, double** oV){
	// Sum of two vectors , VP + VP = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = (*V1[i]) + (*V2[i]);
}

EXPORT void __stdcall VminusV(int Vlen, double* V1, double* V2, double* oV){
	// Sum of two vectors , V - V = V
	for (int i = 0; i < Vlen; i++) oV[i] = V1[i] - V2[i];
}

EXPORT void __stdcall VminusV(int Vlen, double* V1, double* V2, double** oV){
	// Sum of two vectors , V - V = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = V1[i] - V2[i];
}

EXPORT void __stdcall VminusV(int Vlen, double* V1, double** V2, double* oV){
	// Sum of two vectors , V - VP = V
	for (int i = 0; i < Vlen; i++) oV[i] = V1[i] - (*V2[i]);
}

EXPORT void __stdcall VminusV(int Vlen, double* V1, double** V2, double** oV){
	// Sum of two vectors , V - VP = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = V1[i] - (*V2[i]);
}

EXPORT void __stdcall VminusV(int Vlen, double** V1, double* V2, double* oV){
	// Sum of two vectors , VP - V = V
	for (int i = 0; i < Vlen; i++) oV[i] = (*V1[i]) - V2[i];
}

EXPORT void __stdcall VminusV(int Vlen, double** V1, double* V2, double** oV){
	// Sum of two vectors , VP - V = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = (*V1[i]) - V2[i];
}

EXPORT void __stdcall VminusV(int Vlen, double** V1, double** V2, double* oV){
	// Sum of two vectors , VP - VP = V
	for (int i = 0; i < Vlen; i++) oV[i] = (*V1[i]) - (*V2[i]);
}

EXPORT void __stdcall VminusV(int Vlen, double** V1, double** V2, double** oV){
	// Sum of two vectors , VP - VP = VP
	for (int i = 0; i < Vlen; i++) (*oV[i]) = (*V1[i]) - (*V2[i]);
}


EXPORT void __stdcall VAbsDiff(int Vlen, double* V1, double* V2, double* oV){
	// Absolute Difference between two vectors
	for (int i = 0; i < Vlen; i++) oV[i] = fabs(V1[i] - V2[i]);
}

EXPORT double __stdcall VdotV(int Vlen, double* iV1, double* iV2){
	//-- vector dot product. Returns a scalar
	double ret = 0;
	for (int i = 0; i < Vlen; i++) ret += iV1[i] * iV2[i];
	return ret;
}

EXPORT void __stdcall VbyVbyV(int Vlen, double* A, double* B, double* C, double* oV){
	//-- Vector Triple Product, http://mathworld.wolfram.com/VectorTripleProduct.html
	double* oV1 = (double*)malloc(Vlen*sizeof(double));
	double* oV2 = (double*)malloc(Vlen*sizeof(double));

	VbyS(Vlen, A, VdotV(Vlen, B, C), oV1);
	VbyS(Vlen, B, VdotV(Vlen, A, C), oV2);
	VplusV(Vlen, oV1, oV2, oV);

	free(oV1); free(oV2);
}

EXPORT void __stdcall V2VertM(int Vlen, double* V, double**oM){
	//-- transforms a vector into a 1-column matrix
	for (int i = 0; i < Vlen; i++) oM[i][0] = V[i];
}

EXPORT void __stdcall V2HorM(int Vlen, double* V, double**oM){
	//-- transforms a vector into a 1-row matrix
	for (int i = 0; i < Vlen; i++) oM[0][i] = V[i];
}

EXPORT void __stdcall VTraslate(){}

EXPORT void __stdcall MbyS(int my, int mx, double** M, double S, double** oM){
	//-- Matrix Scalar multiplication
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) oM[y][x] = M[y][x] * S;
	}
}

EXPORT double __stdcall Vnorm(int Vlen, double* V){
	// http://mathworld.wolfram.com/VectorNorm.html (4)
	double VSSum=0;
	for(int i=0;i<Vlen;i++) VSSum+=pow(V[i],2);
	return(sqrt(VSSum));
}

EXPORT double __stdcall Mnorm(int My, int Mx, double** M){
	double MSSum = 0;
	for (int y = 0; y < My; y++){
		for (int x = 0; x < Mx; x++){
			MSSum += pow(M[y][x], 2);
		}
	}
	return(sqrt(MSSum));
}
	
EXPORT double __stdcall Vmin(int Vlen, double* V){
	double min = 10000000000000000;
	for (int i = 0; i<Vlen; i++){
		if (V[i]<min) min = V[i];
	}
	return min;
}

EXPORT double __stdcall Vmax(int Vlen, double* V){
	double max = 0;
	for (int i = 0; i<Vlen; i++){
		if (V[i]>max) max = V[i];
	}
	return max;
}

EXPORT int __stdcall Vmax(int Vlen, int* V){
	int max = 0;
	for (int i = 0; i<Vlen; i++){
		if (V[i]>max) max = V[i];
	}
	return max;
}

EXPORT double __stdcall Vsum(int Vlen, double* V){
	double sum = 0;
	for (int i = 0; i<Vlen; i++){
		sum += V[i];
	}
	return (sum);
}

EXPORT double __stdcall Vavg(int Vlen, double* V){
	double sum = 0;
	for (int i = 0; i<Vlen; i++){
		sum += V[i];
	}
	return (sum/Vlen);
}

EXPORT double __stdcall Vmin_NoZero(int Vlen, double* V){
	double min = 10000000000000000;
	for (int i = 0; i<Vlen; i++){
		if (V[i]<min && V[i] != 0) min = V[i];
	}
	return min;
}

EXPORT bool __stdcall VisZero(int Vlen, double* V){
	bool ret = true;
	for (int i = 0; i<Vlen; i++){
		if (V[i] != 0) ret=false;
	}
	return ret;
}

//-- Matrix Element-by-Element operations
EXPORT void __stdcall MElSum(int my, int mx, double**m1, double** m2, double** msum){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) msum[y][x] = m1[y][x] + m2[y][x];
	}
}
EXPORT void __stdcall MElDiff(int my, int mx, double**m1, double** m2, double** mdiff){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) mdiff[y][x] = m1[y][x] - m2[y][x];
	}
}
EXPORT void __stdcall MElProd(int my, int mx, double**m1, double** m2, double** mprod){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) mprod[y][x] = m1[y][x] * m2[y][x];
	}
}
EXPORT void __stdcall MElDiv(int my, int mx, double**m1, double** m2, double** mdiv){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) mdiv[y][x] = m1[y][x] / m2[y][x];
	}
}
//---------------------------------------

EXPORT void __stdcall M2LVV(int my, int mx, double** M, double* oLV){
	//-- transforms a Matrix in its long vector version
	for (int y = 0; y<my; y++){
		for (int x = 0; x<mx; x++) oLV[y*mx + x] = M[y][x];
	}
}

EXPORT void __stdcall LVV2M(int my, int mx, double* LV, double** oM){
	//-- transforms a Long vector version of a matrix into a matrix
	for (int y = 0; y<my; y++){
		for (int x = 0; x < mx; x++) oM[y][x] = LV[y*mx + x];
	}
}

EXPORT void __stdcall M2HorLV(int my, int mx, double** M, double** oM){
	//-- transforms a Matrix in its long vector version, and the long vector into a 1-row matrix
	for (int y = 0; y<my; y++){
		for (int x = 0; x<mx; x++) oM[0][y*mx + x] = M[y][x];
	}
}

EXPORT void __stdcall MplusM(int my, int mx, double**m1, double** m2, double** msum){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++) msum[y][x] = m1[y][x] + m2[y][x];
	}
}

EXPORT void __stdcall MbyM(int m1y, int m1x, int m2y, int m2x, double**m1, double** m2, double** mbym){
	for (int y = 0; y < m1y; y++){
		for (int x2 = 0; x2 < m2x; x2++){
			mbym[y][x2] = 0;
			for (int x = 0; x < m1x; x++) mbym[y][x2] += m1[y][x] * m2[x][x2];
		}
	}
}

EXPORT void __stdcall V2DiagM(int Vlen, double* V, double** M){
	for (int y = 0; y < Vlen; y++){
		for (int x = 0; x < Vlen; x++){
			M[y][x] = (x == y)?V[x]:0;
		}
	}
}

EXPORT void __stdcall Transpose(int my, int mx, double** M, double** TM){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++){
			TM[x][y] = M[y][x];
		}
	}
}

EXPORT void __stdcall MCopy(int my, int mx, double** fromM, double** toM){
	for (int y = 0; y < my; y++){
		for (int x = 0; x < mx; x++){
			toM[y][x] = fromM[y][x];
		}
	}
}

EXPORT double __stdcall VDistance(int VLen, double* V1, double* V2){
	double ret = 0;
	for (int i = 0; i < VLen; i++) ret += (V1[i] - V2[i]);
	return ret;
}

EXPORT double __stdcall Cov(int Vlen, double* V1, double* V2){
	//-- calculates Covariance between two vectors
	double V1avg = Vavg(Vlen, V1);
	double V2avg = Vavg(Vlen, V2);
	double num = 0;
	for (int i = 0; i < Vlen; i++){
		num += (V1[i] - V1avg)*(V2[i] - V2avg);
	}
	return (num / (Vlen - 1));
}

EXPORT void __stdcall CovM(int Vcnt, int Vlen, double** oM, ...){
	//-- Builds a Covariance matrix for an arbitrary number of vectors
	//-- arguments after oM should be double vectors, one for each variable
	//-- http://www.itl.nist.gov/div898/handbook/pmc/section5/pmc541.htm

	int i, j, kaz;
	double** V = (double**)malloc(Vcnt*sizeof(double*)); for (i = 0; i < Vcnt; i++) V[i] = (double*)malloc(Vcnt*sizeof(double));;
	va_list arguments;

	//-- First, save all the vectors passed as arguments into V
	va_start(arguments, Vcnt);
	//-- discard first two arguments
	kaz = va_arg(arguments, int);
	kaz = va_arg(arguments, int);
	for (i = 0; i < Vcnt; i++){
		V[i] = va_arg(arguments, double*);
	}
	va_end(arguments);

	//-- then, calc Covariance for each pair of vectors in V, and put that in oM
	for (i = 0; i < Vcnt; i++){
		for (j = 0; j < Vcnt; j++){
			oM[i][j] = Cov(Vlen, V[i], V[j]);
		}
	}

	for (i = 0; i < Vcnt; i++) free(V[i]);
	free(V);
}

EXPORT double __stdcall Mdet(int mxy, double** M, double*** origM){
	// http://www.mathsisfun.com/algebra/matrix-determinant.html
	int x;
	int tx, ty;
	double ret=0;
	double corner;
	int skipx;

	if (mxy == 2){
		ret = M[0][0] * M[1][1] - M[0][1] * M[1][0];
	}
	else if (mxy<2){
		ret = M[0][0];
	}
	else{
		for (x = 0; x < mxy; x++){
			corner = M[0][x];

			//-- copy M in origM
			MCopy(mxy, mxy, M, origM[mxy-1]);

			//-- rebuild M
			for (ty = 0; ty < (mxy - 1); ty++){
				skipx = 0;
				for (tx = 0; tx < (mxy-1); tx++){
					if (tx == x) skipx=1;
					M[ty][tx] = M[ty +1][tx + skipx];
				}
			}
			//-- calc det for M
			ret += corner*((x % 2)?-1:1)*Mdet(mxy-1, M, origM);

			//-- get back to original M
			MCopy(mxy, mxy, origM[mxy-1], M);
		}
	}

	return ret;
}

void MBuildMinorM(int mxy, double** M, int ignorex, int ignorey, double** mM){
	int x, y;
	int skipx, skipy;

	skipy = 0;
	for (y = 0; y < (mxy - 1); y++){
		if (y == ignorey) skipy = 1;
		skipx = 0;
		for (x = 0; x < (mxy-1); x++){
			if (x == ignorex) skipx = 1;
			mM[y][x] = M[y + skipy][x + skipx];
		}
	}
}

EXPORT void __stdcall MInv(int mxy, double** M, double** InvM){
	// https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
	int i,n, x, y;
	double det = 0;

	//-- 0. malloc()s

	//-- 0.0 origM is needed by Mdet()
	double*** origM = (double***)malloc(mxy*sizeof(double**));
	for (n = 0; n<mxy; n++){
		origM[n] = (double**)malloc(mxy*sizeof(double*)); for (i = 0; i < mxy; i++) origM[n][i] = (double*)malloc(mxy*sizeof(double));
	}
	//-- 0.1 cofM is needed by (2)
	double** cofM = (double**)malloc(mxy*sizeof(double*)); for (i = 0; i < mxy; i++) cofM[i] = (double*)malloc(mxy*sizeof(double));

	//-- 0.2 mM and Mmin are needed by matrix of minors
	double*** mM = (double***)malloc(mxy*mxy*sizeof(double**));
	for (n = 0; n < (mxy*mxy); n++){
		mM[n] = (double**)malloc(mxy*sizeof(double*)); for (i = 0; i < mxy; i++) mM[n][i] = (double*)malloc(mxy*sizeof(double));
	}
	double** Mmin = (double**)malloc(mxy*sizeof(double*)); for (i = 0; i < mxy; i++) Mmin[i] = (double*)malloc(mxy*sizeof(double));
	
	
	//-- 0.3 tM is needed for Transpose
	double** tM = (double**)malloc(mxy*sizeof(double*)); for (i = 0; i < mxy; i++) tM[i] = (double*)malloc(mxy*sizeof(double));

	//-- 1. Matrix of Minors	
	n = 0;
	for (y = 0; y < mxy; y++){
		for (x = 0; x < mxy; x++){
			//-- 1.1 for each element of the original matrix, build a minor matrix, by eliminating row and column of the element
			MBuildMinorM(mxy, M, x, y, mM[n]);
			//-- 1.2 calculate the determinant of the minor matrix
			det = Mdet(mxy - 1, mM[n], origM);
			//-- 1.3 put those determinants into the matrix of minors
			Mmin[y][x] = det;
			n++;
		}
	}

	//-- 2. Matrix of Cofactors
	n = 0;
	for (y = 0; y < mxy; y++){
		for (x = 0; x < mxy; x++){
			cofM[y][x] = Mmin[y][x] * ((n%2)?-1:1);
			n++;
		}
	}

	//-- 3. Adjugate (Transpose)
	Transpose(mxy, mxy, cofM, tM);
	
	//-- 4. Multiply by 1/det
	det = Mdet(mxy, M, origM);
	if (det == 0){
		printf("\nMInv() cannot invert matrix! Simply copying original matrix into inverted matrix...\n");
		MCopy(mxy, mxy, M, InvM);
	}
	MbyS(mxy, mxy, tM, 1 / det, InvM);

	//-- free()s
	for (n = 0; n<mxy; n++){
		for (i = 0; i < mxy; i++) free(origM[n][i]);
		for (i = 0; i < mxy; i++) free(mM[n][i]);
		free(origM[n]); free(M[n]);
	}
	free(origM); free(mM);
	for (i = 0; i < mxy; i++){
		free(Mmin[i]);
		free(tM[i]);
		free(cofM[i]);
	}
	free(Mmin); free(tM); free(cofM);
}

int main(int argc, char* argv[]) {
	int x;
	int HiddenCount=3;
	int InputCount=5;
	int ContextCount=4;
/*	double** A=(double**)malloc(HiddenCount*sizeof(double*)); for(x=0;x<HiddenCount;x++) (double*)A[x]=(double*)malloc(InputCount*sizeof(double));
	double** B=(double**)malloc(HiddenCount*sizeof(double*)); for(x=0;x<HiddenCount;x++) (double*)B[x]=(double*)malloc(ContextCount*sizeof(double));
	double** C=(double**)malloc(HiddenCount*sizeof(double*)); for(x=0;x<HiddenCount;x++) (double*)C[x]=(double*)malloc((InputCount+ContextCount)*sizeof(double));

	A[0][0]=1; A[1][0]=2; A[2][0]=3;
	A[0][1]=4; A[1][1]=5; A[2][1]=6; 
	A[0][2]=7; A[1][2]=8; A[2][2]=9;
	A[0][3]=10; A[1][3]=11; A[2][3]=12;
	A[0][4]=13; A[1][4]=14; A[2][4]=15;
	B[0][0]=1; B[1][0]=2; B[2][0]=3;
	B[0][1]=4; B[1][1]=5; B[2][1]=6; 
	B[0][2]=7; B[1][2]=8; B[2][2]=9;
	B[0][3]=10; B[1][3]=11; B[2][3]=12;

	MExtend(HiddenCount, InputCount, ContextCount, A, B, C);

	double** A3x2=(double**)malloc(3*sizeof(double*)); for(x=0;x<3;x++) (double*)A3x2[x]=(double*)malloc(2*sizeof(double));
	A3x2[0][0]=1;
	A3x2[0][1]=0;
	A3x2[1][0]=-1;
	A3x2[1][1]=-3;
	A3x2[2][0]=2;
	A3x2[2][1]=1;
	double V3[3]={2, 1, 0};
	double VM[3];

	//MbyV(3, 2, A3x2, FALSE, V3, VM);
*/
	int Ax = 2; int Ay = 2;
	int Bx = 2; int By = 2;
	int Cx = 2; int Cy = 2;
	double** A = (double**)malloc(Ay * sizeof(double*)); for (int y = 0; y < Ay; y++) (double*)A[y] = (double*)malloc(Ax * sizeof(double));
	double** B = (double**)malloc(By * sizeof(double*)); for (int y = 0; y < Ay; y++) (double*)B[y] = (double*)malloc(Ax * sizeof(double));
	double** C = (double**)malloc(Cy * sizeof(double*)); for (int y = 0; y < Ay; y++) (double*)C[y] = (double*)malloc(Ax * sizeof(double));

	A[0][0] = 2; A[0][1] = -2;
	A[1][0] = 5; A[1][1] = 3;
	B[0][0] = -1; B[0][1] = 4;
	B[1][0] = 7; B[1][1] = -6;

//	MbyM(2, 2, A, 2, 2, B, C);
	for (int y = 0; y < 2; y++){
		for (x = 0; x<2; x++){
			printf("%1.0f ", C[y][x]);
		}
		printf("\n");
	}

	printf("Press any key to continue...\n"); getchar();;

	return 0;
}


