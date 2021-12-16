#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <time.h>



enum class data_type {random, ascending, descending, vshape, constant };

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
    std::vector<int> a;
    switch (type)
    {
        case data_type::random: {
            srand((unsigned int)time(nullptr));
            for (int i = 0; i < amount; i++)
                a.push_back(rand()%amount);

            break;
        }
        case data_type::ascending: {
            for (int i = 0; i < amount; i++)
                a.push_back(i);

            break;
        }
        case data_type::descending: {

            for (int i = 0; i < amount; i++)
                a.push_back(amount - i);

            break;
        }
        case data_type::vshape: {
            for (int i = 0; i < amount / 2; i++)
                a.push_back(amount / 2 - i);
            for (int i = amount / 2; i < amount; i++)
                a.push_back(i - amount / 2);

            break;
        }
        case data_type::constant:
        {
            a = std::vector<int>((unsigned long long)amount);
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

std::vector<int> quickSortIter(std::vector<int> &in)
{
    tuple range{0,0};
    int p, i, j;
    std::vector<tuple> stack = {tuple{0,(int)in.size() - 1}};
    while (!stack.empty())
    {
        range = stack.back();
        stack.pop_back();
        while (range.r > range.l){
            i = range.l;
            j = range.r;
            p = in[(i+j)/2];
            while (i <= j) {
                while (in[i] < p) i++;
                while (in[j] > p) j--;
                if (i <= j)
                    std::swap(in[i++], in[j--]);

            }
            if (i < range.r)
                stack.push_back(tuple{i, range.r});
            range.r = j;
        }
    }
    return in;
}

void insertionsort(std::vector<int> &in)
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
    int heapsize=in.size();
    for (int i=in.size()/2;i>=1;i--)
    {
        heapify(in, i, heapsize);
    }
}
void heapsort(std::vector<int> &in)
{
    buildheap(in);
    int heapsize=in.size();
    for (int i=in.size();i>=1;i--)
    {
        std::swap(in[0],in[i]);
        heapsize-=1;
        heapify(in, 0, heapsize);
    }
}

int partition(std::vector<int> &in, int p, int r)
{
    int x=in[(p+r)/2];
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
void quicksortMain(std::vector<int> &in)
{
    quicksort(in, 0, in.size());
}

int main()
{
    int s=10000;
    std::vector<int> test;
    test=getData(s, data_type::random);
    /*for (int i=0; i<s; i++)
    {
        std::cout<<test[i]<<" ";
    }*/
    //clock_t t;
	//t = clock();

    auto start = std::chrono::steady_clock::now();

    heapsort(test);
    auto end = std::chrono::steady_clock::now();

   // t = clock() - t;

    std::cout<<std::endl;
    /*for (int i=0; i<s; i++)
    {
        std::cout<<test[i]<<" ";
    }*/
        std::cout << "Elapsed time in nanoseconds : "<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<< " ns" << std::endl;

}
