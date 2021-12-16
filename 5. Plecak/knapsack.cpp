#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

struct item
{
    int value;
    int weight;
    double ratio;
};


std::mt19937 gen{std::random_device{}()};
template<typename T>
inline T random(T min, T max) { return std::uniform_int_distribution<T>{min, max}(gen); }

std::pair<std::vector<int>, std::vector<int>> generate(int size, int limit)
{
    std::vector<int> weight(size);
    std::vector<int> worth(size);

    for (--size; size >= 0; --size)
    {
        weight[size] = random(1,limit);
        worth[size] = random(1,limit);
    }

    return std::make_pair(weight, worth);
}

int knapsack_dynamic(const std::vector<int>& weight, const std::vector<int>& worth, int max_weight)
{
    int s = weight.size() + 1;
    int w = max_weight + 1;
    auto tab = new int*[s];
    for (int i = 0; i < s; ++i) {
        tab[i] = new int[w]{0};
        if (i > 0)
            for (int j = 0; j < w; ++j)
            {
                if (weight[i - 1] <= j)
                    tab[i][j] = std::max({tab[i-1][j], tab[i - 1][j - weight[i - 1]] + worth[i - 1]});
                else
                    tab[i][j] = tab[i - 1][j];
            }
    }

    /*
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < w; ++j)
            std::cout << tab[i][j] << " ";
        std::cout << std::endl;
    }
    */

    std::vector<int> out;
    int sum = 0;
    out.reserve(s - 1);
    int max, maxi, maxj;
    do {
        max = maxi = maxj = 0;
        for (int i = 0; i < s; ++i)
            for (int j = 0; j < w; ++j) {
                if (tab[i][j] > max) {
                    max = tab[i][j];
                    maxi = i;
                    maxj = j;
                }
            }

        if (max > 0 )
        {
            out.push_back(maxi - 1);
            sum += worth[maxi - 1];
            s = maxi;
            w = maxj - weight[maxi - 1] + 1;
        }

    } while (max != 0);

    //return out;
    return sum;
}

bool cmpratio(struct item a, struct item b)
{
    return a.ratio > b.ratio;
}

int knapsack_greedy(const std::vector<int>& weight, const std::vector<int>& worth, int max_weight)
{

    std::vector<item> items (worth.size());

    for (int i = 0; i < weight.size() ; ++i)
    {
        items[i].value=worth[i];
        items[i].weight=weight[i];
        items[i].ratio = ( double(worth[i]) / double(weight[i]) );
    }
    sort(items.begin(), items.end(), cmpratio);

    std::vector<item> out;
    int kvalue = 0;
    int kweight = 0;
    std::cout<<"wchodz¹ elementy: ";
    int j=1;
    for (auto &i : items)
    {

        if (kweight + i.weight <= max_weight)
        {
            out.push_back(i);
            kweight+=i.weight;
            kvalue+=i.value;
            std::cout<<" o wartoœci "<<i.value<<" i o wadze "<<i.weight<<", ";


        }

    }

    std::cout<<std::endl<<"suma : "<<kvalue;
    return kvalue;
}

template <class T>
void print(std::vector<T> in)
{
    for (const auto &item : in) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void test1()
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size, max_weight = 13, prob = 10;
    long long result1, result2;
    std::fstream file;

    file.open("test1.txt", std::ios::out);
    file << "ladunek dynamiczny zachlanny " << max_weight << "\r\n";
    std::cout << "test1 \r\nladunek dynamiczny zachlanny " << max_weight  << "\r\n";
    for (int i = 0; i < 15; ++i)
    {
        result1 = result2 = 0;
        size = 100 * pow(2, i);
        for (int j = 0; j < prob; ++j)
        {
            auto proba = generate(size, 20);
            p1 = clock::now();
            knapsack_dynamic(proba.first, proba.second, max_weight);
            p2 = clock::now();
            result1 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / prob;

            p1 = clock::now();
            knapsack_greedy(proba.first, proba.second, max_weight);
            p2 = clock::now();
            result2 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / prob;
        }
        std::cout << size << " " << result1 << " " << result2 << "\r\n";
        file << size << " " << result1 << " " << result2 << "\r\n";
    }
}

void test2()
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size = 10000, max_weight, prob = 10;
    long long result1, result2;
    std::fstream file;

    file.open("test2.txt", std::ios::out);
    file << "pojemnosc dynamiczny zachlanny " << size << "\r\n";
    std::cout << "test2 \r\npojemnosc dynamiczny zachlanny " << size  << "\r\n";
    for (int i = 0; i < 15; ++i)
    {
        result1 = result2 = 0;
        max_weight = 2 + 2 * i;
        for (int j = 0; j < prob; ++j)
        {
            auto proba = generate(size, 30);
            p1 = clock::now();
            knapsack_dynamic(proba.first, proba.second, max_weight);
            p2 = clock::now();
            result1 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / prob;

            p1 = clock::now();
            knapsack_greedy(proba.first, proba.second, max_weight);
            p2 = clock::now();
            result2 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / prob;
        }
        std::cout << max_weight << " " << result1 << " " << result2 << "\r\n";
        file << max_weight << " " << result1 << " " << result2 << "\r\n";
    }
}

void test3()
{
    int size, max_weight, prob = 100;
    double result1, result2;
    std::fstream file;
    int csize = 18;
    int cweight = 200;

    file.open("test3.txt", std::ios::out);
    file << "ladunek dokladnosc pojemnosc dokladnosc" << "\r\n";
    std::cout << "test3 \r\nladunek dokladnosc pojemnosc dokladnosc"  << "\r\n";
    for (int i = 0; i < 15; ++i)
    {
        result1 = result2 = 0;
        size = 5  + 25 * i;
        max_weight = 10 + 25 * i;
        for (int j = 0; j < prob; ++j)
        {
            auto proba1 = generate(size, 30);
            auto r1 = knapsack_dynamic(proba1.first, proba1.second, cweight);
            auto r2 = knapsack_greedy(proba1.first, proba1.second, cweight);
            result1 += double(r1 - r2) / r1;
            //std::cout << r1 << " " << r2 << std::endl;
            auto proba2 = generate(csize, 30);
             r1 = knapsack_dynamic(proba2.first, proba2.second, max_weight);
             r2 = knapsack_greedy(proba2.first, proba2.second, max_weight);
            result2 += double(r1 - r2) / r1;
        }
        std::cout << size << " " << result1 / prob << " " << max_weight << " " << result2 / prob << "\r\n";
        file << size << " " << result1 / prob << " " << max_weight  << " " << result2 / prob<< "\r\n";
    }
}


int main() {
    //test1();
    //test2();
    //test3();
    std::vector<int> weight = {3, 2, 4, 3, 1};
    std::vector<int> worth = {5, 3, 4, 4, 2};
    knapsack_greedy(weight, worth, 8);
    return 0;
}

