
import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution {

    private record Job(int startTime, int endTime, int profit) {}
    private record AccumulatedProfitTillCurrentEndTime(int endTime, int accumulatedProfit) {}

    public int jobScheduling(int[] startTime, int[] endTime, int[] profit) {

        int totalNumberOfJobs = startTime.length;
        Job[] jobs = new Job[totalNumberOfJobs];
        for (int i = 0; i < totalNumberOfJobs; ++i) {
            jobs[i] = new Job(startTime[i], endTime[i], profit[i]);
        }
        Arrays.sort(jobs, (first, second) -> first.startTime - second.startTime);

        PriorityQueue<AccumulatedProfitTillCurrentEndTime> minHeapEndTime = new PriorityQueue<>((first, second) -> first.endTime - second.endTime);
        int maximumProfit = 0;

        for (Job current : jobs) {
            while (!minHeapEndTime.isEmpty() && minHeapEndTime.peek().endTime <= current.startTime) {
                maximumProfit = Math.max(maximumProfit, minHeapEndTime.peek().accumulatedProfit);
                minHeapEndTime.poll();
            }
            minHeapEndTime.add(new AccumulatedProfitTillCurrentEndTime(current.endTime, maximumProfit + current.profit));
        }

        while (!minHeapEndTime.isEmpty()) {
            maximumProfit = Math.max(maximumProfit, minHeapEndTime.peek().accumulatedProfit);
            minHeapEndTime.poll();
        }

        return maximumProfit;
    }
}
