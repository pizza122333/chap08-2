#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 원본 사진(src)을 불러와요
    Mat src = imread("lenna.bmp");
    if (src.empty()) {
        cerr << "사진을 찾을 수 없어요!" << endl;
        return -1;
    }

    // 2. 원래 사진의 꼭짓점 3개를 지정해요
    Point2f srcPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols, 0);
    srcPts[2] = Point2f(0, src.rows);

    // 3. 2배로 늘어날 사진의 꼭짓점 3개를 가로/세로에 2를 곱해서 지정해요
    Point2f dstPts[3];
    dstPts[0] = Point2f(0, 0);
    dstPts[1] = Point2f(src.cols * 2, 0);
    dstPts[2] = Point2f(0, src.rows * 2);

    // 4. 두 점들을 비교해서 "2배 확대 지도(M)"를 만들어내요
    Mat M = getAffineTransform(srcPts, dstPts);

    // 5. 검은 창에 이 지도의 숫자들을 출력해봐요
    cout << M << endl;

    // 6. 지도를 가지고 실제로 사진을 2배로 늘려 결과 사진(dst)을 만들어요
    // 이때 결과 사진을 담을 공간의 크기도 가로, 세로 2배(src.size() * 2)로 넉넉하게 열어주어야 해요!
    Mat dst;
    warpAffine(src, dst, M, src.size() * 2);

    // 7. 원본 사진과 2배 커진 결과 사진을 화면에 보여줍니다
    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    return 0;
}