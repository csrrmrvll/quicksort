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

int partition(Vector & v, int first, int last)  //  inclusive
{
    int pivot = v[first];
    int i = first + 1;
    for (int j = i; j <= last; ++j)
    {
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            ++i;
        }
    }
    swap(v[first], v[i - 1]);
    return i - 1;
}

int comparisons = 0;

void quicksort(Vector & v, int first, int last) //  inclusive
{
    if (first >= last)
    {
        return;
    }
    comparisons += last - first;
    swap(v[first], v[last]);    //  for the last!!!!
    int p = partition(v, first, last);
    quicksort(v, first, p - 1);
    quicksort(v, p + 1, last);
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
//    Vector v = { -1, 0, -2, 1 };
    Vector v = read();
    int size = v.size();
    quicksort(v, 0, size - 1);
    cout << "number of comparisons: " << comparisons << endl;
    Vector sorted(size);
    int min = *min_element(begin(v), end(v));
    iota(sorted.begin(),sorted.end(),min);
    if (v != sorted)
    {
        cout << "wrong sorting algorithm" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
