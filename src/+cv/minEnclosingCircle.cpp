/**
 * @file minEnclosingCircle.cpp
 * @brief mex interface for cv::minEnclosingCircle
 * @ingroup imgproc
 * @author Kota Yamaguchi
 * @date 2011
 */
#include "mexopencv.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Check the number of arguments
    nargchk(nrhs==1 && nlhs<=2);

    // Argument vector
    vector<MxArray> rhs(prhs, prhs+nrhs);

    // Process
    Point2f center;
    float radius = 0;
    if (rhs[0].isNumeric()) {
        Mat points(rhs[0].toMat(rhs[0].isInt32() ? CV_32S : CV_32F));
        minEnclosingCircle(points, center, radius);
    }
    else if (rhs[0].isCell()) {
        vector<Point2f> points(rhs[0].toVector<Point2f>());
        minEnclosingCircle(points, center, radius);
    }
    else
        mexErrMsgIdAndTxt("mexopencv:error", "Invalid points argument");
    plhs[0] = MxArray(center);
    if (nlhs>1)
        plhs[1] = MxArray(radius);
}
