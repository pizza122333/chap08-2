#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 내 컴퓨터의 웹캠(카메라)을 켭니다. (0번 카메라)
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "카메라를 켤 수 없어요!" << endl;
        return -1;
    }

    Mat frame, dst;
    // 처음에는 'a' 모드(원본 상태)로 시작할게요!
    char mode = 'a';

    while (true) {
        // 2. 카메라로부터 현재 순간의 동영상 한 장면(frame)을 가져와요
        cap >> frame;
        if (frame.empty()) break;

        // 3. 현재 모드가 무엇이냐에 따라 다른 화면을 보여줘요
        if (mode == 'a') {
            // [a 모드] 원본 그대로 출력하기
            imshow("video", frame);
        }
        else if (mode == 'b') {
            // [b 모드] 과제 5번처럼 반으로 줄여서 정중앙에 놓기
            float W = frame.cols;
            float H = frame.rows;

            Point2f srcPts[3] = { Point2f(0, 0), Point2f(W, 0), Point2f(0, H) };
            Point2f dstPts[3] = { Point2f(W / 4.0f, H / 4.0f),
                                  Point2f(3.0f * W / 4.0f, H / 4.0f),
                                  Point2f(W / 4.0f, 3.0f * H / 4.0f) };

            Mat M = getAffineTransform(srcPts, dstPts);
            warpAffine(frame, dst, M, frame.size());

            imshow("video", dst);
        }

        // ?? [가장 중요!] 반복문 안에서 waitKey는 딱 한 번만 호출해서 상자에 저장해요!
        int key = waitKey(30); // 30밀리초 동안 키 입력을 기다려요

        // 4. 저장된 키가 무엇인지 확인하고 모드를 바꾸거나 종료해요
        if (key == 'a' || key == 'A') {
            mode = 'a'; // a를 누르면 원본 모드로 변경!
        }
        else if (key == 'b' || key == 'B') {
            mode = 'b'; // b를 누르면 축소+중앙 모드로 변경!
        }
        else if (key == 'q' || key == 'Q') {
            break; // q를 누르면 무한 반복문을 탈출해서 프로그램 종료!
        }
    }

    return 0;
}