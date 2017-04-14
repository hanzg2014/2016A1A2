
#include <iostream>
#include <cmath>
#include "UTRandom1.h"
#include "UTNormals.h"

using namespace std;

//Homework 1
double BlackSholesCall(double Expiry, double Strike, double Spot, double Vol, double r){
    double s = Vol*sqrt(Expiry); 
    double d1 = (log(Spot/Strike) + r*Expiry + 0.5*s*s) / s;
    double d2 = d1 - s;
    return Spot*CumulativeNormal(d1) - Strike*exp(-r*Expiry) * CumulativeNormal(d2);
}

double SimpleMonteCarlo1(double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths){
	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*std::exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++){
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance*thisGaussian);
		double thisPayoff = thisSpot - Strike;
		thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

int main(){
	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry:\n";
	cin >> Expiry;

	cout << "\nEnter strike:\n";
	cin >> Strike;

	cout << "\nEnter spot:\n";
	cin >> Spot;

	cout << "\nEnter vol:\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths:\n";
	cin >> NumberOfPaths;

	double result1 = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths);
	double result2 = BlackSholesCall(Expiry, Strike, Spot, Vol, r);

	cout << "\nThe price by MonteCarlo is " << result1 << "\n";
	cout << "The price by BlackSholesCall is " << result2 << "\n\n";

	return 0;
}


/*********************************************************

NM00010:HW1 hanzg$ g++ UTMain1.cpp UTNormals.cpp UTRandom1.cpp
NM00010:HW1 hanzg$ ./a.out

Enter expiry:
5

Enter strike:
50

Enter spot:
50

Enter vol:
0.25

r
0.05

Number of paths:
100000

The price by MonteCarlo is 16.3212
The price by BlackSholesCall is 16.252

*********************************************************/




