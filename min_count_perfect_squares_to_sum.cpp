///
/// Leetcode excercise: 
/// Given a positive integer n, 
/// find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
/// For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
///
/// Solution: using dynamic programming (dp) recursion to solve it. Using the dp cache to solve intermediate solutions


class Solution {
public:
    int numSquares(int n) {
        dpCache_.clear();
        dpCache_.resize(n+1, -1);
        dpCache_[0] = 0;
        dpCache_[1] = 1;
        dpCache_[2] = 2;
        dpCache_[3] = 2;
        return computeSolution(n);
    }
    
    int computeSolution(int n) 
    {
        //std::cout << "n: " << n << "\n";
        if (dpCache_[n] > -1)
        {
            //std::cout << "using cache for n: " << n << "\n";
            return dpCache_[n];
        }
        std::vector<int> intermediateSolutions;
        for (int option = 1; option < n; ++option)
        {
            int squareOption = pow(option, 2);
            int sumRemaining = n - squareOption;
            if (sumRemaining < 0) { break; }
            intermediateSolutions.push_back(1 + computeSolution(sumRemaining));
        }
        
        /*
        std::cout << "Intermediate step n:" << n << ":";
        for (auto itWalker = intermediateSolutions.begin(); itWalker != intermediateSolutions.end(); ++itWalker)
        {
            std::cout << *itWalker << ", ";
        }
        std::cout << "\n";
        */
        
        auto it = std::min_element(intermediateSolutions.begin(), intermediateSolutions.end());
        dpCache_[n] = *it;
        return dpCache_[n];
    }
    
private:
    std::vector<int> dpCache_;

};

