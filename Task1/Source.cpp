//1. N rectangles with sides parallel to the coordinate axes are given. 
//Determine how many parts these rectangles divide the plane into.

#include <iostream>

using namespace std;

struct Rectangle
{
	int x1, y1, x2, y2;
};

int CompInt(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int CompRectCoord(const void *x, const void *y)
{
	return ((Rectangle*)x)->x1 - ((Rectangle*)y)->x1;
}

int ArrUniq(int *arr, int Size)
{
	int k = 1, i = 0;
	while ( i < Size - 1 && k < Size - i)
	{
		while (k < Size - i && arr[i + k] == arr[i])
			k++;
		if (k >= Size - i)
			break;
		arr[i + 1] = arr[i + k];
		++i;
	}
	return i + 1;
}

bool IsZero(bool *arr1, int len)
{
	bool a = true;
	for (int i = 0; i < len; i++)
	{
		if (arr1[i] != 0)
			a = false;
	}
	return a;
}

void SetToZero(bool **arr, int len1, int len2)
{
		for (int i = 0; i < len1; i++)
			for (int j = 0; j < len2; j++)
				arr[i][j] = 0;
}


bool ArrComp(bool *arr1, bool *arr2, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (arr1[i] != arr2[i])
			return false;
	}
	return true;
}

bool Belongs(int x1, int y1, int x2, int y2, Rectangle a)
{
	if (x1 >= a.x1 && y1 <= a.y1 && x2 <= a.x2 && y2 >= a.y2)
		return true;
	else return false;
}


int CountUniqLines(bool **Matrix, int Lines, int Columns, int Y_Len)
{
	bool *visited = new bool[Lines];
	for (int i = 0; i < Lines; i++)
		visited[i] = 0;
	int Result = Lines;
	for (int i = 0; i < Lines; i++)
	{
		for (int j = i + 1; j < Lines; j++)
		{
			if (ArrComp(Matrix[i], Matrix[j], Columns) && (!visited[j] || !visited[i]) && ((j - i == 1 && i % Y_Len - 1 != Y_Len - 2) || (j - i == Y_Len - 1)))
			{
				Result--;
				visited[j] = true;
			}
		}
	}
	return Result;
}

int CountAreas(Rectangle *Input, int *X, int *Y, int InputLen)
{
	int Result;

	qsort(X, InputLen * 2 + 2, sizeof(int), *CompInt);
	qsort(Y, InputLen * 2 + 2, sizeof(int), *CompInt);
	qsort(Input, InputLen, sizeof(Rectangle), *CompRectCoord);

	int X_Len = ArrUniq(X, InputLen * 2 + 2);
	int Y_Len = ArrUniq(Y, InputLen * 2 + 2);

	int RectGridLen = (X_Len - 1) * (Y_Len - 1);
	bool **RectGrid = new bool*[RectGridLen];
	for (int i = 0; i < RectGridLen; i++)
	{
		RectGrid[i] = new bool[InputLen];
	}
	SetToZero(RectGrid, RectGridLen, InputLen);
	
	for (int i = 0; i < X_Len - 1; i++)
		for (int j = 0; j < Y_Len - 1; j++)
			for (int k = 0; k < InputLen; k++)
			{
				if (Belongs(X[i], Y[j + 1], X[i + 1], Y[j], Input[k]))
					RectGrid[i * (Y_Len - 1) + j][k] = 1;
			}

	return CountUniqLines(RectGrid, RectGridLen, InputLen, Y_Len);
}

void Get(int &N, int *&X, int *&Y, Rectangle *&Input)
{
	cout << "Enter the number of rectangles: " << endl;
	cin >> N;
	Input = new Rectangle[N];
	int Min_X = INT_MAX, Max_X = INT_MIN, Min_Y = INT_MAX, Max_Y = INT_MIN;
	X = new int[N * 2 + 2];
	Y = new int[N * 2 + 2];

	cout << "Enter coordinates of rectangles in format <x1, y1, x2, y2> (x1, y1 - left top vertex, x2, y2 - right bottom vertex): " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> Input[i].x1 >> Input[i].y1 >> Input[i].x2 >> Input[i].y2;

		if (Input[i].x1 > Max_X)
			Max_X = Input[i].x1;
		if (Input[i].x2 > Max_X)
			Max_X = Input[i].x2;
		if (Input[i].y1 > Max_Y)
			Max_Y = Input[i].y1;
		if (Input[i].y2 > Max_Y)
			Max_Y = Input[i].y2;

		if (Input[i].x1 < Min_X)
			Min_X = Input[i].x1;
		if (Input[i].x2 < Min_X)
			Min_X = Input[i].x2;
		if (Input[i].y1 < Min_Y)
			Min_Y = Input[i].y1;
		if (Input[i].y2 < Min_Y)
			Min_Y = Input[i].y2;

		X[2 * i] = Input[i].x1;
		X[2 * i + 1] = Input[i].x2;
		Y[2 * i] = Input[i].y1;
		Y[2 * i + 1] = Input[i].y2;
	}
	X[2 * N] = Min_X - 1;
	X[2 * N + 1] = Max_X + 1;
	Y[2 * N] = Min_Y - 1;
	Y[2 * N + 1] = Max_Y + 1;

}

int main()
{
	int N, NumOfAreas;
	int *X = NULL, *Y = NULL;
	Rectangle *Input = NULL;
	Get(N, X, Y, Input);
	NumOfAreas = CountAreas(Input, X, Y, N);
	cout << NumOfAreas << endl;
	system("pause");
	return 0;
}