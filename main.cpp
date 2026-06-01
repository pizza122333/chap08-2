#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 원본 사진(src)을 불러와요
    Mat src = imread("lenna.bmp"); // 과제 사진 속 인물의 이름이 '레나'예요!
    if (src.empty()) {
        cerr << "사진을 찾을 수 없어요!" << endl;
        return -1;
    }

    // 2. 가로(X축)로 45도 기우는 마법의 지도 M을 만들어요 (기울기 비율 = 1)
    Mat M = (Mat_<double>(2, 3) << 1, 1, 0,
        0, 1, 0);

    // 3. 지도를 가지고 사진을 밀어줘요! 
    // 이때 맨 뒤에 BORDER_REPLICATE를 넣어 가장자리 색으로 빈곳을 채웁니다.
    Mat dst;
    warpAffine(src, dst, M, Size(src.cols * 2, src.rows), INTER_LINEAR, BORDER_REPLICATE);
    // 팁: 옆으로 밀리니까 가로 크기를 원본의 2배(src.cols * 2)로 넉넉하게 잡아주면 잘리지 않아요!

    // 4. 결과를 화면에 보여줍니다
    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    return 0;
}