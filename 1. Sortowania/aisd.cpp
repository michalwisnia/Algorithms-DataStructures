#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}

enum class data_type {random, ascending, descending, vshape, constant, ashape };

std::vector<int> selectionSort(std::vector<int> &in)
{
    for (int max, j = (int)in.size() - 1; j >= 1; j--)
    {
        max = j;
        for (int i = j - 1; i >= 0; i--)
            if (in[i] > in[max])
                max = i;
        std::swap(in[max], in[j]);
    }
    return in;
}

void merge(std::vector<int> &A, int left, int right, std::vector<int> &B)
{
    int middle = (left + right) / 2;
    if (middle - left > 0)
        merge(A, left, middle, B);
    if (right - middle > 1)
        merge(A, middle + 1, right, B);
    int i = left;
    int j = middle + 1;
    for (int k = left; k <= right; k++)
    {
        if ((i <= middle && j > right) || ((i <= middle && j <= right) && A[i] <= A[j])) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
    }
    for (int k = left; k <= right; k++)
        A[k] = B[k];
}

std::vector<int> mergeSort(std::vector<int> &in)
{
    std::vector<int> out(in.size());
    merge(in, 0, (int)in.size() - 1, out);
    return in;
}

std::vector<int> getData(unsigned int amount, data_type type)
{
    std::vector<int>a;
    for (int i = 0; i < amount; i++)
        a.push_back(random<int>(0, amount));

    switch (type)
    {
        case data_type::random:
            break;
        case data_type::ascending: {
            std::sort(a.begin(), a.end());
            break;
        }
        case data_type::descending: {
            std::sort(a.begin(), a.end(), std::greater<>());
            break;
        }
        case data_type::vshape: {
            std::sort(a.begin(), a.begin()+amount/2, std::greater<>());
            std::sort(a.begin()+amount/2, a.end());
            break;
        }
        case data_type::ashape: {
            std::sort(a.begin(), a.begin()+amount/2);
            std::sort(a.begin()+amount/2, a.end(), std::greater<>());
            break;
        }
        case data_type::constant:
        {
            a = std::vector<int>((unsigned long long)amount, 42);
            break;
        }
    }
    return a;
}

struct tuple
{
    int l;
    int r;
};


enum class pivot_type { right, middle, random};
pivot_type pivotType = pivot_type::middle;
std::vector<int> quickSortIter(std::vector<int> &in)
{
    tuple range{0,0};
    int p, i, j;
    int stack_iterator = 0;
    tuple stack[100] = {};
    stack[0] = tuple{0,(int)in.size() - 1};
    while (stack_iterator >= 0)
    {
        range = stack[stack_iterator];
        stack_iterator--;
        while (range.r > range.l){
            i = range.l;
            j = range.r;
            switch (pivotType)
            {

                case pivot_type::right:
                    p = in[j];
                    //std::cout<<"piwot to indeks "<<j<<" = "<<p;
                    break;
                case pivot_type::middle:
                    p = in[(i+j)/2];
                    //std::cout<<"piwot to "<<p;
                    break;
                case pivot_type::random:
                    p = in[random<int>(i,j)];
                    //std::cout<<"piwot to "<<p;
                    break;

            }

            while (i <= j) {
                while (in[i] < p) i++;
                while (in[j] > p) j--;
                if (i <= j)
                    std::swap(in[i++], in[j--]);

            }
            if (i < range.r)
            {
                stack_iterator++;
                stack[stack_iterator] = tuple{i, range.r};
            }
            range.r = j;
        }
    }
    return in;
}

std::vector<int> insertionSort(std::vector<int> &in)
{
    for (int j=1;j<in.size();j++)
    {
        int key=in[j];
        int i;
        for (i=j-1; i>=0&&in[i]>key;i--)
        {
            in[i+1]=in[i];
        }
        in[i+1]=key;
    }
    return in;
}

void heapify(std::vector<int> &in, int i, int heapsize)
{
    int l=i*2;
    int r=i*2+1;
    int largest;
    if (l<=heapsize && in[l]>in[i]) {largest=l;}
    else {largest=i;}
    if (r<=heapsize && in[r]>in[largest]) {largest=r;}
    if (largest!=i)
    {
        std::swap(in[i],in[largest]);
        heapify(in, largest, heapsize);
    }
}
void buildheap(std::vector<int> &in)
{
    int heapsize=(int)in.size();
    for (int i=(int)in.size()/2;i>=1;i--)
    {
        heapify(in, i, heapsize);
    }
}
std::vector<int> heapSort(std::vector<int> &in)
{
    buildheap(in);
    int heapsize=(int)in.size();
    for (int i=(int)in.size();i>=1;i--)
    {
        std::swap(in[0],in[i]);
        heapsize-=1;
        heapify(in, 0, heapsize);
    }
    return in;
}

int partition(std::vector<int> &in, int p, int r)
{
    int x;
    switch (pivotType)
            {

                case pivot_type::right:
                    x = in[p];
                    //std::cout<<"piwot to indeks "<<j<<" = "<<p;
                    break;
                case pivot_type::middle:
                    x = in[(p+r)/2];
                    //std::cout<<"piwot to "<<p;
                    break;
                case pivot_type::random:
                    x = in[random<int>(p,r)];
                    //std::cout<<"piwot to "<<p;
                    break;

            }
    int i=p-1;
    int j=r+1;
    while (true)
    {
        do
        {
            j=j-1;
        } while(in[j]>x);
        do
        {
            i=i+1;
        }while(in[i]<x);
        if (i<j)
        {
            std::swap(in[i],in[j]);
        }
        else {return j;}
    }
}
void quicksort(std::vector<int> &in, int p, int r)
{
    if (p<r)
    {
        int q=partition(in,p,r);
        quicksort(in,p,q);
        quicksort(in,q+1,r);
    }
}
std::vector<int> quicksortMain(std::vector<int> &in)
{
    quicksort(in, 0, (int)in.size()-1);
    return in;
}

long long  measureSortingTime(std::vector<int>data, std::vector<int> (*sorter)(std::vector<int>&))
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    data = sorter(data);
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

#define START 2000
#define STEP 2000

std::vector<int> (*functions[])(std::vector<int>&) = {insertionSort, selectionSort, mergeSort, heapSort};
void pomiaryI(const std::string &filename, data_type dataType)
{
    std::fstream output;
    output.open(filename, std::ios_base::app);
    output << "probka insertion selection merge heap" << std::endl;
    std::cout << "Zapis do " << filename << std::endl;
    for (unsigned int i = 0; i < 15; i++)
    {
        std::cout << START + STEP * i << " elementow probka nr " << i + 1 << std::endl;
        long long results[4] = {0};
        for (int attempt = 0; attempt < 5; attempt++) {
            std::vector<int> data = getData(START + STEP * i, dataType);
            for (int j = 0; j < 4; j++)
                results[j] = measureSortingTime(data, functions[j]);
        }

        for (auto&a : results)
            a /= 5;

        output << START + STEP * i << " " << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << std::endl;
    }
    output.close();
}

/*void punktI()
{
    pomiaryI("random.txt", data_type::random);
    pomiaryI("ascending.txt", data_type::ascending);
    pomiaryI("descending.txt", data_type::descending);
    pomiaryI("constant.txt", data_type::constant);
    pomiaryI("vshape.txt", data_type::vshape);
}*/

#define MNOZNIK 20
void punktIII()
{
    std::fstream output;
    output.open("quicksort.txt", std::ios_base::app);
    output << "probka rek iter" << std::endl;
    std::cout << "Zapis do quicksort.txt" << std::endl;
    for (unsigned int i = 0; i < 15; i++) {
        std::cout << START + STEP * i * MNOZNIK << " elementow probka nr " << i + 1 << std::endl;
        long long results[2] = {0};
        for (int attempt = 0; attempt < 5; attempt++) {
            std::vector<int> data = getData(START + STEP * i * MNOZNIK, data_type::random);
            results[0] += measureSortingTime(data, quicksortMain);
            results[1] += measureSortingTime(data, quickSortIter);
        }

        for (auto &a : results)
            a /= 5;
        output << START + STEP * i * MNOZNIK << " " << results[0] << " " << results[1] << std::endl;
    }
    /*output << "probka prawy srodkowy losowy" << std::endl;
    std::cout << "Zapis do quicksort.txt" << std::endl;
    for (unsigned int i = 0; i < 15; i++) {
        std::cout << START + STEP * i * MNOZNIK << " elementow probka nr " << i + 1 << std::endl;
        long long results[3] = {0};
        for (int attempt = 0; attempt < 5; attempt++) {
            std::vector<int> data = getData(START + STEP * i * MNOZNIK, data_type::ashape);
            pivotType = pivot_type::right;
            results[0] += measureSortingTime(data, quicksortMain);
            pivotType = pivot_type::middle;
            results[1] += measureSortingTime(data, quicksortMain);
            pivotType = pivot_type::random;
            results[2] += measureSortingTime(data, quicksortMain);
        }

        for (auto &a : results)
            a /= 5;
        output << START + STEP * i * MNOZNIK << " " << results[0] << " " << results[1]  << " " << results[2] << std::endl;
    }*/
}




int main() {
    //punktI();
    punktIII();
    /*int s=50;
    std::vector<int> test;
    test=getData(s, data_type::ashape);
    for (int i=0; i<s; i++)
    {
        std::cout<<test[i]<<" ";
    }
    std::cout<<std::endl;
    pivotType = pivot_type::right;
    quickSortIter(test);
    for (int i=0; i<s; i++)
    {
        std::cout<<test[i]<<" ";
    }*/
    return 0;
}
