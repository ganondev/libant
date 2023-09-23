#pragma once
#include <gtest/gtest.h>
#include "../libant.h"

template<coords Bounds={0, 0}>
class AutomatonTestFixtures : public ::testing::TestWithParam<const char *> {
public:
    la_spatial_structure * backend;

    static std::vector<const char *> sharedParams() {
        return {
            "la_matrix",
            "la_quadtree"
            // Add other backend types here as string identifiers
        };
    }

    void SetUp() override {
        std::string type = GetParam();
        if (type == "la_matrix") {
            backend = new la_matrix(Bounds);
        } else if (type == "la_quadtree") {
            backend = new la_quadtree(Bounds);
        }
        // Add other backend types here
    }

    void TearDown() override {
        delete backend;
    }
};

template<typename TestClass>
std::string customTestName(const ::testing::TestParamInfo<typename TestClass::ParamType>& info) {
    std::string type = info.param;  // Assuming ParamType is const char*
    return type;  // Replace special characters if needed
}