#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


///////////////////  Images  //////////////////////
void main() {
    ///////////////////  Basic Functions  //////////////////////
    //if (0) {
    //  
    //string path = "Resources/cards.jpg";
    //Mat img = imread(path);
    //Mat imgGray;
    //Mat imgBlur;
    //Mat imgCanny;
    //Mat imgDilation;
    //Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    //cvtColor(img, imgGray, COLOR_BGR2GRAY);

    //GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
    //Canny(imgBlur, imgCanny, 50, 100);
    //dilate(imgCanny, imgDilation, kernel);

    //imshow("Image", imgDilation);
    //waitKey(0);
    //
    //
    /////////////////////  Basic Functions  //////////////////////
    //string path = "Resources/cards.jpg";
    //Mat img = imread(path);
    //Mat img_resized;
    //Mat img_cropped;
    //Rect roi(100, 100, 300, 250);

    //cout << img.size() << endl;
    //resize(img, img_resized, Size(), 0.5, 0.5);
    //img_cropped = img(roi);

    //imshow("Image", img_cropped);
    //waitKey(0);   

    
    ///////////////////  Basic Functions  //////////////////////
    string path = "Resources/test.png";
    Mat img = imread(path);
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()){
        cout << "Not loaded!" << endl;
    }

    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 255, 255), 3);
    }

    imshow("Image", img);
    waitKey(0);
}

///////////////////  Videos  //////////////////////
//void main() {
//    string path = "Resources/test_video.mp4";
//    VideoCapture cap(0);
//    Mat img;
//
//    while (true)
//    {
//        cap.read(img);
//        imshow("Image", img);
//        waitKey(1);
//    }
//}