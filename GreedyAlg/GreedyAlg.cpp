#include <iostream>
#include <Windows.h>
#include <fstream>
#include <set>
#include <chrono>
#include <vector>
using namespace std;
void Start(int** a, int n);
void FromGod(int** a, int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			*(*(a + i) + j) = 0;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n - 1; j++)
		{
			*(*(a + i) + j) = rand() % 2;
			*(*(a + j) + i) = *(*(a + i) + j);
		}
	}
}
set<int> Greedy(int** a, int n)
{
	int* nodes = new int[n];
	set<int> vertexCover;
	int sum = 0;//1
	for (int i = 0; i < n; i++)//1+n+1+n=2n+2 (n раз)
		*(nodes + i) = 0;//1
	for (int i = 0; i < n; i++)//2n+2 (n раз)
	{
		for (int j = 0; j < n; j++)//2n+2 (n раз)
		{
			if(i!=j)//1
			*(nodes + i) += *(*(a + i) + j);//2
		}
		sum += *(nodes + i);//2
	}
	while (sum > 0)//n (n-1 раз) 
	{
		int max_node = -1, ind_node = -1;//2
		for (int i = 0; i < n; i++)//2n+2 (n раз)
			if (max_node < *(nodes + i))//1
			{
				max_node = *(nodes + i);//1
				ind_node = i;//1
			}
		vertexCover.insert(ind_node + 1);//2
		for (int i = 0; i < n; i++)//2n+2 (n раз)
		{
			*(nodes + i) -= *(*(a + ind_node) + i);//2
			sum -= *(*(a + ind_node) + i);//2
			*(*(a + i) + ind_node) = 0;//1
			*(*(a + ind_node) + i) = 0;//1
		}
		sum -= *(nodes + ind_node);//2
		*(nodes + ind_node) = 0;//1
	}
	return vertexCover;//1
}
void Generator()
{
	for (int n = 5; n < 20; n++)
	{
		int** a = new int* [n];
		for (int i = 0; i < n; i++)
			a[i] = new int[n];
		FromGod(a, n);
		Start(a, n);
		cout << "--------------------------------------------------------------------------"<<endl;
		for (int i = 0; i < n; i++)
			delete[] a[i];
		delete[]a;
	}
}
void Print(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void FromFile(int** a, int n)
{
	ifstream f("C:\\Users\\akaya\\OneDrive\\Desktop\\test.txt", ios::in);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			f >> a[i][j];
		}
	}

}
void FromKeybord(int** a, int n)
{
	int tmp;
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " строка:";
		for (int j = 0; j < n; j++)
		{
			cin >> tmp;
			*(*(a + i) + j) = tmp;
		}
		cout << endl;
	}
}
set<int> pribl(int** mas, int n)
{
	set<int> otvet;//С
	vector<vector<int>> edge;//С
	vector<vector<int>> temp_edge;//С
	srand(time(0));//С
	for (int i = 0; i < n - 1; i++)//1+n+n-1=2n
		for (int j = i + 1; j < n; j++)//2n+n^2/2-n/2+n+n^2/2-n/2 = n^2 + 2n (n^2/2-n/2 раз)
			if (mas[i][j] == 1)//1
				edge.push_back({ i,j });//C2
	while (!edge.empty())//C3 (n/2 раз)
	{
		int r = rand() % edge.size();//C4
		int x = edge[r][0];//1
		int y = edge[r][1];//1
		otvet.insert(x);//C4
		otvet.insert(y);//C4
		temp_edge.clear();//C4
		for (int k = 0; k < edge.size(); k++)//n/2 + n^2/8 - n/4 + n/2 + n^2/8 - n/4 = n^2/4 + n/2 (n^2/8-n/4 раз)
			if (!(edge[k][0] == x || edge[k][1] == x || edge[k][0] == y || edge[k][1] == y))//8
			{
				temp_edge.push_back(edge[k]);//C6
			}
		edge = temp_edge;//1
	}
	return otvet;//1
}
set<int> full(int** mas, int n)
{
	bool log = false;//1
	bool log1 = false;//1
	set<int> otvet;//С
	vector<vector<int>> edge;//С
	vector<vector<int>> temp_edge;//С
	vector<int> comb;//С
	for (int i = 0; i < n - 1; i++)//1+n+n-1=2n
		for (int j = i + 1; j < n; j++)//2n+n^2/2-n/2+n+n^2/2-n/2 = n^2 + 2n (n^2/2-n/2 раз)
			if (mas[i][j] == 1)//1
				edge.push_back({ i,j });//С2


		for (int l = 0; l < n; l++)//1+n+1+n=2n+2
		{
			if (!log)//2
			{
				temp_edge.clear();//C3
				for (int k1 = 0; k1 < edge.size(); k1++)//1 + n^2/2-n/2 + 1 + n^2/2-n/2 = 2 + n^2 - n (n^2/2-n/2 раз)
					if (!(edge[k1][0] == l || edge[k1][1] == l))//4
						temp_edge.push_back(edge[k1]);//C4

				if (temp_edge.empty())//C5
				{
					log = true;//1
					comb.push_back(l);//C6
				}
			}
		}
		if (!log)//2
			for (int k = 2; k < n; k++)//1+n-1+n-2 (n-2 раза)
			{
			if (!log)//2
			{
				comb.clear();//С7
				for (int i = 0; i <= k - 1; i++)//n-2 + n^2/2 - n/2 - 1 + n - 2 + n^2/2 - n/2 - 1 = n^2 + n - 6 ( n^2/2 - n/2 - 1 раз)
					comb.push_back(i);//С8

				log = true;//1
				for (int k1 = 0; k1 < edge.size(); k1++)//2 + n^2 - n (n^2/2-n/2 раз)
				{
					log1 = false;//1
					for (int l = 0; l < comb.size(); l++)//n^4 /2 - 7/2 n^2 + 3n (n^4/4 - n^3/2 - n^2/4 + n/2 раз)
						if (edge[k1][0] == comb[l] || edge[k1][1] == comb[l])//3
							log1 = true;//1
					log = log && log1;//2
				}
				if (!log)//2
				{
					while (comb[0] < n - k && !log)//4*(n-2) + 4*(2^n-2n-4 при n>3)+ (2^n-2n-4 раз при n>3)
					{
						int count = k - 1;//2
						comb[count]++;//1
						while (count >= 0 && comb[count] >= n)//3*(2^n-2n-4) + ???? (? раз)
						{
							count--;//1
							comb[count]++;//1
						}
						for (count = count + 1; count <= k - 1; count++)//2(2^n-2n-4) + ????????? (? раз)
							comb[count] = comb[count - 1] + 1;//3
						log = true;//1
						for (int k2 = 0; k2 < edge.size(); k2++)//2 + n^2 - n (n^2/2-n/2 раз)
						{
							log1 = false;//1
							for (int l = 0; l < comb.size(); l++)// n^2*2^n
								if (edge[k2][0] == comb[l] || edge[k2][1] == comb[l])//3
									log1 = true;//1
							log = log && log1;//2
						}
					}
				}
			}			
			}	

	for (int l = 0; l < comb.size(); l++)//1+n+n-1=2n (n-1 раз)
		otvet.insert(comb[l]);//С9
	return otvet;//1
}
void Start(int** a, int n)
{
	auto start = chrono::steady_clock::now();
	set<int> ans = pribl(a, n);
	cout << "Результат приближенного алгоритма: ";
	for (int vertex : ans) {
		cout << vertex + 1 << " ";
	}
	cout << "\nВремя работы: " << chrono::duration <double, milli>(chrono::steady_clock::now() - start).count() << " ms" << endl;

	
	start = chrono::steady_clock::now();
	ans = full(a, n);
	cout << "\nРезультат переборного алгоритма: ";
	for (int vertex : ans) {
		cout << vertex+1 << " ";
	}
	cout << "\nВремя работы: " << chrono::duration <double, milli>(chrono::steady_clock::now() - start).count() << " ms" << endl;
	start = chrono::steady_clock::now();
	ans = Greedy(a, n);
	cout << "\nРезультат жадного алгоритма: ";
	for (int vertex : ans) {
		cout << vertex << " ";
	}
	cout << "\nВремя работы: " << chrono::duration <double, milli>(chrono::steady_clock::now() - start).count() << " ms" << endl;
}
int main()
{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		//Generator();
		{
			int n;
			cout << "Введите n: ";
			cin >> n;
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];
			cout << "Выберите заполнение массива:\n1. С клавиатуры\n2. Из файла\n3. Случайно\n";
			int pick;
			cin >> pick;
			switch (pick)
			{
			case 1:
				FromKeybord(a, n);
				break;
			case 2:
				FromFile(a, n);
				break;
			case 3:
				FromGod(a, n);
			default:
				break;
			}
			Print(a, n);
			Start(a, n);
		}
}



