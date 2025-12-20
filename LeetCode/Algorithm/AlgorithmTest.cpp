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
			/*int l1 = nums1.size(), l2 = nums2.size();
			int sum = l1 + l2;
			int index1 = 0, index2 = 0;
			int n1 = 0, n2 = 0;
			while (index1 + index2 <= sum / 2)
			{
				if (nums1[index1] < nums2[index2])
				{
					index2++;
					if (index1 + index2 == sum / 2 - 1)
					{
						n1 = nums2[index2];
					}
					else if (index1 + index2 == sum / 2)
					{

					}
				}
			}*/
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
		#pragma region 7.整数反转
		int reverse(int x) 
		{
			int ret = 0;
			while (x)
			{
				if (ret > INT32_MAX / 10 || ret < INT32_MIN / 10)
				{
					return 0;
				}
				int digit = x % 10;
				x /= 10;
				ret = ret * 10 + digit;
			}
			return ret;
		}
		#pragma endregion
		#pragma region 8.atoi
		int myAtoi(string s) {
			if (s == "")
			{
				return 0;
			}
			int ret = 0;
			int index = 0;
			int symbol = 1;
			while (s[index] < '0' || s[index] > '9' && index < s.size())
			{
				if (s[index] == ' ')
				{
					return 0;
				}
				index++;
			}
			if (index > 0 && s[index - 1] == '-')
			{
				symbol = -1;
			}
			while (s[index] >= '0' && s[index] <= '9' && index<s.size())
			{
				if (ret < INT32_MAX / 10)
				{
					ret = ret * 10 + (s[index++] - '0');
				}
			}
			return ret * symbol;
		}
		#pragma endregion
		#pragma region 9.回文数
		bool isPalindrome(int x) 
		{
			if (x < 0)return false;
			int ret = 0;
			int temp = x;
			while (temp)
			{
				int digit = temp % 10;
				temp /= 10;
				ret = ret * 10 + digit;
				if (ret > INT32_MAX / 10) return false;
			}
			return ret == x ? true : false;
		}
		#pragma endregion
		#pragma region 10.正则表达式匹配 （非自主）
		bool isMatch(string s, string p) 
		{
			int m = s.size();
			int n = p.size();

			// dp[i][j] 表示 s[0..i-1] 是否能匹配 p[0..j-1]
			vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

			dp[0][0] = true;

			// 处理 p 形如 a* a*b* 能匹配空串的情况
			for (int j = 2; j <= n; j++)
			{
				if (p[j - 1] == '*')
					dp[0][j] = dp[0][j - 2];
			}

			for (int i = 1; i <= m; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					// 普通字符 或 '.'
					if (p[j - 1] == '.' || p[j - 1] == s[i - 1])
					{
						dp[i][j] = dp[i - 1][j - 1];
					}
					// '*'
					else if (p[j - 1] == '*')
					{
						// 匹配 0 次
						dp[i][j] = dp[i][j - 2];

						// 匹配 1 次或多次
						if (p[j - 2] == '.' || p[j - 2] == s[i - 1])
						{
							dp[i][j] = dp[i][j] || dp[i - 1][j];
						}
					}
				}
			}

			return dp[m][n];
		}
		#pragma endregion
		#pragma region 11.装水最多的容器
		int maxArea(vector<int>& height) {
			//方法1
			/*int ret = 0;
			for (int i = 0; i < height.size(); i++)
			{
				for (int j = i; j < height.size(); j++)
				{
					int v = min(height[i], height[j]) * (j - i);
					ret = max(ret, v);
				}
			}
			return ret;*/
			//方法2
			int left = 0, right = height.size() - 1;
			int ret = 0;
			while (left < right)
			{
				int tempS = min(height[left], height[right]) * (right - left);
				ret = max(ret, tempS);
				height[left] < height[right] ? left++ : right--;
			}
			return ret;
		}
		#pragma endregion
		#pragma region 12.整数转罗马数字
		string intToRoman(int num) {
			pair<int, string> valueSymbol[] = { {1000, "M"},{900,  "CM"},{500,  "D"},{400,  "CD"},{100,  "C"},
												{90,   "XC"},{50,   "L"},{40,   "XL"},{10,   "X"},{9,    "IX"},
												{5,    "V"},{4,    "IV"},{1,    "I"},};
			string ret = "";
			for (const auto& [value, symbol] : valueSymbol)
			{
				while (num >= value)
				{
					ret += symbol;
					num -= value;
				}
				if (num == 0)break;
			}
			return ret;
		}
		#pragma endregion

};

int main()
{
	Solution solution;
#pragma region 1.两数之和
	{
		vector<int> nums = { 2, 7, 11, 15 };
		int target = 9;
		vector<int> result = solution.twoSum(nums, target);
		for (int index : result)
		{
			cout << index << " ";
		}
		cout << endl;
	}
#pragma endregion
#pragma region 2.两数相加
	{
		ListNode* l1 = new ListNode(8, new ListNode(6, new ListNode(5)));
		ListNode* l2 = new ListNode(2, new ListNode(3, new ListNode(4)));
		ListNode* ret = solution.addTwoNumbers(l1, l2);
		while (ret)
		{
			cout << ret->val;
			ret = ret->next;
		}
		cout << endl;
	}
#pragma endregion
#pragma region 3.无重复字符的最长字串
	{
		int maxLength = solution.lengthOfLongestSubstring("abcacbb");
		cout << maxLength << endl;
	}
#pragma endregion
#pragma region 4.寻找两个正序数组的中位数
	{
		vector<int> nums1 = { 1,2,4 };
		vector<int> nums2 = { 2,5,6 };
		double med = solution.findMedianSortedArrays(nums1, nums2);
		cout << med << endl;
	}
#pragma endregion
#pragma region 5.最长回文字串
	{
		string palindrome = solution.longestPalindrome("bbcabacb");
		cout << palindrome << endl;
	}
#pragma endregion
#pragma region 6.Z字变换
	{
		string convertRet = solution.convert("PAYPALISHIRING", 3);
		cout << convertRet << endl;
	}
#pragma endregion
#pragma region 7.整数反转
	{
		int reverse1 = solution.reverse(123);
		int reverse2 = solution.reverse(INT32_MAX);
		cout << reverse1 << " " << reverse2 << endl;
	}
#pragma endregion
#pragma region 8.atoi
	{
		int atoi = solution.myAtoi("as-0123as");
		cout << atoi << endl;
	}
#pragma endregion
#pragma region 9.回文数
	{
		cout << solution.isPalindrome(12321) << endl;
	}
#pragma endregion
#pragma region 10.正则表达式匹配
	{
		cout << solution.isMatch("aab", "c*a*b") << endl;
	}
#pragma endregion
#pragma region 11.装水最多的容器
	{
		vector<int> height = { 1,8,6,2,5,4,8,3,7 };
		cout << solution.maxArea(height) << endl;
	}
#pragma endregion
#pragma region 12.整数转罗马数字
	{
		cout << solution.intToRoman(3999) << endl;
	}
#pragma endregion

	return 0;
}