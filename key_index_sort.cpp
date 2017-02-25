// keys are from a finite set - then we have a linear time algorithm to sort the keys
// this forms the basis for radix sort/buck sort etc
// the main idea 
// ##############
// keys belong to a finite set - lets say all numbers from 0 to 9. 
// then you can count the keys
//  array of keys --> countkeys arrays --> cumSumCount array --> create a aux(rtrn) array that will contain the sorted keys by using cumSumCount (will be incrememented for every access) as indexing scheme
//  again the main idea is to use the cumSumCount array as the indexing array for the output array

#include <vector>
#include <iostream>
#include <cassert>


std::vector<int> keySort(const std::vector<int>& keys)
{

    std::vector<int> counter(10, 0);

    //ensure keys are from a finite set {0,1,...9}
    for (const auto x : keys)
    {
        assert(0 <= x && x < 10);
        ++counter[x];
    }

    std::vector<int> cumSumCounter(11, 0);

    for (std::size_t i = 1; i < cumSumCounter.size(); ++i)
    {
        cumSumCounter[i] = counter[i-1] + cumSumCounter[i - 1];
    }

    // at the point cumSumCounter holds the start location for each key

    std::vector<int> rtrn(keys.size());
    for (std::size_t i = 0; i < keys.size(); ++i)
    {
        auto key = keys[i];
        rtrn[cumSumCounter[key]++] = key;
    }

    return rtrn;

}




int main()
{
    std::vector<int> keys = { 9,7,9,7,5,4,3,4,3,2,5,6,4,3,0,1,2,3,4,5,6,7,8,9 };
    
    for (auto& x : keys)
        std::cout << x << ", ";
    std::cout << std::endl;


    auto sorted = keySort(keys);

    for (auto& x : sorted)
        std::cout << x << ", ";
    std::cout << std::endl;

    return 0;
}