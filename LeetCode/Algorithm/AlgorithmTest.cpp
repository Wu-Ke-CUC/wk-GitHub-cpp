#include<iostream>
#include<vector>
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

		}
		#pragma endregion
};

int main()
{
	vector<int> nums = { 2, 7, 11, 15 };
	int target = 9;
	Solution solution;
	vector<int> result = solution.twoSum(nums, target);
	for (int index : result)
	{
		cout << index << " ";
	}
	return 0;
}