#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
using Vector = vector<int>;
using Iterator = Vector::iterator;

void output(Vector v)
{
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int comparisons = 0;

void quicksort(Iterator first, Iterator last)
{

    if(first == last) return;
    int pivot = *first; //*(last - 1);
    comparisons += last - first - 1;
    Iterator middle1 = std::partition(first, last,
                         [pivot](int em){ return em < pivot; });
//    comparisons += last - middle1 - 1;
    Iterator middle2 = std::partition(middle1, last,
                         [pivot](int em){ return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

Vector read()
{
    string line;
    ifstream is;
    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\quicksort\\bin\\Debug\\QuickSort.txt",std::ios::in);
    Vector v;
    if (is.is_open())
    {
        while (getline(is,line))
        {
            int n;
            std::istringstream is(line);
            is >> n;
            v.emplace_back(n);
        }
        is.close();
    }
    else
    {
        cout << "file is not open!!" << endl;
    }
    return v;
}

int main()
{
//    Vector v = { -1, 8, -3, 2 };
    Vector v = read();
    quicksort(begin(v), end(v));
    cout << "number of comparisons choosing first element as pivot: " << comparisons << endl;
    int size = v.size();
    Vector sorted(size);
    iota(sorted.begin(),sorted.end(),1);
    if (v != sorted)
    {
        cout << "wrong sorting algorithm" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
