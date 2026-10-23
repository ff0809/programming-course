#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>& nums, int a, int b) {
    int i = a;
    int j = b + 1;
    int x = nums[a];
    while (true) {
        while (nums[++i] < x && i < b);
        while (nums[--j] > x);
        if (i >= j)break;
        swap(nums[i], nums[j]);
    }
    nums[a] = nums[j];
    nums[j] = x;
    return j;
}

int randompartition(vector<int>& nums, int a, int b)
{
    int c = rand() % (b - a + 1) + a;
    swap(nums[a], nums[c]);
    return partition(nums, a, b);
}

int randomquickselect(vector<int>& nums, int a, int b, int target) {
    if (a == b) return nums[a];
    int pos = randompartition(nums, a, b);
    if (pos == target) return nums[pos];
    else if (pos < target) return randomquickselect(nums, pos + 1, b, target);
    else return randomquickselect(nums, a, pos - 1, target);
}

int findKthLargest(vector<int>& nums, int k) {
    int length = nums.size();
    return randomquickselect(nums, 0, length - 1, length - k);
}

int main()
{
    cout << "请依次输入数组中元素(以-1结束），最后输入要查找第几大的元素：" << endl;
    int a;
    vector<int>nums;
    while (true)
    {
        cin >> a;
        nums.push_back(a);
        if (a == -1)break;
    }
    int k;
    cin >> k;
    cout << findKthLargest(nums, k);
	return 0;
}