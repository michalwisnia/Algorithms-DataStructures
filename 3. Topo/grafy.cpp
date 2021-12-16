#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

std::mt19937 gen{std::random_device{}()};

int MST(int** in, int size)
{
    bool* included = new bool[size]{false};
    int mst=0;
    included[0]=true;
    int included_vertexes=1;
    while(included_vertexes<size)
    {
        int min=1000;
        int vertex=-1;
        for (int i=0; i<size; ++i)
        {
            if (included[i])
            {
                for (int j=0; j<size; ++j)
                {
                    if (in[i][j]<min && in[i][j]!=0  && included[j]==false)
                    {
                        min=in[i][j];
                        vertex=j;
                    }

                }
            }

        }
        included[vertex]=true;
        mst+=min;
        included_vertexes++;
    }
    //std::cout<<" Iteracje matrix = "<<ITERACJA<<" dla "<<size;
    return mst;
}

int MST(std::vector<std::pair<int,int>>* in, int size)
{
    bool* included = new bool[size]{false};
    int mst=0;
    included[0]=true;
    int included_vertexes=1;
    while(included_vertexes<size)
    {
        int min=1000;
        int vertex=-1;
        for (int i=0; i<size; ++i)
        {
            if (included[i])
            {
                for (const auto& a : in[i])
                {
                    if (a.second < min && !included[a.first])
                    {
                        min = a.second;
                        vertex = a.first;

                    }

                }
            }
        }
        included[vertex]=true;
        mst+=min;
        included_vertexes++;
    }
    //std::cout<<" Iteracje Lista = "<<ITERACJA<<" dla "<<size<<std::endl;
    return mst;
}

void printGraph(bool**in, int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << in[i][j] << " ";
        std::cout << std::endl;
    }
}

void printGraph(int**in, int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << in[i][j] << " ";
        std::cout << std::endl;
    }
}

void printGraph(std::vector<int>* in, int size)
{
    for (int i = 0; i < size; ++i) {
        for (auto a: in[i])
            std::cout << a << " ";
        std::cout << std::endl;
    }
}

void printGraph(std::vector<std::pair<int, int>>* in, int size)
{
    for (int i = 0; i < size; ++i) {
        for (auto a: in[i])
            std::cout << a.first << "|" << a.second << " ";
        std::cout << std::endl;
    }
}

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}

bool** generateStandardGraph(int size, float density = 0.6)
{
    auto tab = new bool*[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = new bool[size]{false};
    }


    for (int i = 1; i < size; ++i) {
        tab[i][i-1] = true;
        tab[i-1][i] = true;
    }

    int edges = size - 1;
    const int target = size * (size - 1) / 2 * density;

    int v1, v2;
    while (edges < target)
    {
        v1 = random(0, size-1);
        v2 = random(0, size-1);

        if (v1 == v2)
            continue;

        if (tab[v1][v2])
            continue;

        tab[v1][v2] = true;
        tab[v2][v1] = true;
        ++edges;
    }

    return tab;
}

int** generateWageGraph(int size, float density = 0.6)
{
    auto tab = generateStandardGraph(size, density);

    auto out = new int*[size];
    for (int i = 0; i < size; ++i) {
        out[i] = new int[size]{0};
    }

    for (int i = 0; i < size; ++i)
        for (int j = 0; j <= i; ++j)
            if (tab[i][j])
                out[i][j] = out[j][i] = random(0, 1000);
    return out;
}

bool** generateDirectedGraph(int size, float density = 0.6)
{
    auto tab = generateStandardGraph(size, density);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j <= i; ++j)
            tab[i][j] = false;

    int v1, v2;
    for (int i = 0; i < size; ++i)
    {
        v1 = random(0, size - 1);
        v2 = random(0, size - 1);

        if (v1 == v2)
            continue;

        std::swap(tab[v1], tab[v2]);

        for (int j = 0; j < size; ++j){
            std::swap(tab[j][v1], tab[j][v2]);
        }
    }
    return tab;
}


std::vector<int>* convert(bool** in, int size)
{
    auto* tab = new std::vector<int>[size];
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (in[i][j])
                tab[i].push_back(j);
    return tab;
}

std::vector<std::pair<int, int>>* convert(int** in, int size)
{
    auto* tab = new std::vector<std::pair<int, int>>[size];
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (in[i][j])
                tab[i].emplace_back(j,in[i][j]);
    return tab;
}

void _topologicalSort(std::vector<int>::iterator& iter, std::vector<int>* tab, bool* visited, int vertex)
{
    if (visited[vertex])
        return;

    visited[vertex] = true;
    *(iter++) = vertex;
    for (auto& a : tab[vertex])
        if (!visited[a])
            _topologicalSort(iter, tab, visited, a);
}

std::vector<int> topologicalSort(std::vector<int>* tab, int size)
{
    auto visited = new bool[size]{false};
    std::vector<int> out(size);
    int i = 0;
    auto iter = out.begin();
    while (iter != out.end())
        _topologicalSort(iter, tab, visited, i++);
    return out;

}

//TSort_MATRIX
void _topologicalSort(std::vector<int>::iterator& iter, bool** in, bool visited[], int vertex, int size)
{
    if (visited[vertex])
        return;

    visited[vertex]=true;
    *(iter++) = vertex;
    for (int i=0; i < size; i++)
    {
            if (visited[i]==false && in[vertex][i]==true)
            {
                _topologicalSort(iter, in, visited, i, size);
            }
    }
}

std::vector<int> topologicalSort(bool** in, int size)
{
    auto visited = new bool[size]{false};
    std::vector<int> out(size);
    int vertex=0;
    auto iter = out.begin();
    while (iter != out.end())
    {
            _topologicalSort(iter, in, visited, vertex++, size);

    }
    return out;

}

void test1()
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size;
    long long result1, result2;

    std::fstream file;
    file.open("top_sort.txt", std::ios::out);
    file << "proba macierz lista\r\n";
    std::cout << "test nr 1 \r\n proba macierz lista \r\n";
    for (int i = 0; i < 16; ++i)
    {
        result1 = result2 = 0;
        size = 500 + 100 * i;
        for (int j = 0; j < 5; ++j) {
            auto macierz = generateDirectedGraph(size);
            auto lista = convert(macierz, size);

            p1 = clock::now();
            topologicalSort(macierz,size);
            p2 = clock::now();
            result1 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;

            p1 = clock::now();
            topologicalSort(lista, size);
            p2 = clock::now();
            result2 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;
        }
        std::cout << size << " " << result1 << " " << result2 << "\r\n";
        file << size << " " << result1 << " " << result2 << "\r\n";
    }
}


void test2(float density)
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size;
    long long result1, result2;

    std::fstream file;
    file.open("mst"+ std::to_string(density) + ".txt", std::ios::out);
    file << "proba macierz lista " << density << "\r\n";
    std::cout << "test nr 2 \r\n proba macierz lista " << density << "\r\n";
    for (int i = 0; i < 15; ++i)
    {
        result1 = result2 = 0;
        size = 150 + 30 * i;
        for (int j = 0; j < 5; ++j) {
            auto macierz = generateWageGraph(size, density);
            auto lista = convert(macierz, size);

            p1 = clock::now();
            MST(macierz, size);
            p2 = clock::now();
            result1 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;

            p1 = clock::now();
            MST(lista, size);
            p2 = clock::now();
            result2 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;
        }
        std::cout << size << " " << result1 << " " << result2 << "\r\n";
        file << size << " " << result1 << " " << result2 << "\r\n";
    }
}


int main() {

    auto macierz =  generateDirectedGraph(10);
    auto lista=convert(macierz,10);
    printGraph(macierz,10);




    //test1();
    //test2(0.25);
    //test2(0.7);
    //test2(0.8);
    //test2(0.9);
    return 0;
}
