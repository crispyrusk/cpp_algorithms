#include <iostream>
#include <vector>
#include <iterator>


template<typename T>
std::size_t partition(std::vector<T>& v, std::size_t startIndex, std::size_t endIndex)
{
    if ((startIndex > endIndex) || (endIndex - startIndex < 2))
        return startIndex;

    auto wallIndex = startIndex; // all indices <= wallIndex have value <= pivot and right of wallIndex > pivot
    auto pivot = v[wallIndex]; // first element is pivot - eventually swap it
    for (std::size_t i = startIndex + 1; i < endIndex; ++i)
    {
        if (v[i] <= pivot)
        {
            ++wallIndex;
            std::swap(v[wallIndex], v[i]);
        }
    }
    std::swap(v[startIndex], v[wallIndex]); // swap the pivot from the startIndex to the wallIndex
    return wallIndex;
}


template<typename T>
void quickSort(std::vector<T>& v, std::size_t startIndex, std::size_t endIndex)
{
    std::size_t partitionIndex = partition(v, startIndex, endIndex);
    
    if ((partitionIndex - startIndex) < 2)
    {
        return;
    }

    quickSort(v, startIndex, partitionIndex);
    quickSort(v, partitionIndex + 1, endIndex);

}


int main()
{
    std::vector<int> v = { -623,   25,   13, -550,  639,  320,  899, -384,  912,  136, -783,
        -354, -310, -166,  618,  661,  495,  206,  371, -574,  814, -962,
        -25,  832,  625, -485,  688,  325, -263,  380, -756,  181,  -43,
        -735, -649, -991, -571,  907,  280,  589, -168,   46,  946,  179,
        486,  142, -395,  925,  744, -320,  392, -431,  506,  713,  625,
        -519,  -50, -677, -266,  188,  755, -571, -747,  244,   30, -109,
        -39,  732,  355,  288,  417, -122, -758, -757, -794,   55,  866,
        -792,  379,  193, -260,  813,  828,  494,  943, -850,    9, -190,
        920,  129,  580,   91, -256,  300,  927,  274, -990,  787,  356, 
        748 };

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    quickSort(v, 0, v.size());

    std::cout << std::endl;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    return 0;
}