#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 원본 사진(src)을 불러와요 (사진 이름이 "tekapo.jpg"라고 가정해볼게요)
    Mat src = imread("tekapo.bmp");
    if (src.empty()) {
        cerr << "사진을 찾을 수 없어요!" << endl;
        return -1;
    }

    // 2. 이동하기 전의 점 3개와 이동한 후의 점 3개를 컴퓨터에게 알려줘요
    Point2f srcPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols, 0);
    srcPts[2] = Point2f(0, src.rows);

    Point2f dstPts[3];
    dstPts[0] = Point2f(150, 100);
    dstPts[1] = Point2f(src.cols + 150, 100);
    dstPts[2] = Point2f(150, src.rows + 100);

    // 3. [주문 1] 두 점들을 비교해서 "이동 지도(M)"를 만들어요
    Mat M = getAffineTransform(srcPts, dstPts);

    // 4. 과제 화면에 나온 것처럼 숫자 표(지도)를 검은 창에 출력해봐요
    cout << M << endl;

    // 5. [주문 2] 지도를 가지고 실제로 사진을 이동시켜서 결과 사진(dst)을 만들어요
    Mat dst;
    warpAffine(src, dst, M, src.size());

    // 6. 원본 사진과 완성된 결과 사진을 화면에 보여줘요
    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    return 0;
}