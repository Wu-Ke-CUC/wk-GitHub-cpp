#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution 
{
	public:
		#pragma region 1.两数之和
		vector<int> twoSum(vector<int>& nums, int target)
		{
			for (int i = 0; i < nums.size(); i++)
			{
				for (int j = i + 1; j < nums.size(); j++)
				{
					if (nums[i] + nums[j] == target)
					{
						return { i, j };
					}
				}
			}
			return {};
		}
		#pragma endregion
		#pragma region 2.两数相加
		ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
		{
			ListNode* head = nullptr; ListNode* tail = nullptr;
			int carry = 0;
			while (l1 || l2)
			{
				int n1 = l1 ? l1->val : 0, n2 = l2 ? l2->val : 0;
				int sum = n1 + n2 + carry;
				if (head == nullptr)
				{
					head = tail = new ListNode(sum % 10);
				}
				else
				{
					tail->next = new ListNode(sum % 10);
					tail = tail->next;
				}
				carry = sum / 10;
				if (l1) { l1 = l1->next; }
				if (l2) { l2 = l2->next; }
			}
			if (carry != 0)
			{
				tail->next = new ListNode(carry);
				tail = tail->next;
			}
			return head;
		}
		#pragma endregion
		#pragma region 3.无重复字符的最长字串
		int lengthOfLongestSubstring(string s) {
			int ret = 0;
			int left = 0;
			unordered_set<char> hashTable;
			for (int right = 0; right < s.length(); right++)
			{
				while(hashTable.count(s[right]))
				{
					hashTable.erase(s[left]);
					left++;
				}
				hashTable.insert(s[right]);
				ret = max(ret, right - left + 1);
			}
			return ret;
		}
		#pragma endregion
		#pragma region 4.寻找两个正序数组的中位数
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
		{
			int n1 = nums1.size();
			int n2 = nums2.size();
			int n = 0, m = 0;
			vector<int> addArray(n1 + n2);
			int temp = 0;
			while (n != n1 && m != n2)
			{
				if (nums1[n] < nums2[m])
				{
					addArray[temp++] = nums1[n++];
				}
				else
				{
					addArray[temp++] = nums2[m++];
				}
			}
			while (n != n1)
			{
				addArray[temp++] = nums1[n++];
			}
			while (m != n2)
			{
				addArray[temp++] = nums2[m++];
			}
			if (temp % 2 == 1)
			{
				return (double)addArray[temp / 2];
			}
			else
			{
				return (addArray[temp / 2 - 1] + addArray[temp / 2]) / (double)2;
			}
		}
		#pragma endregion

};

int main()
{
	#pragma region 1.两数之和
	vector<int> nums = { 2, 7, 11, 15 };
	int target = 9;
	Solution solution;
	vector<int> result = solution.twoSum(nums, target);
	for (int index : result)
	{
		cout << index << " ";
	}
	cout << endl;
	#pragma endregion
	#pragma region 2.两数相加
	ListNode* l1 = new ListNode(8, new ListNode(6, new ListNode(5)));
	ListNode* l2 = new ListNode(2, new ListNode(3, new ListNode(4)));
	ListNode* ret = solution.addTwoNumbers(l1, l2);
	while (ret)
	{
		cout << ret->val;
		ret = ret->next;
	}
	cout << endl;
	#pragma endregion
	#pragma region 3.无重复字符的最长字串
	int maxLength = solution.lengthOfLongestSubstring("abcacbb");
	cout << maxLength << endl;
	#pragma endregion
	#pragma region 4.寻找两个正序数组的中位数
	vector<int> nums1 = { 1,2,4 };
	vector<int> nums2 = { 2,5,6 };
	double med = solution.findMedianSortedArrays(nums1, nums2);
	cout << med << endl;
	#pragma endregion

	return 0;
}