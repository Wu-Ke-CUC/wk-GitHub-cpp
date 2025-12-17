#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
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
			/*for (int i = 0; i < nums.size(); i++)
			{
				for (int j = i + 1; j < nums.size(); j++)
				{
					if (nums[i] + nums[j] == target)
					{
						return { i, j };
					}
				}
			}
			return {};*/
			unordered_map<int,int> hashTable;
			for (int i = 0; i < nums.size(); i++)
			{
				auto it = hashTable.find(target - nums[i]);
				if (it != hashTable.end())
				{
					return { it->second,i };
				}
				hashTable[nums[i]] = i;
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
				size_t n1 = l1 ? l1->val : 0, n2 = l2 ? l2->val : 0;
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
		#pragma region 5.最长回文字串
		string longestPalindrome(string s) 
		{
			/*int len = 0;
			string ret = "";
			for (int i = 0; i < s.length(); i++)
			{
				for (int j = s.length() - 1; j >= i; j--) 
				{
					int left = i, right = j;
					int isPalindrome = true;
					while (left <= right)
					{
						if (s[left] != s[right])
						{
							isPalindrome = false;
							break;
						}
						left++; right--;
					}
					if (isPalindrome)
					{
						if (j - i + 1 > len)
						{
							len = j - i + 1;
							ret = s.substr(i, j - i + 1);
						}
					}
				}
			}
			return ret;*/
			//中心扩展算法
			int start = 0, end = 0;
			for (int i = 0; i < s.length(); i++)
			{
				auto [left1, right1] = expendAroundCenter(s, i, i);
				auto [left2, right2] = expendAroundCenter(s, i, i + 1);
				if (right1 - left1 > end - start)
				{
					start = left1;
					end = right1;
				}
				if (right2 - left2 > end - start)
				{
					start = left2;
					end = right2;
				}
			}
			return s.substr(start, end - start + 1);
		}
		pair<int, int> expendAroundCenter(string s, int left, int right)
		{
			while (left >= 0 && right <= s.length() && s[left] == s[right])
			{
				left--, right++;
			}
			return { left + 1,right - 1 };
		}
		#pragma endregion
		#pragma region 6.Z字变换
		/*示例 1：
			输入：s = "PAYPALISHIRING", numRows = 3
			输出："PAHNAPLSIIGYIR"
			P   A   H   N
			A P L S I I G
			Y   I   R   
		  示例 2：
			输入：s = "PAYPALISHIRING", numRows = 4
			输出："PINALSIGYAHRPI"
			P     I    N
			A   L S  I G
			Y A   H R
			P     I
		  示例 3：
			输入：s = "A", numRows = 1
			输出："A"*/
		string convert(string s, int numRows) 
		{
			if (numRows == 1 || numRows >= s.length()) 
			{
				return s;
			}
			string ret;
			int t = numRows * 2 - 2;
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j + i < s.length(); j += t)
				{
					ret += s[j + i];
					if (i > 0 && i < numRows - 1 && j + t - i < s.length())
					{
						ret += s[j + t - i];
					}
				}
			}
			return ret;
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
	#pragma region 5.最长回文字串
	string palindrome = solution.longestPalindrome("bbcabacb");
	cout << palindrome << endl;
	#pragma endregion
	#pragma region 6.Z字变换
	string convertRet = solution.convert("PAYPALISHIRING", 3);
	cout << convertRet << endl;
	#pragma endregion

	return 0;
}