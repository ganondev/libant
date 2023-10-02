#pragma once
#include <functional>
#include <unordered_map>
#include <variant>

struct coords;

namespace libant
{
    struct condition {
        coords relative_position;
        std::function<bool(int)> predicate;
    };

    struct assignment {
        coords relative_position;
        char variable_name;
    };

    struct invalid_variable_exception final : std::exception {
        char name;
        std::string message; // Store the message as a member variable

        explicit invalid_variable_exception(const char name):
            name(name),
            message("Invalid variable name: " + std::string(1, name)) {}

        [[nodiscard]]
        const char * what() const noexcept override {
            return message.c_str();
        }
    };

    struct symbols {
        std::unordered_map<char, int> table;
        explicit symbols(const std::unordered_map<char, int>& values) : table(values) {}

        [[nodiscard]]
        int value_of(const char& key) const
        {
            if (const auto it = table.find(key); it != table.end()) {
                return it->second;
            }
            throw invalid_variable_exception(key);
        }
    };
    
    class rule {
        
        int radius_ = 0;

        void update_radius(const coords& new_coords)
        {
            const int new_radius = static_cast<int>(std::max(std::abs(new_coords.x), std::abs(new_coords.y)));
            radius_ = std::max(radius_, new_radius);
        }
        
    public:
        std::vector<condition> conditions;
        std::vector<assignment> assignments;
        std::function<int(const symbols&)> mapper;

        rule& cell_matches_scalar(const coords relative_coords, int scalar) {
            const std::function predicate = [scalar](const int value) { return value == scalar; };
            return cell_satisfies_predicate(relative_coords, predicate);
        }

        rule& cell_satisfies_predicate(const coords relative_coords, const std::function<bool(int)>& predicate) {
            conditions.push_back({relative_coords, predicate});
            update_radius(relative_coords);
            return *this;
        }
        
        rule& variable_cell(const coords relative_coords, const char name) {
            assignments.push_back({relative_coords, name});
            update_radius(relative_coords);
            return *this;
        }

        // TODO what happens if the variable doesn't exist?
        rule& maps_to(std::function<int(const symbols&)> fn) {
            mapper = std::move(fn);
            return *this;
        }

        [[nodiscard]]
        int radius() const {
            return radius_;
        }
        
        [[nodiscard]] 
        int apply(const std::vector<std::vector<int>>& slice) const {
            std::unordered_map<char, int> variables;

            // Calculate the center of the slice
            int center_y = static_cast<int>(slice.size() / 2);
            int center_x = static_cast<int>(slice[0].size() / 2);

            // Validate conditions
            for (const auto& [relative_position, predicate] : conditions) {
                int y = center_y + relative_position.y;
                int x = center_x + relative_position.x;
                if (!predicate(slice[y][x])) {
                    return 0;  // Condition failed based on predicate
                }
            }

            // Assign variables
            for (const auto& [relative_position, variable_name] : assignments) {
                int y = center_y + relative_position.y;
                int x = center_x + relative_position.x;
                variables[variable_name] = slice[y][x];
            }

            try
            {
                // Call the mapper function
                return mapper(symbols{variables});
            }
            catch (const invalid_variable_exception& e)
            {
                std::cerr << "Encountered exception in application of rule: " << e.what() << std::endl;
                return 0;
            }
        }
    };

    // inline int apply_rule(const rule& rule, const coords& center_coord) {
    //     const rule::cell_map_t cell_slice = get_cells_around(center_coord);  // To be implemented in derived classes
    //     return rule.apply(cell_slice);
    // }
    
}