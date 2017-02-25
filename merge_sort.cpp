#include <iostream>
#include <vector>
#include <iterator>

template<typename T>
void merge(std::vector<T>& v, std::size_t startIndex, std::size_t endIndex, std::size_t midIndex)
{
    std::vector<T> aux = v;
    auto leftIndex = startIndex;
    auto rightIndex = midIndex;
    for (std::size_t i = startIndex; i < endIndex; ++i)
    {
        if (leftIndex >= midIndex) // left has reach mid, so watever is left in v'right will be what is in aux's right
            break;

        if (rightIndex >= endIndex) // right has reached end, so just fill up with left
            v[i] = aux[leftIndex++];
        else if (aux[leftIndex] < aux[rightIndex])
            v[i] = aux[leftIndex++];
        else
            v[i] = aux[rightIndex++];

    }

}

template<typename T>
void mergeSort(std::vector<T>& v, std::size_t startIndex, std::size_t endIndex)
{
    if (endIndex - startIndex < 2)
        return;

    auto midIndex = (startIndex + endIndex) / 2;
    mergeSort(v, startIndex, midIndex);
    mergeSort(v, midIndex, endIndex);
    merge(v, startIndex, endIndex, midIndex);
}


int main()
{
    std::vector<int> v = { -78, -90, -27, -87,  58,  12, -14, -78, -68,   1 };
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
    mergeSort(v, 0, v.size());
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    return 0;
    
}