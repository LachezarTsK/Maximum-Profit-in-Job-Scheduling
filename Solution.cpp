
#include <queue>
#include <vector>
using namespace std;

struct Job {
    int startTime{};
    int endTime{};
    int profit{};
    Job(int startTime, int endTime, int profit) : startTime{startTime}, endTime{endTime}, profit{profit} {}
};

struct AccumulatedProfitTillCurrentEndTime {
    int endTime{};
    int accumulatedProfit{};
    AccumulatedProfitTillCurrentEndTime(int endTime, int accumulatedProfit) : endTime{endTime}, accumulatedProfit{accumulatedProfit} {}
};

class Solution {
    
public:
    int jobScheduling(const vector<int>& startTime, const vector<int>& endTime, const vector<int>& profit) const {

        size_t totalNumberOfJobs = startTime.size();
        vector<Job> jobs;
        for (int i = 0; i < totalNumberOfJobs; ++i) {
            jobs.emplace_back(startTime[i], endTime[i], profit[i]);
        }
        //C++20: std::ranges::sort(jobs, comparator);
        sort(jobs.begin(), jobs.end(), [](const Job& first, const Job & second) {
            return first.startTime < second.startTime; });

        auto comparator = [](const auto& first, const auto& second) {return first.endTime > second.endTime;};
        priority_queue<AccumulatedProfitTillCurrentEndTime, vector<AccumulatedProfitTillCurrentEndTime>, decltype(comparator) > minHeapEndTime(comparator);
        int maximumProfit = 0;

        for (Job current : jobs) {
            while (!minHeapEndTime.empty() && minHeapEndTime.top().endTime <= current.startTime) {
                maximumProfit = max(maximumProfit, minHeapEndTime.top().accumulatedProfit);
                minHeapEndTime.pop();
            }
            minHeapEndTime.emplace(current.endTime, maximumProfit + current.profit);
        }

        while (!minHeapEndTime.empty()) {
            maximumProfit = max(maximumProfit, minHeapEndTime.top().accumulatedProfit);
            minHeapEndTime.pop();
        }

        return maximumProfit;
    }
};
