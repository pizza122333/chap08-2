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

    // 계산하기 편하게 가로(W)와 세로(H) 크기를 변수에 담아두기
    float W = src.cols;
    float H = src.rows;

    // 2. 원래 사진의 꼭짓점 3개
    Point2f srcPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(W, 0);
    srcPts[2] = Point2f(0, H);

    // 3. 1/2로 줄어들고 정중앙으로 이동할 꼭짓점 3개 계산값 넣기
    Point2f dstPts[3];
    dstPts[0] = Point2f(W / 4.0f, H / 4.0f);
    dstPts[1] = Point2f(3.0f * W / 4.0f, H / 4.0f);
    dstPts[2] = Point2f(W / 4.0f, 3.0f * H / 4.0f);

    // 4. 두 점들을 비교해서 "축소 + 이동 통합 지도(M)"를 만들어요
    Mat M = getAffineTransform(srcPts, dstPts);

    // 5. 지도를 가지고 실제로 사진을 변환해요
    // 결과 창 크기를 원본과 똑같이(src.size()) 지정하면 남은 공간은 자동으로 검은색으로 채워져요!
    Mat dst;
    warpAffine(src, dst, M, src.size());

    // 6. 원본과 결과를 화면에 보여줍니다
    imshow("src", src);
    imshow("dst2", dst);
    waitKey();

    return 0;
}