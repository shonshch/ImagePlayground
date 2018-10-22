#include <gtest/gtest.h>
#include "../../Detection/detection.h"



    TEST(detectorTests, notExistingDirectory) {
        Detector d;
        string path="";
        Image test(path);
        DetectedData a =d.Detect(test);
        ASSERT_EQ(true, a.CircleBound.empty());
        ASSERT_EQ(true, a.RectBound.empty());
        ASSERT_EQ(true, a.SquareBound.empty());
    }


    TEST(detectorTests, invalidFileFormat) {
    Detector d;
    string path = "../resources/doc.odt";
    Image test(path);
    DetectedData a = d.Detect(test);
    ASSERT_EQ(true, a.CircleBound.empty());
    ASSERT_EQ(true, a.RectBound.empty());
    ASSERT_EQ(true, a.SquareBound.empty());
    }

    TEST(detectorTests, notExistingFile) {
    Detector d;
    string path="../resources/foo.png";
    Image test(path);

    DetectedData a = d.Detect(test);
    ASSERT_EQ(true, a.CircleBound.empty());
    ASSERT_EQ(true, a.RectBound.empty());
    ASSERT_EQ(true, a.SquareBound.empty());
    }

TEST(detectorTests, rectDetection) {
    Detector d;
    string path="../resources/Rectangle_.png";
    Image test(path);

    DetectedData a = d.Detect(test);
    Rect testRect(48,44,362,217);
    ASSERT_EQ(0, a.CircleBound.size());
    ASSERT_EQ(0, a.SquareBound.size());
    ASSERT_EQ(1, a.RectBound.size());
    ASSERT_EQ(testRect, a.RectBound[0]);

}

TEST(detectorTests, suqareDetection) {
    Detector d;
    string path="../resources/square.png";
    Image test(path);

    DetectedData a = d.Detect(test);
    Rect testRect(64,64,475,475);
    ASSERT_EQ(0, a.CircleBound.size());
    ASSERT_EQ(1, a.SquareBound.size());
    ASSERT_EQ(testRect, a.SquareBound[0]);
    ASSERT_EQ(0, a.RectBound.size());
}


    TEST(detectorTests, circleDetection) {
    Detector d;
    string path="../resources/circle.png";
    Image test(path);

    DetectedData a = d.Detect(test);

    Rect testRect(33,13,176,176);
    ASSERT_EQ(testRect, a.CircleBound[0]);
    ASSERT_EQ(1, a.CircleBound.size());
    ASSERT_EQ(0, a.SquareBound.size());
    ASSERT_EQ(0, a.RectBound.size());
    }

    int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
