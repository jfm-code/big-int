//BigInt.cpp
#include <iostream>
#include "bigInt.h"

using namespace std;
bool flag;

int main()
{
	cout << "Big Int part 3 testing:" << endl;
	BigInt a("123456789");
	BigInt b("-54321");
	cout << a << " / " << b << " = " << a / b << endl;
	a = BigInt("654321");
	b = BigInt("54321");
	cout << a << " / " << b << " = " << a / b << endl;
	a = BigInt("-158");
	b = BigInt("-2");
	cout << a << " / " << b << " = " << a / b << endl;
	a = BigInt("-158");
	b = BigInt("10");
	cout << a << " / " << b << " = " << a / b << endl;

	a = BigInt("-158");
	b = BigInt("2");
	cout << a << " % " << b << " = " << a % b << endl;
	a = BigInt("4321");
	b = BigInt("21");
	cout << a << " % " << b << " = " << a % b << endl;
	a = BigInt("654321");
	b = BigInt("54321");
	cout << a << " % " << b << " = " << a % b << endl;

	return 0;
}

BigInt::BigInt()
{
	data = "0";
	isNegative = false;
}

BigInt::BigInt(int x)
{
	if (x < 0)
		isNegative = true;
	else
		isNegative = false;
	string s = to_string(x);
	data = s;
	
}

BigInt::BigInt(string x)
{
	if (!(isValidString(x, isNegative)))
	{
		cout << "String: " << x << "is not valid." << endl;
		flag = false;
	}
	else
	{
		data = x;
		flag = true;
	}
}

ostream& operator<<(ostream& out, const BigInt& right)
{
	if (flag == true)
		//return out << right.data << " is negative(1) or not(0):" << right.isNegative << endl;
		return out << right.data;
	else 
		return out;
}

bool BigInt::isValidString(string s, bool& checkNegative)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 48 && s[i] <= 57)
		{
			checkNegative = false;
			return true;
		}
		else if ((s[i] == '+') || (s[i] == '-'))
		{
			if (s[i] == '+')
				checkNegative = false;
			else if (s[i] == '-')
				checkNegative = true;
			if (s[i + 1] >= 48 && s[i + 1] <= 57) //if next character is a digit (48 and 57 are values in ASCII)
				return true;
			else 
				return false;
		}
		else;
	}
	return false;
}

BigInt operator+(BigInt left, BigInt right)
{
	BigInt res;
	//addition when both positive or both negative
	if ((!(left.isNegative) && !(right.isNegative)) || (left.isNegative && right.isNegative))
		res.data = addition(left.data, right.data);
	//substraction when one of them is negative 
	else
		res.data = substraction(left.data, right.data);
	return res;
}

BigInt operator-(BigInt left, BigInt right)
{
	BigInt res;
	//substraction when both positive or both negative
	if ((!(left.isNegative) && !(right.isNegative)) || (left.isNegative && right.isNegative))
		res.data = substraction(left.data, right.data);
	//addition when one of them is positive 
	else
	{
		if(right.isNegative)
			right.data[0] = '+';
		res.data = addition(left.data, right.data);
	}

	return res;
}

BigInt operator*(BigInt left, BigInt right)
{
	BigInt res; 
	//check if both is positive or both negative to determine the sign later
	bool same_sign = false;
	if ((!left.isNegative && !right.isNegative)  ||  (left.isNegative && right.isNegative))
		same_sign = true;


	//reverse the strings to not mess up with the index
	left.data = reverse(left.data);
	right.data = reverse(right.data);

	string result;
	vector<int>total_vector;

	//delete the sign character if have one 
	if (!isdigit(left.data[left.data.size()-1]))
		left.data.pop_back();
	if (!isdigit(right.data[right.data.size()-1]))
		right.data.pop_back();

	//use 2 for loops to iterate through the strings
	for (int i = 0; i < left.data.size(); i++)
	{
		int total_digit = 0;
		int carry = 0;
		int carry_vector = 0;
		int i_vector = i;
		for (int y = 0; y < right.data.size(); y++)
		{
			total_digit = (left.data[i] - '0') * (right.data[y] - '0') + carry;
			carry = total_digit / 10;
			if(i == 0 || i_vector>total_vector.size()-1)
				total_vector.push_back(total_digit % 10);
			else
			{
				total_vector[i_vector] += (total_digit % 10);
				if (total_vector[i_vector] >= 10)
				{
					carry_vector = total_vector[i_vector] / 10;
					total_vector[i_vector] %= 10;
					carry += carry_vector;
				}
				i_vector++;
			}
		}
		if (carry != 0)
			total_vector.push_back(carry);
	}

	//convert from int vector to string and return
	for (int a = 0; a < total_vector.size(); a++)
		result.push_back(total_vector[a] + '0');
	if (!same_sign)
		result.push_back('-');
	res.data = reverse(result);
	return res;
}

BigInt operator/(BigInt left, BigInt right)
{
	BigInt res;
	int dividend = 0;
	int divisor = 0;
	int quotient = 0;
	int remainder = 0;
	vector<int>result;

	//check if both is positive or both negative to determine the sign later
	bool same_sign = false;
	if ((!left.isNegative && !right.isNegative) || (left.isNegative && right.isNegative))
		same_sign = true;

	//reverse the strings to delete the sign character if have one 
	left.data = reverse(left.data);
	right.data = reverse(right.data);
	if (!isdigit(left.data[left.data.size() - 1]))
		left.data.pop_back();
	if (!isdigit(right.data[right.data.size() - 1]))
		right.data.pop_back();

	//reverse back
	left.data = reverse(left.data);
	right.data = reverse(right.data);
	
	//start dividing
	if (right.data == "0")
		res.data = "Cannot divide by zero";
	else
	{
		//special cases
		if (left.data == right.data)
			res.data = "1";
		else if ((left.data != right.data) && (right.data == "1"))
			res.data = left.data;
		else if (left.data == "0" || ((left.data != right.data) && (left.data == "1")))
			res.data = "0";

		//normal cases
		int i_right = 0;
		int i_left = 0;
		int i_pow = 0;
		while (i_right < right.data.size())
		{
			divisor = (divisor * pow(10, i_pow)) + (right.data[i_right]-'0');
			dividend = (dividend * pow(10, i_pow)) + (left.data[i_right]-'0');
			i_pow = 1;
			if (dividend < divisor && (left.data.size() > right.data.size()) && (i_right == right.data.size()-1))
			{
				i_left = i_right + 1;
				dividend = (dividend * pow(10, i_pow)) + (left.data[i_left] - '0');
			}
			else
				i_left = i_right;
			i_right++;
		}
		quotient = dividend / divisor;
		result.push_back(quotient);
		remainder = dividend - (quotient * divisor);
		while (i_left < left.data.size() - 1)
		{
			i_left++;
			dividend = (remainder * 10) + (left.data[i_left]-'0');
			quotient = dividend / divisor;
			result.push_back(quotient);
			remainder = dividend - (quotient * divisor);
		}
	}
	//convert from int vector to string and return
	for (int y = 0; y < result.size(); y++)
	{
		char c = result[y] + '0';
		res.data.push_back(c);
	}
	res.data = reverse(res.data);
	res.data.pop_back();
	if(!same_sign && res.data != "0")
		res.data.push_back('-');
	res.data = reverse(res.data);
	return res;
}

BigInt operator%(BigInt left, BigInt right)
{
	BigInt res;
	int dividend = 0;
	int divisor = 0;
	int quotient = 0;
	int remainder = 0;
	vector<int>result;
	vector<int>v_remainder;
	//check if both is positive or both negative to determine the sign later
	bool same_sign = false;
	if ((!left.isNegative && !right.isNegative) || (left.isNegative && right.isNegative))
		same_sign = true;

	//reverse the strings to delete the sign character if have one 
	left.data = reverse(left.data);
	right.data = reverse(right.data);
	if (!isdigit(left.data[left.data.size() - 1]))
		left.data.pop_back();
	if (!isdigit(right.data[right.data.size() - 1]))
		right.data.pop_back();

	//reverse back
	left.data = reverse(left.data);
	right.data = reverse(right.data);

	//start dividing
	if (right.data == "0")
		res.data = "Cannot divide by zero";
	else
	{
		//special cases
		if (left.data == right.data)
			res.data = "1";
		else if ((left.data != right.data) && (right.data == "1"))
			res.data = left.data;
		else if (left.data == "0" || ((left.data != right.data) && (left.data == "1")))
			res.data = "0";

		//normal cases
		int i_right = 0;
		int i_left = 0;
		int i_pow = 0;
		while (i_right < right.data.size())
		{
			divisor = (divisor * pow(10, i_pow)) + (right.data[i_right] - '0');
			dividend = (dividend * pow(10, i_pow)) + (left.data[i_right] - '0');
			i_pow = 1;
			if (dividend < divisor && (left.data.size() > right.data.size()) && (i_right == right.data.size() - 1))
			{
				i_left = i_right + 1;
				dividend = (dividend * pow(10, i_pow)) + (left.data[i_left] - '0');
			}
			else
				i_left = i_right;
			i_right++;
		}
		quotient = dividend / divisor;
		result.push_back(quotient);
		remainder = dividend - (quotient * divisor);
		while (i_left < left.data.size() - 1)
		{
			i_left++;
			dividend = (remainder * 10) + (left.data[i_left] - '0');
			quotient = dividend / divisor;
			result.push_back(quotient);
			remainder = dividend - (quotient * divisor);
		}
	}
	
	//just return the remainder, not the quotient
	res.data.pop_back();
	if (remainder > 10) //if remainder has more than 1 character 
	{
		while (remainder != 0)
		{
			res.data.push_back(remainder % 10 + '0');
			remainder /= 10;
		}
		res.data = reverse(res.data);
	}
	else //if remainder has only 1 character
		res.data.push_back(remainder % 10 + '0');
	return res;
}

bool operator<(BigInt left, BigInt right)
{
	bool both_positive = false;
	if (!(left.isNegative) && right.isNegative)
		return false;
	else if (left.isNegative && !(right.isNegative))
		return true;
	else if ((!(left.isNegative) && !(right.isNegative)) || (left.isNegative && right.isNegative))
	{
		//remove the sign character
		if (!isdigit(left.data[0]))
			left.data.pop_back();
		if (!isdigit(right.data[0]))
			right.data.pop_back();

		//mark if both numbers are positive or not
		if (!(left.isNegative))
			both_positive = true;

		//reverse the strings and delete leading zeros
		left.data = reverse(left.data);
		right.data = reverse(right.data);
		int i = left.data.size() - 1;
		while(left.data[i] == '0')
		{
			left.data.pop_back();
			i--;
		}
		int y = right.data.size() - 1;
		while(right.data[y] == '0')
		{
			right.data.pop_back();
			y--;
		}
		//compare size
		if (left.data.size() < right.data.size())
		{
			if (both_positive)
				return true;
			else
				return false;
		}
		else if (left.data.size() > right.data.size())
		{
			if (both_positive)
				return false;
			else
				return true;
		}
		else
		{
			for (int i = left.data.size() - 1; i >= 0; i--)
			{
				if ((left.data[i] - '0') < (right.data[i] - '0'))
				{
					if (both_positive)
						return true;
					else
						return false;
				}
				else if ((left.data[i] - '0') > (right.data[i] - '0'))
				{
					if (both_positive)
						return false;
					else
						return true;
				}
				else;
			}
		}
	}
}

bool operator>(BigInt left, BigInt right)
{
	//bool both_positive = false;
	//if (!(left.isNegative) && right.isNegative)
	//	return true;
	//else if (left.isNegative && !(right.isNegative))
	//	return false;
	//else if ((!(left.isNegative) && !(right.isNegative)) || (left.isNegative && right.isNegative))
	//{
	//	//remove the sign character
	//	if (!isdigit(left.data[0]))
	//		left.data.pop_back();
	//	if (!isdigit(right.data[0]))
	//		right.data.pop_back();

	//	//mark if both numbers are positive or not
	//	if (!(left.isNegative))
	//		both_positive = true;

	//	//reverse the strings and delete leading zeros
	//	left.data = reverse(left.data);
	//	right.data = reverse(right.data);
	//	int i = left.data.size() - 1;
	//	while (left.data[i] == '0')
	//	{
	//		left.data.pop_back();
	//		i--;
	//	}
	//	int y = right.data.size() - 1;
	//	while (right.data[y] == '0')
	//	{
	//		right.data.pop_back();
	//		y--;
	//	}
	//	//compare size
	//	if (left.data.size() < right.data.size())
	//	{
	//		if (both_positive)
	//			return false;
	//		else
	//			return true;
	//	}
	//	else if (left.data.size() > right.data.size())
	//	{
	//		if (both_positive)
	//			return true;
	//		else
	//			return false;
	//	}
	//	else
	//	{
	//		for (int i = left.data.size() - 1; i >= 0; i--)
	//		{
	//			if ((left.data[i] - '0') < (right.data[i] - '0'))
	//			{
	//				if (both_positive)
	//					return false;
	//				else
	//					return true;
	//			}
	//			else if ((left.data[i] - '0') > (right.data[i] - '0'))
	//			{
	//				if (both_positive)
	//					return true;
	//				else
	//					return false;
	//			}
	//			else;
	//		}
	//	}
	//}

	return !(left < right);
}

bool operator==(BigInt left, BigInt right)
{
	return left.data.compare(right.data);
}

string reverse(string s)
{
	char temp = 'a';
	for (int i = 0; i < s.length()/2; i++)
	{
		temp = s[i];
		s[i] = s[s.length() - 1 - i];
		s[s.length() - 1 - i] = temp;
	}
	return s;
}

string addition(string left, string right)
{
	bool left_is_negative = false;
	string result;

	//reverse to calculate easier
	left = reverse(left);
	right = reverse(right);

	//always put left string as longer string 
	if (left.length() < right.length())
		left.swap(right);

	//remove the sign character
	if (!isdigit(left[left.length() - 1]))
	{
		if (left[left.length() - 1] == '-')
			left_is_negative = true;
		left.pop_back();
	}
	if (!isdigit(right[right.length() - 1]))
		right.pop_back();

	//calculate each digit and add them to sum_total
	vector<int>sum_total;
	int sum_digit = 0;
	int carry = 0;
	for (int i = 0; i < left.length(); i++)
	{
		if (i < right.length())
		{
			sum_digit += (left[i] - '0') + (right[i] - '0') + carry;
		}
		else
		{
			sum_digit += left[i] - '0' + carry;
		}
		sum_total.push_back(sum_digit % 10);
		carry = sum_digit/10;
		sum_digit = 0;
	}

	for (int i = 0; i < sum_total.size(); i++)
	{
		result.push_back(sum_total[i] + '0');
	}
	if (left_is_negative == true)
		result.push_back('-');
	if (carry != 0)
		result.push_back(carry + '0');

	return reverse(result);
}

string substraction(string left, string right)
{
	bool left_is_negative = false;
	string result;

	//reverse to calculate easier
	left = reverse(left);
	right = reverse(right);

	//always put left string as longer string 
	if (left.length() < right.length())
		left.swap(right);

	//remove the sign character
	if (!isdigit(left[left.length() - 1]))
	{
		if (left[left.length() - 1] == '-')
			left_is_negative = true;
		left.pop_back();
	}
	if (!isdigit(right[right.length() - 1]))
		right.pop_back();

	//calculate each digit and add them to sum_total
	vector<int>sum_total;
	int sum_digit = 0;
	int carry = 0;
	int borrow = 0;
	for (int i = 0; i < left.length(); i++)
	{
		if (i < right.length())
		{
			if (left[i] == '0')
			{
				sum_digit += 10 - (right[i] - '0') - borrow + carry;
				borrow = 1;
			}
			else
			{
				sum_digit += (left[i] - '0') - (right[i] - '0') - borrow + carry;
				borrow = 0;
			}
		}
		else
		{
			sum_digit += (left[i] - '0') - borrow + carry;
		}
		sum_total.push_back(sum_digit % 10);
		carry = sum_digit / 10;
		sum_digit = 0;
	}

	int y = sum_total.size()-1;
	while (sum_total[y] == 0)
	{
		sum_total.pop_back();
		y--;
	}
		
	for (int i = 0; i < sum_total.size(); i++)
	{
		
		result.push_back(sum_total[i] + '0');
	}
	if (left_is_negative == true)
		result.push_back('-');
	if (carry != 0)
		result.push_back(carry + '0');

	return reverse(result);
}
