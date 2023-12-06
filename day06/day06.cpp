#include <iostream>
#include <fstream>
#include <regex>
#include <numeric>
#include <sstream>

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    std::regex num_reg{"\\d+"};
    std::vector<std::vector<int>> race_data;
    race_data.reserve(2);
    if (data.is_open())
    {
        std::string line;
        int currIdx = 0;
        while (std::getline(data, line))
        {
            std::sregex_token_iterator word_begin{line.begin(), line.end(), num_reg};
            const std::sregex_token_iterator word_end;
            std::vector<int> curr_race_data;
            while(word_begin != word_end) {
                curr_race_data.push_back(std::stoi(word_begin->str()));
                word_begin++;
            }
             race_data.push_back(curr_race_data);
            currIdx++;
        }
        data.close();
    }
    auto times = race_data[0];
    auto records = race_data[1];

    std::vector<int> winning_counts{};
    std::ostringstream time_oss;
    std::ostringstream record_oss;

    for(int i = 0; i < times.size(); i++) {
        int winning_count = 0;
        int current_time = times[i];
        int current_record = records[i];
        time_oss << current_time;
        record_oss << current_record;
        for(int j = 0; j < times[i]; j++) {
            int distance = j * (current_time - j);
            if (distance > current_record) {
                winning_count++;
            }
        }
        winning_counts.push_back(winning_count);
    }
    
    for(auto ele : winning_counts) {
        std::cout << ele << '\n';
    }

    int result = std::reduce(winning_counts.begin(), winning_counts.end(), 1, std::multiplies<int>() );

    std::cout << result << '\n'; 

    long long time = std::stoll(time_oss.str());
    long long record = std::stoll(record_oss.str());
    long long winning_times = 0;
    for(long long i = 0; i < time; i++) {
        long long distance = i * (time - i);
        if(distance > record) {
            winning_times++;
        }
    }

    std::cout << winning_times << '\n';
    
}