#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include <locale.h>
#include <chrono>
#include <map>
using namespace std;

long hash1(string key){
    long ans = 152 * (key[0] - 'A') + 172 * (key[1] - 'A') + 181*(key[2] - 'A');
    return ans;
}

long hash2(string key){
    long ans = 1;
    for (int i = 0; i < 3; i++)
        ans = 3 * (key[i] - 'A') + 19 * ans;

    return ans;
}


class Flower{
private:
    string name;
    string color;
    string smell;
    string region;
    long hash_1;
    long hash_2;

public:
    Flower ()
    {
        name = "";
        color = "";
        smell = "";
        region = "";
        hash_1 = 0;
        hash_2 = 0;
    }
    Flower (string n, string c, string s, string r, long h1, long h2)
    {
        name = n;
        color = c;
        smell = s;
        region = r;
        hash_1 = h1;
        hash_2 = h2;
    }
    Flower (const Flower& f)
    {
        name = f.GetName();
        color = f.GetColor();
        smell = f.GetSmell();
        region = f.GetRegion();
        hash_1 = f.GetHash1();
        hash_2 = f.GetHash2();
    }
    ~Flower () {};
    string GetName() const
    {
        return name;
    }
    string GetColor() const
    {
        return color;
    }
    string GetSmell() const
    {
        return smell;
    }
    string GetRegion() const
    {
        return region;
    }
    long GetHash1() const
    {
        return hash_1;
    }
    long GetHash2() const
    {
        return hash_2;
    }
    Flower& operator= (Flower f)
    {
        name = f.GetName();
        color = f.GetColor();
        smell = f.GetSmell();
        region = f.GetRegion();
        hash_1 = f.GetHash1();
        hash_2 = f.GetHash2();
    }
    friend ostream& operator<< (ostream &out, const Flower &A);
};
ostream& operator<< (ostream &out, const Flower &A){
    out << A.GetName() << " " << A.GetColor() << " " << A.GetSmell() << " " << A.GetRegion() << " " << A.GetHash1() << " " << A.GetHash2() << endl;
    return out;
}
bool operator> (Flower f1, Flower f2)
    {
        if (f1.GetName() > f2.GetName())
            return true;
        else if(f1.GetName() == f2.GetName() && f1.GetColor() > f2.GetColor())
            return true;
        else if(f1.GetName() == f2.GetName() && f1.GetColor() == f2.GetColor() && f1.GetSmell() > f2.GetSmell())
            return true;
        return false;
    }
bool operator>= (Flower f1, Flower f2)
    {
        if (f1.GetName() >= f2.GetName())
            return true;
        else if(f1.GetName() == f2.GetName() && f1.GetColor() >= f2.GetColor())
            return true;
        else if(f1.GetName() == f2.GetName() && f1.GetColor() == f2.GetColor() && f1.GetSmell() >= f2.GetSmell())
            return true;
        return false;
    }
bool operator< (Flower f1, Flower f2)
    {
        if (f2 > f1)
            return true;
        return false;
    }
 bool operator<= (Flower f1, Flower f2)
    {
        if (f2 >= f1)
            return true;
        return false;
    }
long findSmallestPosition(vector<Flower> &A, long startPosition, long vectorLength)
{
	long smallestPosition = startPosition;

	for(long i = startPosition; i < vectorLength; i++)
	{
		if(A[i] < A[smallestPosition])
			smallestPosition = i;
	}
	return smallestPosition;
}

void selectionSort(vector<Flower> &A, long vectorLength)
{
	for(long i = 0; i < vectorLength; i++)
	{
		long smallestPosition = findSmallestPosition(A, i, vectorLength);
		Flower x = A[smallestPosition];
		A[smallestPosition] = A[i];
		A[i] = x;
	}
	return;
}
int Partition(vector<Flower> &A, int start, int pivot)
{
	int i = start;
	while(i < pivot)
	{
		if(A[i] > A[pivot] && i == pivot-1)
		{
			Flower x = A[i];
			A[i] = A[pivot];
			A[pivot] = x;
			pivot--;
		}

		else if(A[i] > A[pivot])
		{
			Flower x = A[pivot - 1];
			A[pivot - 1] = A[pivot];
			A[pivot] = x;

			x = A[i];
			A[i] = A[pivot];
			A[pivot] = x;
			pivot--;
		}

		else i++;
	}
	return pivot;
}

void quickSort(vector<Flower> &A, int start, int End)
{
	if(start < End)
	{
		int pivot = Partition(A, start, End);

		quickSort(A, start, pivot - 1);
		quickSort(A, pivot + 1, End);
	}
}

void heapify(vector<Flower> &A, long vectorLength, long root)
{
	long largest = root;
	long l = 2*root + 1;
	long r = 2*root + 2;

	if (l < vectorLength && A[l] > A[largest])
		largest = l;

	if (r < vectorLength && A[r] > A[largest])
		largest = r;

	if (largest != root)
	{
		Flower x = A[root];
		A[root] = A [largest];
		A[largest] = x;
		heapify(A, vectorLength, largest);
	}
}

void heapSort(vector <Flower> &A, long vectorLength)
{
	for(long i = vectorLength / 2 - 1; i >= 0; i--)
		heapify(A, vectorLength, i);

	for(long i = vectorLength - 1; i >= 0; i--)
	{
		Flower x = A[i];
		A[i] = A[0];
		A[0] = x;
		heapify(A, i, 0);
	}
}

int linearSearch(vector <Flower> &A, long n, string key){
    for (long i = 0; i < n; i++)
        if (A[i].GetName() == key)
            return i;
    return -1;
}

int binarySearch(vector <Flower> A, long n, string key){

    long l = 0, r = n, m;

    while (l <= r){
        m = (l + r) / 2;

        if (A[m].GetName() == key)
            return m;
        if (A[m].GetName() > key)
            r = m - 1;
        else
            l = m + 1;
    }

    return -1;
}
class HashTable1{
public:
    Flower** table;
    long kol[20000] = {0};

    HashTable1(){
    }

    HashTable1(vector<Flower> f, long n)
    {
        int counter = 0;

        table = new Flower* [20000];

        cout << "Sozdanie hash tablitsi dlya viborki objemom " << n << endl;
        for (long i = 0; i < 20000; i++)
            table[i] = nullptr;
        for (long i = 0; i < n; i++){
            long hash = hash1(f[i].GetName());
            if (table[hash] == nullptr)
            {
                table[hash] = new Flower [1];
                table[hash][0] = f[i];
                kol[hash] = 1;
            }
            else
            {
                counter++;
                long last = kol[hash];
                Flower* tmp = new Flower [last + 1];
                for (long j = 0; j < last; j++)
                    tmp[j] = table[hash][j];
                tmp[last] = f[i];
                table[hash] = tmp;
                kol[hash]++;
            }
        }

        cout << counter << " collisions" << endl;
    }
};

class HashTable2{
public:
    Flower** table;
    long kol[37000] = {0};

    HashTable2(){

    }

    HashTable2(vector<Flower> f, long n){
        int counter = 0;
        table = new Flower* [37000];
        cout << "Sozdanie hash tablitsi dlya viborki objemom " << n << endl;

        for (long i = 0; i < 37000; i++)
            table[i] = nullptr;

        for (long i = 0; i < n; i++){
            long hash = hash2(f[i].GetName());
            if (table[hash] == nullptr){
                table[hash] = new Flower [1];
                table[hash][0] = f[i];
                kol[hash] = 1;
            }
            else
            {
                counter++;
                long last = kol[hash];
                Flower* tmp = new Flower [last + 1];
                for (long j = 0; j < last; j++)
                    tmp[j] = table[hash][j];
                tmp[last] = f[i];
                table[hash] = tmp;
                kol[hash]++;
            }
        }
        cout << counter << " collisions" << endl;
    }
};
Flower poisk(HashTable1 ht, string key){
    long hash = hash1(key);
    if (ht.table[hash] != nullptr)
    {
        for (int i = 0; i < ht.kol[hash]; i++)
            if (ht.table[hash][i].GetName() == key)
                return ht.table[hash][i];
    }
    return Flower();
}

Flower poisk(HashTable2 ht, string key){
    long hash = hash2(key);
    if (ht.table[hash] != nullptr)
    {
        for (int i = 0; i < ht.kol[hash]; i++)
            if (ht.table[hash][i].GetName() == key)
                return ht.table[hash][i];
    }
    return Flower();
}
int main()
{
    long vibor;
    cout << "Vibor:\n1. hs1\n2. hs2\n";
    cin >> vibor;
    vector<Flower> f1,f2,f3,f4,f5,f6,f7;
    ifstream fin100("f100.txt"),
             fin500("f500.txt"),
             fin1k("f1000.txt"),
             fin10k("f10000.txt"),
             fin20k("f20000.txt"),
             fin50k("f50000.txt"),
            fin100k("f100000.txt");
    for (long i = 0; i < 100; i++)
    {
        string a,b,c,d;
        fin100 >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f1.push_back(x);
    }
    for (long i = 0; i < 500; i++)
    {
        string a,b,c,d;
        fin500 >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f2.push_back(x);
    }
    for (long i = 0; i < 1000; i++)
    {
        string a,b,c,d;
        fin1k >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f3.push_back(x);
    }
    for (long i = 0; i < 10000; i++)
    {
        string a,b,c,d;
        fin10k >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f4.push_back(x);
    }
    for (long i = 0; i < 20000; i++)
    {
        string a,b,c,d;
        fin20k >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f5.push_back(x);
    }
    for (long i = 0; i < 50000; i++)
    {
        string a,b,c,d;
        fin50k >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f6.push_back(x);
    }
    for (long i = 0; i < 100000; i++)
    {
        string a,b,c,d;
        fin100k >> a >> b >> c >> d;
        long hs1 = hash1(a);
        long hs2 = hash2(b);
        Flower x(a,b,c,d,hs1,hs2);
        f7.push_back(x);
    }
     if (vibor == 1){
        HashTable1 ht1(f1, 100), ht2(f2, 500), ht3(f3, 1000), ht4(f4, 10000), ht5(f5, 20000), ht6(f6, 50000), ht7(f7, 100000);

        cout << "Viborka objemom 100:\t";
        auto nach = chrono::steady_clock::now();
        auto tmp = poisk(ht1, "YPV");
        auto kon = chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 500:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht2, "UKF");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 1000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht3, "LZX");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 10000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht4, "WJB");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 20000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht5, "WYV");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 50000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht6, "XOD");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 100000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht7, "BEC");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

    }
    else if (vibor == 2){
        HashTable2 ht1(f1, 100), ht2(f2, 500), ht3(f3, 1000), ht4(f4, 10000), ht5(f5, 20000), ht6(f6, 50000), ht7(f7, 100000);

        cout << "Viborka objemom 100:\t";
        auto nach = chrono::steady_clock::now();
        auto tmp = poisk(ht1, "YPV");
        auto kon = chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 500:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht2, "UKF");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 1000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht3, "LZX");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 10000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht4, "WJB");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 20000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht5, "WYV");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 50000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht6, "XOD");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Viborka objemom 100000:\t";
        nach = chrono::steady_clock::now();
        tmp = poisk(ht7, "BEC");
        kon = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(kon - nach);
        cout << elapsed_ms.count() << " nanoseconds\n";

    }
    fin100.close();
    fin500.close();
    fin1k.close();
    fin10k.close();
    fin20k.close();
    fin50k.close();
    fin100k.close();
    ofstream o100("out100.txt"),
             o500("out500.txt"),
             o1k("out1000.txt"),
             o10k("out10000.txt"),
             o20k("out20000.txt"),
             o50k("out50000.txt"),
             o100k("out100000.txt");
    for (long i = 0; i < 100; i++)
    {
        o100 << f1[i];
    }
    for (long i = 0; i < 500; i++)
    {
        o500 << f2[i];
    }
    for (long i = 0; i < 1000; i++)
    {
        o1k << f3[i];
    }
    for (long i = 0; i < 10000; i++)
    {
        o10k << f4[i];
    }
    for (long i = 0; i < 20000; i++)
    {
        o20k << f5[i];
    }
    for (long i = 0; i < 50000; i++)
    {
        o50k << f6[i];
    }
    for (long i = 0; i < 100000; i++)
    {
        o100k << f7[i];
    }
    o100.close();
    o500.close();
    o1k.close();
    o10k.close();
    o20k.close();
    o50k.close();
    o100k.close();

}
