// Simplex.cpp: Ð¾Ð¿Ñ€ÐµÐ´ÐµÐ»ÑÐµÑ‚ Ñ‚Ð¾Ñ‡ÐºÑƒ Ð²Ñ…Ð¾Ð´Ð° Ð´Ð»Ñ ÐºÐ¾Ð½ÑÐ¾Ð»ÑŒÐ½Ð¾Ð³Ð¾ Ð¿Ñ€Ð¸Ð»Ð¾Ð¶ÐµÐ½Ð¸Ñ.
//

#include "stdafx.h"
#include "locale.h"
#include "iostream"
#include "fstream"
#include "stdlib.h"

using namespace std;

void print(int n, int m, double **M)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	double **M,
		max = 0,
		el = 0,
		rat1 = 0,
		rat2 = 0;
	int n,
		m,
		l = 0,
		p = 1,
		iterator = 0,
		f = 0,
		s = 0;
	setlocale(LC_ALL, "rus");
	fstream txt("tab1.txt");
	if (!txt)
	{
		cout << "Файл не существует." << endl;
		system("pause");
		return 0;
	}
	txt >> n;
	txt >> m;
	M = new double*[n];
	for (int i = 0; i < n; i++)
	{
		M[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			txt >> M[i][j];
		}
	}
	cout << endl << "Исходная симплекс-таблица: " << endl;
	print(n, m, M);
	while (f != m - 1)
	{
		if (iterator == 0)
		{
			for (int i = 0; i < n - 1; i++)
			{
				if (M[i][0] <= 0)
					s += 1;
			}
			if (s != n - 1)
			{
				max = M[n - 1][1];
				for (int j = 2; j < m; j++)
				{
					if (M[n - 1][j] < max && M[n - 1][j] != 0)
					{
						max = M[n - 1][j];
						p = j;
					}
				}
				max = fabs(M[l][1]);
				for (int j = 2; j < m; j++)
				{
					if (fabs(M[l][j]) > max)
					{
						el = max = M[l][j];
						p = j;
					}
				}
				if (fabs(M[0][0]) != 0)
				{
					rat1 = fabs(M[0][0] / M[0][p]);
					el = M[0][p];
					l = 0;
				}
				for (int i = 1; i < n; i++)
				{
					if (fabs(M[i][0]) != 0 && M[i][0] > 0)
						rat2 = fabs(M[i][0] / M[i][p]);
					if (rat2 < rat1)
					{
						rat1 = rat2;
						el = M[i][p];
						l = i;
					}
				}
			}
			else
			{
				max = M[0][0];
				for (int i = 1; i < n - 1; i++)
				{
					if (M[i][0] < max)
					{
						max = M[i][0];
						l = i;
					}
				}
				el = max = M[l][1];
				for (int j = 2; j < m; j++)
				{
					if (M[l][j] < max)
					{
						el = max = M[l][j];
						p = j;
					}
				}
			}
			cout << endl << "Итерация " << iterator << "-ая" << endl;
			cout << "Разрешающая строка: " << l + 1 << endl;
			cout << "Разрешающий столбец: " << p + 1 << endl;
			cout << "Разрешающий элемент: " << el << endl;
			cout << "Целевая функция: " << M[n - 1][0] << endl;
		}
		else
		{
			if (s != n - 1)
			{
				f = 0;
				max = M[n - 1][1];
				p = 1;
				for (int j = 2; j < m; j++)
				{
					if (M[n - 1][j] < max && M[n - 1][j] != 0)
					{
						max = M[n - 1][j];
						p = j;
					}
				}
				if (fabs(M[0][0]) != 0)
				{
					rat1 = fabs(M[0][0] / M[0][p]);
					el = M[0][p];
					l = 0;
				}
				for (int i = 1; i < n; i++)
				{
					if (fabs(M[i][0]) != 0 && M[i][0] > 0)
						rat2 = fabs(M[i][0] / M[i][p]);
					if (rat2 < rat1)
					{
						rat1 = rat2;
						el = M[i][p];
						l = i;
					}
				}
			}
			else
			{
				f = 0;
				max = M[0][0];
				l = 0;
				for (int i = 1; i < n - 1; i++)
				{
					if (M[i][0] < max)
					{
						max = M[i][0];
						l = i;
					}
				}
				el = max = M[l][1];
				p = 1;
				for (int j = 2; j < m; j++)
				{
					if (M[l][j] < max)
					{
						el = max = M[l][j];
						p = j;
					}
				}
			}
			cout << endl << "Итерация " << iterator << "-ая" << endl;
			cout << "Разрешающая строка: " << l + 1 << endl;
			cout << "Разрешающий столбец: " << p + 1 << endl;
			cout << "Разрешающий элемент: " << el << endl;
			cout << "Целевая функция: " << M[n - 1][0] << endl;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (i != l && j != p)
					M[i][j] = M[i][j] - M[l][j] * M[i][p] / el;
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (i == l && j != p)
					M[i][j] = M[i][j] / el;
				if (i != l && j == p)
					M[i][j] = -1 * M[i][j] / el;
				if (i == l && j == p)
					M[i][j] = 1 / M[i][j];
				if (M[i][j] == 0)
					M[i][j] = fabs(M[i][j]);
			}
		}
		cout << endl << "Преобразованная симплекс-талица: " << endl;
		print(n, m, M);
		if (s != n - 1)
		{
			for (int j = 1; j < m; j++)
			{
				if (M[n - 1][j] >= 0)
					f += 1;
			}
		}
		else
		{
			for (int i = 0; i < n - 1; i++)
			{
				if (M[i][0] >= 0)
					f += 1;
			}
		}
		iterator += 1;
	}
	cout << endl << "Целевая функция: " << M[n - 1][0] << endl;
	delete[] M;
	system("pause");
	return 0;
}