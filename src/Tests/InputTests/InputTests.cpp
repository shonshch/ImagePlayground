#include <gtest/gtest.h>
#include "../../InputHandler/InputHandler.h"
#include "../../Utilities/Image.h"

TEST(inputTests, isGetAllDirectory) {
    InputHandler inputHandler;
    vector<Image> images;
    inputHandler.GetImages("../resources", images );
    ASSERT_EQ(5, images.size());
}

TEST(inputTests, notExistingDirectory) {
    InputHandler inputHandler;
    vector<Image> images;
    inputHandler.GetImages("", images );
    ASSERT_EQ(0, images.size());
}

