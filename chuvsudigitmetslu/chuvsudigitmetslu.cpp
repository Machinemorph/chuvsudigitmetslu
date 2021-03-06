// chuvsudigitmetslu.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void gauss(double *x, double **a, int n)
{
	double k;
	for (int ii = 0; ii < n; ii++)
	{
		k = a[0 + ii][0 + ii];
		for (int j = 0 + ii; j < n + 1; j++)
			a[0 + ii][j] = a[0 + ii][j] / k;
		for (int i = 1 + ii; i < n; i++)
		{
			k = a[i][0 + ii];
			for (int j = 0 + ii; j < n + 1; j++)
				a[i][j] = a[i][j] - (a[0 + ii][j] * k);
		}
	}
	for (int ii = n - 1; ii >= 1; ii--)
	{
		for (int i = ii - 1; i >= 0; i--)
		{
			k = a[i][ii];
			for (int j = n; j >= i + 1; j--)
			{
				a[i][j] = a[i][j] - (a[ii][j] * k);

			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		x[i] = a[i][n];
	}
}

void iter(double *x0, double *x1, double **a, int n, double e)
{
	bool k = true;
	for (int i = 0; i < n; i++)
	{
		double s = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j) s += a[i][j];
		}
		if (a[i][i] < s) k = false;
	}
	if (k) 
	{
		double **b = new double*[n];
		for (int i = 0; i < n; i++)
		{
			b[i] = new double[n + 1];
			for (int j = 0; j < n + 1; j++)
			{
				if (i == j) b[i][j] = 0;
				else b[i][j] = - a[i][j] / a[i][i];
			}
		}
		bool k1 = true;
		do
		
		//for (int ii = 0; ii < 3; ii++)
		{
			for (int i = 0; i < n; i++)
			{
				x1[i] = 0;
				for (int j = 0; j < n; j++)
				{
					x1[i] += b[i][j] * x0[j];
				}
				x1[i] += b[i][n];
				k1 = k1 && (abs(x1[i] - x0[i]) > e);
				x0[i] = x1[i];
			}
		} while (k1);
	}
}

void zeid(double *x0, double *x1, double **a, int n, double e)
{
	bool k = true;
	for (int i = 0; i < n; i++)
	{
		double s = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j) s += a[i][j];
		}
		if (a[i][i] < s) k = false;
	}
	if (k)
	{
		double **b = new double*[n];
		for (int i = 0; i < n; i++)
		{
			b[i] = new double[n + 1];
			for (int j = 0; j < n + 1; j++)
			{
				if (i == j) b[i][j] = 0;
				else b[i][j] = -a[i][j] / a[i][i];
			}
		}
		bool k1 = true;
		do

			//for (int ii = 0; ii < 3; ii++)
		{
			for (int i = 0; i < n; i++)
			{
				x1[i] = 0;
				for (int j = 0; j < n; j++)
				{
					if (j >= i) x1[i] += b[i][j] * x0[j];
					else x1[i] += b[i][j] * x1[j];
				}
				x1[i] += b[i][n];
				k1 = k1 && (abs(x1[i] - x0[i]) > e);
				x0[i] = x1[i];
			}
		} while (k1);
	}
}

int main()
{
	int start = clock();
	ifstream inp("inp.txt");
	int n = 3;
	double e = 0.0001;
	double **a = new double*[n];
	double *xg = new double[n];
	double *x0 = new double[n];
	double *x0z = new double[n];
	double *x1 = new double[n];
	double *x1z = new double[n];
	x0[0] = 0.9;
	x0[1] = 4.9;
	x0[2] = -0.9;
	x0z[0] = 0.9;
	x0z[1] = 4.9;
	x0z[2] = -0.9;
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n + 1];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			inp >> a[i][j];
		}
	}
	iter(x0, x1, a, n, e);
	zeid(x0z, x1z, a, n, e);
	gauss(xg, a, n);
	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	cout << "Gaussom:" << endl;
	for (int i = 0; i < n; i++)
		cout << 'x' << i + 1 << " = " << xg[i] << endl;
	cout << "Iteraciyami:" << endl;
	for (int i = 0; i < n; i++)
		cout << 'x' << i + 1 << " = " << -x1[i] << endl;
	cout << "Zeidel':" << endl;
	for (int i = 0; i < n; i++)
		cout << 'x' << i + 1 << " = " << -x1z[i] << endl;
	cout << "zatracheno " << clock() - start << endl;
	system("pause");
	return 0;
}

