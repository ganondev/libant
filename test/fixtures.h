#pragma once
#include <gtest/gtest.h>
#include "../libant.h"

class AutomatonTestFixtures : public ::testing::TestWithParam<const char *>
{
public:

    static std::vector<const char *> shared_params()
    {
        return {
            "la_matrix",
            "la_quadtree",
            // Add other backend types here as string identifiers
        };
    }

    std::unique_ptr<la_spatial_structure> get_backend(coords bounds) const
    {
        std::string type = GetParam();
        if (type == "la_matrix") {
            return std::make_unique<la_matrix>(bounds);
        } else if (type == "la_quadtree") {
            return std::make_unique<la_quadtree>(bounds);
        }
        EXPECT_NE(true, true) << "Invalid backend type: " << type;
        return std::make_unique<la_matrix>(bounds);;
    }

    void SetUp() override
    {
        
    }

    void TearDown() override {
        
    }
};

template<typename TestClass>
std::string custom_test_name(const ::testing::TestParamInfo<typename TestClass::ParamType>& info) {
    std::string type = info.param;  // Assuming ParamType is const char*
    return type;  // Replace special characters if needed
}