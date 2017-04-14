#include <iostream>

class Matrix{
	Matrix(int nrows, int ncols, double ini = 0);
	int r; // number of rows
	int c; // number of columns
	double *d; // array of double for the matrix elements
};

Matrix::Matrix(int nrows, int ncols, double ini):r(nrows), c(ncols){
	d = new double [nrows*ncols];
	double *p = d;
	for (int i = 0; i < nrows*ncols; ++i) 
		*p++ = ini;
}

int main(){
	std::cout << "Hello, world!" << std::endl;
	double tmp;
	std::cin >> tmp;
	std::cout << tmp;

	Matrix m1(3,4);
	std::cout<<m1.r<<" "<<m1.c<<endl:
	return 0;



}



