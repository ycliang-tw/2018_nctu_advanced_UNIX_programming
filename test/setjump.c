#include <setjmp.h>
#include <stdio.h>

static jmp_buf jb;
//int a = 1;

int f1(){
	volatile int a = 1;
	volatile int b = 2;
	volatile int c = 3;
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	if(setjmp(jb) != 0){
		printf("a = %d, b = %d, c = %d\n", a, b, c);
		return 1;
	}
	a = 101, b = 102, c = 103;
//	printf("a = %d, b = %d, c = %d\n", a, b, c);
	return 0;
}

int f2(int p, int q, int r, int s){
	volatile int f = 201;
	volatile int g = 202;
	volatile int h = 203;
	longjmp(jb, 1);
	return 0;
}

void f3(){
	longjmp(jb, 1);
}

int main(){
	if(f1() != 0)	return 0;
	f2(501, 502, 503, 504);
	//f3();
	return 0;
}
