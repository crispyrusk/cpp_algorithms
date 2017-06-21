/*

Given a grayscale image represented by an NxN matrix, write a method to rotate the image by a given degree theta.

You can use nearest neighbor, linear interpolation etc. For more details about algorithms, please refer to
https://www.mathworks.com/help/images/ref/imrotate.html

*/


#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


using namespace std;

#define PI 3.141592653589793

// rotate with nearest neighbor interpolation
vector< vector<float> > rotate(vector< vector<int> > inputMat, const float thetaDeg)
{
    const auto thetaRad = thetaDeg * PI / 180.0;
    auto M = inputMat.size();
    // dont handle empty matrices yet
    assert(M > 0);
    auto N = inputMat[0].size();
    assert(N > 0);
    double xResolution = 2.0 / (N - 1);
    double yResolution = 2.0 / (M - 1);
    vector<double> xSpan(N);
    vector<double> ySpan(M);
    for (size_t xx = 0; xx < N; ++xx)
        xSpan[xx] = -1.0 + xx * xResolution;
    for (size_t yy = 0; yy < M; ++yy)
        ySpan[yy] = -1.0 + yy * yResolution;

    vector< vector<float> > outputMat(M);
    for (auto& row : outputMat)
        row.resize(N);

    for (auto xTarget : xSpan)
    {
        for (auto yTarget : ySpan)
        {
            auto xSource = cos(thetaRad) * xTarget + sin(thetaRad) * yTarget;
            auto ySource = -sin(thetaRad) * xTarget + cos(thetaRad) * yTarget;

            auto index0 = int((1 + yTarget) / yResolution);
            auto index1 = int((1 + xTarget) / xResolution);

            if (xSource < -1.0 || xSource > 1.0 || ySource < -1.0 || ySource > 1.0)
                outputMat[M - 1 - index0][index1] = 0.0f;
            else
            {
                int sourceIndex0 = static_cast<int>(round((1 + ySource) / yResolution));
                int sourceIndex1 = static_cast<int>(round((1 + xSource) / xResolution));
                outputMat[M - 1 - index0][index1] = inputMat[M - 1 - sourceIndex0][sourceIndex1];
            }
        }
    }
    return outputMat;

}

template<typename T>
void printMat(const vector< vector<T> >& mat)
{
    for (auto& row : mat)
    {
        for (auto& element : row)
            cout << element << ", ";
        cout << "\n";
    }
}

int main()
{
    /*
    vector<vector<int> > img = { { 1, 1, 5, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 } };

    */
    vector<vector<int> > img = { { 1, 1, 5, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 5, 1, 1 },
    { 3, 1, 1, 3, 1 },
    { 1, 4, 5, 10, 1 },
    { 1, 1, 1, 1, 1 } };


    const float theta = 10; // degress

    vector<vector<float> > img_rot = rotate(img, theta);
    cout << "input img \n";
    printMat(img);
    cout << "rot img \n";
    printMat(img_rot);

    return 0;

}


/*
Below the python code used for testing; primarily for imshow
*/

/*
import numpy as np
import matplotlib.pyplot as plt



if __name__ == "__main__":
input_mat = np.array([[1, 1, 5, 1, 1],
[1, 1, 1, 1, 1],
[1, 1, 5, 1, 1],
[4, 1, 1, 4, 1],
[1, 1, 1, 1, 1],
[4, 5, 1, 3, 1]])

theta = 90
theta_rad = theta * np.pi / 180.0

M, N = input_mat.shape
x_resolution = 2.0/(N-1)
y_resolution = 2.0/(M-1)
x_span = [-1 + xx*x_resolution for xx in range(N)]
y_span = [-1 + yy*y_resolution for yy  in range(M)]
print(x_span)
print(y_span)

output_mat = np.zeros_like(input_mat, dtype=np.float32)
m = 0
n = 0
for x_target in x_span:
for y_target in y_span:
x_source = np.cos(theta_rad) * x_target + np.sin(theta_rad) * y_target
y_source = -np.sin(theta_rad) * x_target + np.cos(theta_rad) * y_target
#print(x_target, y_target)
#print(x_source, y_source)
index = int((1 + y_target) / y_resolution), int((1 + x_target) / x_resolution)
print(index)
if (x_source < -1.0 or x_source > 1.0 or y_source < -1.0 or y_source > 1.0):
output_mat[M - 1 - index[0], index[1]] = 0.0
else:
m_frac = (1 + y_source) / y_resolution
n_frac = (1 + x_source) / x_resolution
#print(y_source, x_source)
#print((m_frac, n_frac))
source_index = (np.round(m_frac), np.round(n_frac))
output_mat[M - 1 - index[0], index[1]] = input_mat[M - 1 - source_index[0], source_index[1]]
# code for linear interpolation
# no time to convert to c++
'''
m_ceil = np.ceil(m_frac)
m_floor = np.floor(m_frac)
m_lambda = (m_frac - m_floor)/y_resolution
n_frac = x_source * x_resolution
n_ceil = np.ceil(n_frac)
n_floor = np.floor(n_frac)
n_lambda = (n_frac - n_floor)/x_resolution
new_value =  m_lambda * (1-n_lambda) * input_mat[M - m_floor, n_ceil] \
+ (1-m_lambda) * (1-n_lambda) * input_mat[M - m_ceil, n_ceil] \
+ (1-m_lambda) * n_lambda * input_mat[M - m_ceil, n_floor] \
+ m_lambda * n_lambda * input_mat[M - m_floor, n_floor]
output_mat[M-int(m_frac), int(n_frac)]
'''










plt.figure()
plt.imshow(input_mat, interpolation="none")
plt.figure()
plt.imshow(output_mat, interpolation="none")
print(input_mat)
print(output_mat)
*/
