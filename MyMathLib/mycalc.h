#ifndef MYCALC_H
#define MYCALC_H

#ifdef __cplusplus
extern "C" {
#endif
	
	_declspec(dllimport) int int_add(int a, int b);
	_declspec(dllimport) int int_mult(int a, int b);

#ifdef __cplusplus
}
#endif


#endif // !MYCALC_H
