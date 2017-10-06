#undef EXPORT
#define EXPORT __declspec(dllexport)

//-- Overloaded VCopy, VminusV and VplusV, to handle arrays of pointers to values
EXPORT void __stdcall VCopy(int Vlen, double* V1, double* V2);
EXPORT void __stdcall VCopy(int Vlen, double* V1, double** V2);
EXPORT void __stdcall VCopy(int Vlen, double** V1, double* V2);
EXPORT void __stdcall VCopy(int Vlen, double** V1, double** V2);
//--
EXPORT void __stdcall VplusV(int Vlen, double* V1, double* V2, double* oV);
EXPORT void __stdcall VplusV(int Vlen, double* V1, double* V2, double** oV);
EXPORT void __stdcall VplusV(int Vlen, double* V1, double** V2, double* oV);
EXPORT void __stdcall VplusV(int Vlen, double* V1, double** V2, double** oV);
EXPORT void __stdcall VplusV(int Vlen, double** V1, double* V2, double* oV);
EXPORT void __stdcall VplusV(int Vlen, double** V1, double* V2, double** oV);
EXPORT void __stdcall VplusV(int Vlen, double** V1, double** V2, double* oV);
EXPORT void __stdcall VplusV(int Vlen, double** V1, double** V2, double** oV);
EXPORT void __stdcall VminusV(int Vlen, double* V1, double* V2, double* oV);
EXPORT void __stdcall VminusV(int Vlen, double* V1, double* V2, double** oV);
EXPORT void __stdcall VminusV(int Vlen, double* V1, double** V2, double* oV);
EXPORT void __stdcall VminusV(int Vlen, double* V1, double** V2, double** oV);
EXPORT void __stdcall VminusV(int Vlen, double** V1, double* V2, double* oV);
EXPORT void __stdcall VminusV(int Vlen, double** V1, double* V2, double** oV);
EXPORT void __stdcall VminusV(int Vlen, double** V1, double** V2, double* oV);
EXPORT void __stdcall VminusV(int Vlen, double** V1, double** V2, double** oV);
//--
EXPORT void __stdcall VInit(int Vlen, double* V, double InitVal);
EXPORT void __stdcall MInit(int my, int mx, double** M, double InitVal);
EXPORT void __stdcall  VExtend(int l1, double* v1, int l2, double* v2, double* vsum);
EXPORT void __stdcall  VSplit(double* vsum, int l1, double* v1, int l2, double* v2);
EXPORT void __stdcall VbyS(int Vlen, double* iV, double s, double* oV);
EXPORT void __stdcall VdivS(int Vlen, double* iV, double s, double* oV);
EXPORT double __stdcall VbyV(int Vlen, double* V1, double* V2);
EXPORT void __stdcall VbyV2V(int Vlen, double* iV1, double* iV2, double* oV);
EXPORT void __stdcall VbyV2M(int Vylen, double* vY, int Vxlen, double* vX, bool transpose, double** oM);
EXPORT void __stdcall VminusV(int Vlen, double* V1, double* V2, double* oV);
EXPORT void __stdcall VAbsDiff(int Vlen, double* V1, double* V2, double* oV);
EXPORT void __stdcall VbyVbyV(int Vlen, double* A, double* B, double* C, double* oV);
EXPORT double __stdcall VdotV(int Vlen, double* iV1, double* iV2);
EXPORT double __stdcall Vnorm(int Vlen, double* V);
EXPORT double __stdcall Mnorm(int My, int Mx, double** M);
EXPORT double __stdcall Vmin(int Vlen, double* V);
EXPORT double __stdcall Vmax(int Vlen, double* V);
EXPORT int __stdcall Vmax(int Vlen, int* V);
EXPORT double __stdcall Vsum(int Vlen, double* V);
EXPORT double __stdcall Vavg(int Vlen, double* V);
EXPORT double __stdcall Vmin_NoZero(int Vlen, double* V);
EXPORT bool __stdcall VisZero(int Vlen, double* V);
EXPORT void __stdcall V2VertM(int Vlen, double* V, double**oM);
EXPORT void __stdcall V2HorM(int Vlen, double* V, double**oM);
EXPORT void __stdcall V2DiagM(int Vlen, double* V, double** M);
EXPORT void __stdcall M2LVV(int my, int mx, double** M, double* oLV);
EXPORT void __stdcall LVV2M(int my, int mx, double* LV, double** oM);
//-- Matrix Element-by-Element operations
EXPORT void __stdcall MElSum(int my, int mx, double**m1, double** m2, double** msum);
EXPORT void __stdcall MElDiff(int my, int mx, double**m1, double** m2, double** mdiff);
EXPORT void __stdcall MElProd(int my, int mx, double**m1, double** m2, double** mprod);
EXPORT void __stdcall MElDiv(int my, int mx, double**m1, double** m2, double** mdiv);
//------------------------------------------------------------------------
EXPORT void __stdcall MSumH(int my, int mx, double** m, double* oHsum);
EXPORT void __stdcall MSumV(int my, int mx, double** m, double* oVsum);
//------------------------------------------------------------------------
EXPORT void __stdcall M2HorLV(int my, int mx, double** M, double** oM);
EXPORT void __stdcall MplusM(int my, int mx, double** M1, double** M2, double** MSum);
EXPORT void __stdcall MbyM(int m1y, int m1x, int m2y, int m2x, double**m1, double** m2, double** mbym);
EXPORT void __stdcall Transpose(int my, int mx, double** M, double** TM);
EXPORT void __stdcall MCopy(int my, int mx, double** fromM, double** toM);
EXPORT void __stdcall MInv(int mxy, double** M, double** InvM);
EXPORT void __stdcall MatrixInversion(double **A, int order, double **Y);
EXPORT void __stdcall MatrixInversion2(double **A, int order, double **Y);
EXPORT double __stdcall VDistance(int VLen, double* V1, double* V2);
EXPORT void __stdcall MExtend(int m12x, int m1y, int m2y, double** m1, double** m2, double** m12);
EXPORT void __stdcall MbyV(int my, int mx, double** m, bool Transpose, double*v, double* ov);
EXPORT void __stdcall MbyS(int my, int mx, double** M, double S, double** oM);
EXPORT double __stdcall Cov(int Vlen, double* V1, double* V2);
EXPORT void __stdcall CovM(int Vcnt, int Vlen, double** oM, ...);
