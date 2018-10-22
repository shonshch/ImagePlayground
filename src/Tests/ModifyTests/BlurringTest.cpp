#include <gtest/gtest.h>
#include "../../Modify/modifier.h"

TEST(BlurImage, checkBlurChanged){
    Mat source(10, 10, CV_8UC3, Scalar(0,0,0));
    Mat whites=Mat::zeros(3,3,CV_8UC3);
    //change the source
    source.ptr(1,1)[0]= 1;
    source.ptr(1,3)[0]= 1;

    Mat dest=source.clone();
    Modifier modifier;
    vector<Rect> data;
    Rect test(1,1,4,4);
    data.push_back(test);
    modifier.blurPart(data,dest);
    int check =countNonZero(source!= dest);
    EXPECT_NE(0, check);
}

TEST(BlurImage, checkBlurDecreasedGradient){
    Mat source(10, 10, CV_8UC3, Scalar(0,0,0));
    Mat whites=Mat::zeros(3,3,CV_8UC3);
    //change the source
    source.ptr(1,1)[0]= 1;
    source.ptr(1,3)[0]= 1;

    Mat dest=source.clone();
    Modifier modifier;
    vector<Rect> data;
    Rect test(1,1,4,4);
    data.push_back(test);
    modifier.blurPart(data,dest);
    //calc gradients
    cv::Mat Dx;
    cv::Sobel(source, Dx, CV_64F, 1, 0, 3);
    cv::Mat Dy;
    cv::Sobel(source, Dy, CV_64F, 0, 1, 3);


    cv::Mat Dx_d;
    cv::Sobel(dest, Dx_d, CV_64F, 1, 0, 3);
    cv::Mat Dy_d;
    cv::Sobel(dest, Dy_d, CV_64F, 0, 1, 3);

    Scalar meanGradX = mean(abs( Dx) );
    Scalar meanGradY = mean( abs(Dy ));

    Scalar meanGradX_d = mean( abs(Dx_d ));
    Scalar meanGradY_d = mean(abs( Dy_d) );

    EXPECT_GT(meanGradX.val[0],meanGradX_d.val[0] );
    EXPECT_GT(meanGradY.val[0],meanGradY_d.val[0] );

}



TEST(BlurImage, checkBlurChangedRect){
    Mat source(10, 10, CV_8UC3, Scalar(0,0,0));
    Mat whites=Mat::zeros(3,3,CV_8UC3);
    //change the source
    source.ptr(1,1)[0]= 1;
    source.ptr(1,3)[0]= 1;

    Mat dest=source.clone();
    Modifier modifier;
    vector<Rect> data;
    Rect test(1,1,4,4);
    data.push_back(test);
    modifier.blurPart(data,dest);
    int check =countNonZero(source(test)!= dest(test));
    EXPECT_NE(0, check);
}