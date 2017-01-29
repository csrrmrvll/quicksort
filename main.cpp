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

class QuickSort
{
public:
    int sortAndGetComparisons(Vector & v)
    {
        int comparisons = 0;
        this->quicksort(v, 0, v.size() - 1, comparisons);
        return comparisons;
    }

private:
    void quicksort(Vector & v, int first, int last, int & comparisons) //  inclusive
    {
        if (first >= last)
        {
            return;
        }
        const int size = last - first + 1;
        comparisons += size - 1;
        int pivotIndex = first;
    //        int pivotIndex = last;
    //        int pivotIndex = getPivotIndex(v, first, last);
        swap(v[first], v[pivotIndex]);    //  for the median!!!!
        pivotIndex = partition(v, first, last);
        quicksort(v, first, pivotIndex - 1, comparisons);
        quicksort(v, pivotIndex + 1, last, comparisons);
    }

    int partition(Vector & v, int first, int last)  //  inclusive
    {
        const int pivot = v[first];
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
        const int   middle = (first + last) / 2,
                    f = v[first],
                    m = v[middle],
                    l = v[last];
        const map<int,int> values{ make_pair(f, first), make_pair(m, middle), make_pair(l, last) };
        const int result = (++begin(values))->second;
        return result;
    }
};

Vector read()
{
    string line;
    ifstream is;
    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\quicksort\\bin\\Debug\\QuickSort.txt",std::ios::in);
//    is.open("C:\\Users\\csr\\Documents\\Algorithm design and analyisis I\\programming assignments\\quicksort\\bin\\Debug\\1000.txt",std::ios::in);
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
//    Vector v = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
//    Vector v = { 3, 9, 8, 4, 6, 10, 2, 5, 7, 1 };
    Vector v = read();
    QuickSort qs;
    const int comparisons = qs.sortAndGetComparisons(v);
    cout << "number of comparisons: " << comparisons << endl;
    Vector sorted(v.size());
    int min = *min_element(begin(v), end(v));
    iota(sorted.begin(),sorted.end(),min);
    if (v != sorted)
    {
        cout << "wrong sorting algorithm" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
