#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>

std::mt19937 gen{std::random_device{}()};
template<typename T>
inline T random(T min, T max) { return std::uniform_int_distribution<T>{min, max}(gen); }

void print_graph(bool **in, int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << in[i][j] << " ";
        std::cout << std::endl;
    }
}

void print_vertices_level(bool**in, int size)
{
    int foo;
    for (int i = 0; i < size; ++i) {
        foo = 0;
        for (int j = 0; j < size; ++j)
            if (in[i][j])
                ++foo;
        std::cout << i << "|" << foo << std::endl;
    }
}

//Cyclic Euler Hamilton Graph
bool** generate_CEHG(int size, float density)
{
    //Alokacja
    auto tab = new bool*[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = new bool[size]{false};
    }

    //Graf minimalny
    tab[0][size - 1] = tab[size - 1][0] = true;

    for (int i = 1; i < size; ++i) {
        tab[i][i-1] = tab[i-1][i] = true;
    }

    //Losowanie krawędzi
    int edges = size;
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

        tab[v1][v2] = tab[v2][v1] = true;
        ++edges;
    }

    //Krótka funkcja zwracająca stopień wierzchołka
    auto v_level = [&tab, &size](int x) -> int { int foo = 0; for (int i = 0; i < size; ++i) if (tab[x][i]) ++foo; return foo;};

    //Usuwanie niaparzystości stopni
    //Znajdź parę wierchołków o nieparzystym stopniu, jeśli mają krawędź to ją usuń, jeśli nie mają to stwórz
    for (int i = 0; i < size; ++i) {
        if (v_level(i) % 2 == 1) {
            for (int j = 0; j < size; ++j) {
                if (i != j && v_level(j) % 2 == 1) {
                    tab[i][j] = tab[j][i] = !tab[i][j];
                    break;
                }
            }
        }
    }

    //Mieszanie wierzchołków
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

void _euler(bool** in, int vertex, const int& size, std::list<int>& list)
{
    for (int i = 0; i < size; ++i)
        if(in[vertex][i])
        {
            in[vertex][i] = in[i][vertex] = false;
            _euler(in, i, size, list);
        }
    list.push_back(vertex);
}

//Modyfikuje macierz
std::list<int> euler(bool** in,const int& size)
{
    std::list<int> list;
    _euler(in, 0, size, list);
    return list;
}


void printcycle(std::vector<int> cycle)
{
    std::cout<<"Cykl: ";
    for (auto i : cycle) {std::cout<<i<<" ";}
    std::cout<<std::endl;
}

bool notincluded(int v, std::vector<int>& cycle) //czy wierzcholek jest juz zawarty w ciagu
{
    for (auto i : cycle)
    {
        if (i==v) {return false; }
    }

    return true;
}

//cykl Hamiltona (pierwszy)
bool _hamilton(bool** in, const int& size, std::vector<int>& cycle, int v)
{
    if (cycle.size()==size) // czy jest już ciąg wykorzystujący wszystkie wierzchołki
    {
        if ( in[cycle[size-1]][cycle[0]] == true ) //sprawdzenie cyklu
        {
            cycle.push_back(cycle[0]); //dodanie jeszcze raz pierwszego elementu
            return true;
        }
        else {}

    }
    else //jeśli nie to chcemy dodać następny
    {
        for (int i=1; i<size; ++i)
        {

            if ( (in[v][i]==1) && notincluded(i, cycle)==true )
            {
                //std::cout<<"Dobre "<<v<<" "<<i<<std::endl;
                cycle.push_back(i);
                if (_hamilton(in, size, cycle, i)==true) {return true;}  //wchodzimy w kolejny wierzchołek
            }
            else {}

        }
    }

    cycle.pop_back(); //zawracanie
    return false;

}

std::vector<int> hamilton(bool** in, const int& size)
{
    std::vector<int> cycle{0};
    _hamilton(in, size, cycle, 0);
    return cycle;
}


//wszystkie cykle hamiltona
void _hamiltons(bool** in, const int& size, std::vector<int>& cycle, int v)
{
    if (cycle.size()==size)
    {
        if ( in[cycle[size-1]][cycle[0]] == true )
        {
            cycle.push_back(cycle[0]);
            //printcycle(cycle); //wypisujemy jeden z cykli i idziemy dalej
            cycle.pop_back();
        }
        else {}

    }
    else
    {
        for (int i=1; i<size; ++i)
        {

        if ( (in[v][i]==1) && notincluded(i, cycle)==true )
        {
            //std::cout<<"Dobre "<<v<<" "<<i<<std::endl;
            cycle.push_back(i);
            _hamiltons(in, size, cycle, i);
        }
        else {}

        }

    }
    //printcycle(cycle);
    //std::cout<<"usuwanie"<<cycle[cycle.size()-1]<<std::endl;
    cycle.pop_back();
    //printcycle(cycle);
}


void hamiltons(bool** in, const int& size)
{
    std::vector<int> cycle{0};
    _hamiltons(in, size, cycle, 0);

}

void test1(const float& density)
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size;
    long long result1, result2;
    std::fstream file;

    file.open("euler_hamilton"+std::to_string(density)+".txt", std::ios::out);
    file << "proba euler hamilton " << density << "\r\n";
    std::cout << "test1 \r\n proba euler hamilton " << density << "\r\n";
    for (int i = 0; i < 15; ++i)
    {
        result1 = result2 = 0;
        size = 10 + 10 * i;
        for (int j = 0; j < 5; ++j)
        {
            auto matrix = generate_CEHG(size, density);
            p1 = clock::now();
            hamilton(matrix, size);
            p2 = clock::now();
            result2 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;

            p1 = clock::now();
            euler(matrix, size);
            p2 = clock::now();
            result1 += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;
        }
        std::cout << size << " " << result1 << " " << result2 << "\r\n";
        file << size << " " << result1 << " " << result2 << "\r\n";
    }
}

void test1()
{
    test1(0.3);
    test1(0.7);
}

void test2()
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point p1, p2;
    int size;
    long long result;
    std::fstream file;

    file.open("hamiltons.txt", std::ios::out);
    file << "proba hamiltons" << "\r\n";
    std::cout << "test2 \r\n proba hamiltons \r\n ";
    for (int i = 0; i < 15; ++i)
    {
        result = 0;
        size = 5 + i;
        for (int j = 0; j < 5; ++j)
        {
            auto matrix = generate_CEHG(size, 0.5);
            p1 = clock::now();
            hamiltons(matrix, size);
            p2 = clock::now();
            result += std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count() / 5;
        }
        std::cout << size << " " << result << "\r\n";
        file << size << " " << result << "\r\n";
    }
}

int main()
{
    //TEST
    /*
    auto graph = generate_CEHG(size, 0.3);
    print_graph(graph, size);
    print_vertices_level(graph, size);
    auto a = euler(graph, size);
    for (const auto &item : a) {
        std::cout << item << " " ;
    }
    */

    /*
    auto hamgraph = generate_CEHG(size, 0.7);
    print_graph(hamgraph, size);

    std::vector<int> ham = hamilton(hamgraph, size); //pierwszy cykl grafu
    printcycle(ham);

    hamiltons(hamgraph,size); //wyszukanie (i wypisanie) wszystkich cykli hamiltona w grafie
    */
   //test1();
   test2();
    return 0;
}
