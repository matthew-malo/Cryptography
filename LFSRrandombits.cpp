#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main(int argc, char* argv[])
{

	auto startTime = chrono::system_clock::now();

	//needed to use unsigned longs for the LFSRs due to the size of the numbers
	//I used them as integers first but let the compiler handle the bitwise operations
	unsigned long lfsr1 = 13253206;
	unsigned long lfsr2 = 26580141;
	unsigned long lfsr3 = 53209435;

	//placeholder for the initial fill of LFSR1
	unsigned long initialFill = lfsr1;


	int count0 = 0;
	int count1 = 0;
	ofstream out;
	out.open("stream.txt");

	//k is just a placeholder to space out the bitsream output
	int k = 0;

	//output is generated from the least significant bits of the LFSRs for Galios LFSRs
	//I used the bitwise and operator to obtain the value of the LSB
	int lsb1 = lfsr1 & 1;
	int lsb2 = lfsr2 & 1;
	int lsb3 = lfsr3 & 1;

	//shifts both LFSRs
	lfsr1 >>= 1;
	lfsr2 >>= 1;
	lfsr3 >>= 1;
	
	int y = 0;

	//invert the bits at tap locations
	if (lsb1 == 1) {
		lfsr1 ^= 0xE10000;
		y += 1;
	}
	if (lsb2 == 1) {
		lfsr2 ^= 0x1200000;
		y += 1;
	}
	if (lsb3 == 1) {
		lfsr3 ^= 0x204F5F6;
		y += 1;
	}

	//Test for minority vote system, outputs minority bit
	if (y >= 2) {
		out << 0;
		count0 += 1;
	}
	else {
		out << 1;
		count1 += 1;
	}

	//Increments counter for digit spacing in printout, resets value of y
	k += 1;
	y = 0;
	
	//while loop to produce bits until LFSR1 arrives back at its initial fill, with 
	//the operations in the while loop repeating the process above until completion
	while (lfsr1 != initialFill) {
		lsb1 = lfsr1 & 1;
		lsb2 = lfsr2 & 1;
		lsb3 = lfsr3 & 1;

		//shifts both LFSRs
		lfsr1 >>= 1;
		lfsr2 >>= 1;
		lfsr3 >>= 1;

		//invert the bits at tap locations and increment y if output is 1
		if (lsb1 == 1) {
			lfsr1 ^= 0xE10000;
			y += 1;
		}
		if (lsb2 == 1) {
			lfsr2 ^= 0x1200000;
			y += 1;
		}
		if (lsb3 == 1) {
			lfsr3 ^= 0x204F5F6;
			y += 1;
		}

		//Voting test to determine output bit
		if (y >= 2) {
			out << 0;
			count0 += 1;
		}
		else {
			out << 1;
			count1 += 1;
		}


		//incrementer to space out the output file for better readability
		k += 1;
		if (k % 500 == 0)
			out << endl;

		//reset y value
		y = 0;
	} 

	out << endl << "1s: " << count1 << " 0s: " << count0 << endl;
	
	auto endTime = chrono::system_clock::now();
	chrono::duration<double> elapsedTime = endTime - startTime;
	out << "Time taken: " << elapsedTime.count() << " seconds" << '\n';

	out.close();

	return 0;
}