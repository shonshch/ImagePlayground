#include <Tests/lib/googletest/googletest/include/gtest/gtest.h>
#include <Modify/modifier.h>

using namespace cv;

TEST(Make_Box, Circle_Box_10_on_10){
    Mat source = Mat::zeros(10, 10, CV_8UC3);
    Modifier modifier;
    DetectedData data;
    vector<Rect> * BoundRect = new vector<Rect>[3];
    Rect box(0, 0, 9, 9);
    BoundRect[0].push_back(box);
    data = DetectedData{BoundRect[0], BoundRect[1], BoundRect[2]};
    modifier.drawBox(data, source);
    Scalar color;
    color = source.at<uchar>(Point(0, 0));
    EXPECT_TRUE(color == Scalar(255,0,0));
    color = source.at<uchar>(Point(9, 9));
    EXPECT_TRUE(color == Scalar(255,0,0));
    color = source.at<uchar>(Point(0, 9));
    EXPECT_TRUE(color == Scalar(255,0,0));
    color = source.at<uchar>(Point(9, 0));
    EXPECT_TRUE(color == Scalar(255,0,0));
}

TEST(Make_Box, Empty_Data_Set){
    Mat source = Mat::zeros(10, 10, CV_8UC3);
    Modifier modifier;
    DetectedData data;
    vector<Rect> * BoundRect = new vector<Rect>[3];
    data = DetectedData{BoundRect[0], BoundRect[1], BoundRect[2]};
    modifier.drawBox(data, source);
    Scalar color;
    color = source.at<uchar>(Point(0, 0));
    EXPECT_TRUE(color == Scalar(0,0,0));
    color = source.at<uchar>(Point(9, 9));
    EXPECT_TRUE(color == Scalar(0,0,0));
    color = source.at<uchar>(Point(0, 9));
    EXPECT_TRUE(color == Scalar(0,0,0));
    color = source.at<uchar>(Point(9, 0));
    EXPECT_TRUE(color == Scalar(0,0,0));
}




