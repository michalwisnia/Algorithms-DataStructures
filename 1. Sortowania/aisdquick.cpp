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
tuple stack[562000];
enum class pivot_type {right, middle, random};
std::vector<int> quickSortIter(std::vector<int> &in, pivot_type pivot)
{
    tuple range{0,0};
    int p, i, j;
    int stack_iterator = 0;
    stack[0] = tuple{0,(int)in.size() - 1};
    while (stack_iterator >= 0)
    {
        range = stack[stack_iterator];
        stack_iterator--;
        while (range.r > range.l){
            i = range.l;
            j = range.r;
            switch (pivot)
            {

                case pivot_type::right:
                    p = in[j];
                    break;
                case pivot_type::middle:
                    p = in[(i+j)/2];
                    break;
                case pivot_type::random:
                    p = in[random<int>(i,j)];
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


long long  measureSortingTime(std::vector<int>data, pivot_type pivot)
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    data = quickSortIter(data, pivot);
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

#define START 2000
#define STEP 1999

#define MNOZNIK 7
void punktIII()
{
    std::fstream output;
    output.open("quicksort.txt", std::ios_base::app);
    output << "probka prawy srodkowy losowy" << std::endl;
    std::cout << "Zapis do quicksort.txt" << std::endl;
    for (unsigned int i = 0; i < 15; i++) {
        std::cout << START + STEP * i * MNOZNIK << " elementow probka nr " << i + 1 << std::endl;
        long long results[3] = {0};
        for (int attempt = 0; attempt < 5; attempt++) {
            std::vector<int> data = getData(START + STEP * i * MNOZNIK, data_type::ashape);
            results[0] += measureSortingTime(data, pivot_type::right);
            results[1] += measureSortingTime(data, pivot_type::middle);
            results[2] += measureSortingTime(data, pivot_type::random);
        }

        for (auto &a : results)
            a /= 5;
        output << START + STEP * i * MNOZNIK << " " << results[0] << " " << results[1]  << " " << results[2] << std::endl;
    }
}




int main() {
    //punktI();
    punktIII();
    return 0;
}

