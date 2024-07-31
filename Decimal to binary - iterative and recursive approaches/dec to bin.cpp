#include <iostream>
#include <string>
#include <vector>

using std::cout; 
using std::cin; 
using std::endl; 
using std::string;

/*for readability/groups of 4 binary digits*/
void addPaddingZeros(std::vector<int>& binaryDigits)
{
	while (binaryDigits.size() % 4 != 0)
	{
		binaryDigits.push_back(0);
	}
}

std::vector<int> convertDecToBin_iteratively(int decimalNumber)
{

	std::vector<int> binaryDigits; 
	while (decimalNumber > 0)
	{
		binaryDigits.push_back(decimalNumber % 2);

		decimalNumber = decimalNumber / 2; 
	}
	//for 4 digit grouping/readability: 
	addPaddingZeros(binaryDigits);

	std::reverse(binaryDigits.begin(), binaryDigits.end());
	
	return binaryDigits;
}


void convertDecToBin_recursively(int decimalNumber)
{

	//base case: 
	if (decimalNumber == 0)
	{
		cout << "Done";
	}

	//recursive case: 
	else
	{
		//0010 1010

		convertDecToBin_recursively(decimalNumber / 2); //reduce to a "smaller problem" (number)

		cout << decimalNumber % 2;

	}
}

/*prints with space every 4 digits for readability - also prints original decimal number*/
void printBinaryDigits(std::vector<int> binaryDigits, int decimalNumber)
{
	cout << "The decimal number " << decimalNumber << " in binary is: \n";

	for (int i = 0; i < binaryDigits.size(); i++)
	{
		if (i > 0 && i % 4 == 0)
		{
			cout << " ";
		}
		cout << binaryDigits[i]; 
	}
	cout << "\n";
}

int convertBinToDec(std::vector<int> binaryDigits)
{
	std::reverse(binaryDigits.begin(), binaryDigits.end()); 

	int decimalEquivalent = 0; 

	for (int i = 0; i < binaryDigits.size(); i++)
	{
		//cout << "2^ i = " << pow(2, i) << "\t";
		decimalEquivalent += binaryDigits[i] * pow(2, i); 
		//cout << "dec equiv. so far ..." << decimalEquivalent << "\n";
	}

	return decimalEquivalent; 
}

int main()
{
	int decimalNumber = 42;
	//0010 1010
	//auto binaryEquivalent = convertDecToBin_iteratively(decimalNumber); 

	convertDecToBin_recursively(decimalNumber);

	//printBinaryDigits(binaryEquivalent, decimalNumber); 

	//auto decEquivalent = convertBinToDec(binaryEquivalent); 
	
	//cout << "Converted back to dec: " << decEquivalent << "\n";

	return 0; 
}