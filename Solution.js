
//const {MinPriorityQueue} = require('@datastructures-js/priority-queue');

/**
 * @param {number[]} startTime
 * @param {number[]} endTime
 * @param {number[]} profit
 * @return {number}
 */
var jobScheduling = function (startTime, endTime, profit) {

    const totalNumberOfJobs = startTime.length;
    const jobs = new Array(totalNumberOfJobs);
    for (let i = 0; i < totalNumberOfJobs; ++i) {
        jobs[i] = new Job(startTime[i], endTime[i], profit[i]);
    }
    jobs.sort((first, second) => first.startTime - second.startTime);

    //PriorityQueue<AccumulatedProfitTillCurrentEndTime>
    const minHeapEndTime = new MinPriorityQueue({compare: (first, second) => first.endTime - second.endTime});
    let maximumProfit = 0;

    for (let current of jobs) {
        while (!minHeapEndTime.isEmpty() && minHeapEndTime.front().endTime <= current.startTime) {
            maximumProfit = Math.max(maximumProfit, minHeapEndTime.front().accumulatedProfit);
            minHeapEndTime.dequeue();
        }
        minHeapEndTime.enqueue(new AccumulatedProfitTillCurrentEndTime(current.endTime, maximumProfit + current.profit));
    }

    while (!minHeapEndTime.isEmpty()) {
        maximumProfit = Math.max(maximumProfit, minHeapEndTime.front().accumulatedProfit);
        minHeapEndTime.dequeue();
    }

    return maximumProfit;
};

/**
 * @param {number} startTime
 * @param {number} endTime
 * @param {number} profit
 */
function Job(startTime, endTime, profit) {
    this.startTime = startTime;
    this.endTime = endTime;
    this.profit = profit;
}

/**
 * @param {number} endTime
 * @param {number} accumulatedProfit
 */
function AccumulatedProfitTillCurrentEndTime(endTime, accumulatedProfit) {
    this.endTime = endTime;
    this.accumulatedProfit = accumulatedProfit;
}
