#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
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

int getPivotIndex(Vector & v, int first, int last)
{
    int size = last - first + 1;
    if (size < 3)
    {
        return v[first] < v[last] ? first : last;
    }
    int middle;
    if (size % 2 == 0)
    {
        middle = size / 2 - 1;
    }
    else
    {
        middle = size / 2;
    }
    int f = v[first],
        m = v[middle],
        l = v[last];
    map<int,int> values{ make_pair(f, first), make_pair(m, middle), make_pair(l, last) };
    int result = (++begin(values))->second;
    return result;
}

int comparisons = 0;

void quicksort(Vector & v, int first, int last) //  inclusive
{
    if (first >= last)
    {
        return;
    }
    comparisons += last - first;
//    swap(v[first], v[last]);    //  for the last!!!!
    int pivotIndex = getPivotIndex(v, first, last);
    swap(v[first], v[pivotIndex]);    //  for the median!!!!
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
    Vector v = { 5, 4, 3, 2, 1, 0 };
//    Vector v = read();
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
