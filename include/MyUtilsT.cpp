#pragma once

#include <vld.h>

#undef EXPORT
#define EXPORT __declspec(dllexport)

#ifdef __cplusplus
template <typename T>
EXPORT T __stdcall ArrayMax(int arrlen, T* arr) {
	T max = -10000;
	for (int i = 0; i < arrlen; i++) {
		if (arr[i] > max) max = arr[i];
	}
	return max;
}
template <typename T>
EXPORT T __stdcall ArrayMax(int arr1len, T* arr1, T** arr2) {
	T max = -10000;
	for (int i = 0; i < arr1len; i++) {
		for (int j = 0; j < arr1[i]; j++) {
			if (arr2[i][j] > max) max = arr2[i][j];
		}
	}
	return max;
}

template <typename T>
EXPORT T****** __stdcall MallocArray(int dim0, int dim1, int dim2, int dim3, int dim4, int dim5) {
	int l, i, j, k, m;
	T****** Arr = (T******)malloc(dim0 * sizeof(T*****));
	for (l = 0; l<dim0; l++) {
		Arr[l] = (T*****)malloc(dim1 * sizeof(T****));
		for (i = 0; i<dim1; i++) {
			Arr[l][i] = (T****)malloc(dim2 * sizeof(T***));
			for (j = 0; j<dim2; j++) {
				Arr[l][i][j] = (T***)malloc(dim3 * sizeof(T**));
				for (k = 0; k<dim3; k++) {
					Arr[l][i][j][k] = (T**)malloc(dim4 * sizeof(T*));
					for (m = 0; m < dim4; m++) {
						Arr[l][i][j][k][m] = (T*)malloc(dim5 * sizeof(T));
					}
				}
			}
		}
	}
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, int dim1, int dim2, int dim3, int dim4, int dim5, T Arr) {
	int i0, i1, i2, i3, i4;
	for (i0 = 0; i0 < dim0; i0++) {
		for (i1 = 0; i1 < dim1; i1++) {
			for (i2 = 0; i2 < dim2; i2++) {
				for (i3 = 0; i3 < dim3; i3++) {
					for (i4 = 0; i4 < dim4; i4++) {
						free(Arr[i0][i1][i2][i3][i4]);
					}
					free(Arr[i0][i1][i2][i3]);
				}
				free(Arr[i0][i1][i2]);
			}
			free(Arr[i0][i1]);
		}
		free(Arr[i0]);
	}
	free(Arr);
}

template <typename T>
EXPORT T***** __stdcall MallocArray(int dim0, int dim1, int dim2, int dim3, int dim4) {
	int l, i, j, k;
	T***** Arr = (T*****)malloc(dim0 * sizeof(T****));
	for (l = 0; l<dim0; l++) {
		Arr[l] = (T****)malloc(dim1 * sizeof(T***));
		for (i = 0; i<dim1; i++) {
			Arr[l][i] = (T***)malloc(dim2 * sizeof(T**));
			for (j = 0; j<dim2; j++) {
				Arr[l][i][j] = (T**)malloc(dim3 * sizeof(T*));
				for (k = 0; k<dim3; k++) {
					Arr[l][i][j][k] = (T*)malloc(dim4 * sizeof(T));
				}
			}
		}
	}
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, int dim1, int dim2, int dim3, int dim4, T Arr) {
	int i0, i1, i2, i3;
	for (i0 = 0; i0 < dim0; i0++) {
		for (i1 = 0; i1 < dim1; i1++) {
			for (i2 = 0; i2 < dim2; i2++) {
				for (i3 = 0; i3 < dim3; i3++) {
					free(Arr[i0][i1][i2][i3]);
				}
				free(Arr[i0][i1][i2]);
			}
			free(Arr[i0][i1]);
		}
		free(Arr[i0]);
	}
	free(Arr);
}
template <typename T>
EXPORT T**** __stdcall MallocArray(int dim0, int dim1, int dim2, int dim3) {
	int l, i, j;
	T**** Arr = (T****)malloc(dim0 * sizeof(T***));
	for (l = 0; l<dim0; l++) {
		Arr[l] = (T***)malloc(dim1 * sizeof(T**));
		for (i = 0; i<dim1; i++) {
			Arr[l][i] = (T**)malloc(dim2 * sizeof(T*));
			for (j = 0; j<dim2; j++) {
				Arr[l][i][j] = (T*)malloc(dim3 * sizeof(T));
			}
		}
	}
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, int dim1, int dim2, int dim3, T Arr) {
	int i0, i1, i2;
	for (i0 = 0; i0 < dim0; i0++) {
		for (i1 = 0; i1 < dim1; i1++) {
			for (i2 = 0; i2 < dim2; i2++) {
				free(Arr[i0][i1][i2]);
			}
			free(Arr[i0][i1]);
		}
		free(Arr[i0]);
	}
	free(Arr);
}
template <typename T>
EXPORT T*** __stdcall MallocArray(int dim0, int dim1, int dim2) {
	int l, i;
	T*** Arr = (T***)malloc(dim0 * sizeof(T**));
	for (l = 0; l<dim0; l++) {
		Arr[l] = (T**)malloc(dim1 * sizeof(T*));
		for (i = 0; i<dim1; i++) {
			Arr[l][i] = (T*)malloc(dim2 * sizeof(T));
		}
	}
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, int dim1, int dim2, T Arr) {
	int l, i;
	for (l = 0; l<dim0; l++) {
		for (i = 0; i<dim1; i++) {
			free(Arr[l][i]);
		}
		free(Arr[l]);
	}
	free(Arr);
}
template <typename T>
EXPORT T** __stdcall MallocArray(int dim0, int dim1) {
	int l;
	T** Arr = (T**)malloc(dim0 * sizeof(T*));
	for (l = 0; l<dim0; l++) {
		Arr[l] = (T*)malloc(dim1 * sizeof(T));
	}
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, int dim1, T Arr) {
	int l;
	for (l = 0; l<dim0; l++) {
		free(Arr[l]);
	}
	free(Arr);
}
template <typename T>
EXPORT T* __stdcall MallocArray(int dim0) {
	T* Arr = (T*)malloc(dim0 * sizeof(T));
	return Arr;
}
template <typename T>
EXPORT void __stdcall FreeArray(int dim0, T Arr) {
	free(Arr);
}
#endif