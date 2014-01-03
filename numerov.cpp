/*
 numerov.cpp
 Izabella Balce
 i.balce@jacobs-university.de
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "math.h"

using namespace std;
int main() {
	/*
	 * X= Array with the reduced grid point coordinates
	 * G= Array with the values of (X^2-2*Er)
	 * Y= Array with the values of Psi at each grid point
	 * M= Number of grid points
	 * s= integration step
	 * Er= Guess Eigenvalue
	 */
	vector<float> x, y, G;
	int M;
	float s, x0, Er;
	/*
	 * read the value of the integration step (s)
	 * the initial value of the x coordinate
	 * x(0) and the number of intervals(M)
	 */
	string input;
	cout << "Key in integration step: ";
	getline(cin, input);
	stringstream ss(input);
	ss >> s;
	cout << "Key in # of intervals: ";
	getline(cin, input);
	stringstream sm(input);
	sm >> M;
	G.resize(M - 1);
	y.resize(M - 1);
	cout << "Key in initial x coordinate: ";
	getline(cin, input);
	stringstream sx(input);
	sx >> x0;
	x.push_back(x0);
	y[0] = 0;
	y[1] = 1e-4;
	x.push_back(x[0] + s);

	while (Er >= 0) { /* Exit condition from the loop*/
		cout << "Insert a value of Er :";
		getline(cin, input);
		stringstream se(input);
		se >> Er;
		if (Er > 0) {
			G[0] = pow(x[0], 2) - 2 * Er;
			G[1] = pow(x[1], 2) - 2 * Er;
//			cout << G[0] << "\t" << y[0] << endl;
//			cout << G[1] << "\t" << y[1] << endl;
			int nodes = 0;
			for (int i = 2; i < M + 1; i++) { /* Loop on the number of points*/
				x.push_back(x[i - 1] + s);
				G[i] = pow(x[i], 2) - (2 * Er);
				y[i] = ((2 * y[i - 1] - y[i - 2])
						+ (5 * G[i - 1] * y[i - 1] * pow(s, 2) / 6)
						+ (G[i - 2] * y[i - 2] * pow(s, 2) / 12))
						/ (1 - (G[i] * pow(s, 2) / 12));
//				cout << G[i] << "\t" << y[i] << endl;
				if (y[i] * y[i - 1] < 0) { /*Check the presence of nodes*/
					nodes++;
//					cout << G[i] << "\t" << G[i - 1] << endl;
				}
			}
			/*
			 * Print the value of Er, the number of nodes
			 * and the value of Y at Xmax.
			 */
			cout << Er << "\t" << nodes << "\t" << y[M] << endl;
		}
	}
	cout << "end Numerov";

	return 0;
}
