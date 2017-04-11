#include <iostream>
#include <utility>
#include <string>
#include <bitset>

using namespace std;

int potenciacion(int b, int p){
	if (p == 0) return 1; else if (p == 1) return b;	
	int base = b;	
	for (int i = 1; i < p; i++)
		b *= base;
	return b;
}

string twosComplement(int a){
	string binary;
	int sz = sizeof(char) * 8, tam, size;
	size = sz-1;
	binary[0] = '1';
	for(int i = 1; i < sz; i++){
		tam = potenciacion(2, size-1);
		size--;
		if (a < tam) 
			binary += '0';
		else{
			binary += '1';
			a -= tam;
		}
	}
	binary += '\0';
	return binary;
}

int binToDec(string a, int s = 8){ //convertir de binario a decimal
	int total, size; //s = bits
	//tam = sizeof(char) * 8; //8 bits
	size = s - 1;
	if (a[0] == '1')
		total =  0 - potenciacion(2, size);
	size--;
	for(int i = 1; i < 8; i++){
		if (a[i] == '1')
			total += potenciacion(2, size);
		size--;
	}
	return total;
}

int booth(int m, int q){ //m = multiplicand, q = multiplier
	bitset<8> bitsA (0);
	bitset<8> bitsQ (0);
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	int result, q_0, bit, a, q_1 = 0;
	string binaryA, binaryQ;
	for ( ; count != 0; count--){
		q_0 = bitsQ[0]; //= bit en la pos 0 de q
		a = binToDec(bitsA.to_string());
		if (q_0 == 0 && q_1 == 1){ //01
			a += m;
		} else if (q_0 == 1 && q_1 == 0){ //10
			a -= m;
		}
		bitsA = bitset<8> (a);
		bitsA = bitsA >> 1; //shifting a to the right by 1
		bit = bitsQ[n-1]; //bit en la posicion n-1 (7) en q
		if (bit == 0) //q = 0xx...xx
			//a &= ~(1 << 0); //bit en la pos 0 de a = 0 (ultimo q)
			bitsA[0] = 0;
		else //q = 1x...xx
			//a |= (1 << 0); //bit en la pos 0 de a = 1 (ultimo q)
			bitsA[0] = 1;
		bitsQ = bitsQ >> 1; //shifting q to the right by 1
		bit = q_1; //bit a la derecha del LSB de q
		if (bit == 0) //q_1 = 0xx...xx
			bitsQ[0] = 0; //bit en la pos 0 de q = 0 (q_1)
		else
			bitsQ[0] = 1; //bit en la pos 0 de q = 1 (q_1) 
		q_1 = q_1 >> 1; //shifting q_1 to the right by 1
		count--;
	}
	binaryA = bitset<8>(a).to_string();
	binaryQ = bitset<8>(q).to_string();
	binaryA += binaryQ; //concatenating a and q
	result = binToDec(binaryA, 16);
	cout << "Resultado en bits: " << binaryA << endl;
	return result;
}

pair<int, int> division(int m, int q){ //m = divisor, q = dividend
	int a = 0;
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	short bit;
	bitset<8> bitsM (m);
	bitset<8> bitsQ (q);
	bitset<8> bitsA (a);
	for ( ; count != 0; count--){
		bitsA = bitsA << 1; //shifting a to the left by 1
		bit = bitsQ[n-1]; //bit en la posicion n-1 (7) en q
		if (bit == 0) //q = 0x...xx
			bitsA[0] = 0; //bit en la pos 0 de a = 0
		else //q = 1x...xx
			bitsA[0] = 1; //bit en la pos 0 de a = 1
		bitsQ = bitsQ << 1; //shifting q to the left by 1
		a = binToDec(bitsA.to_string()); //a a decimal
		m = binToDec(bitsM.to_string()); //m a decimal
		a -= m;
		bitsA = a; 
		if (a < 0){
			a += m;
			bitsQ[0] = 0; //q_0 = 0
			bitsA = a;
		} else
			bitsQ[0] = 1; //q_0 = 1
	}
	pair<int, int> results;
	q = binToDec(bitsQ.to_string());
	a = binToDec(bitsA.to_string());
	results.first = q;
	results.second = a;
	return results;
}

int main(){
	int q, m, multi, coc, res;
	pair<int, int> div;
	cout << "Ingrese el primer valor: ";
	cin >> m;
	cout << "Ingrese el segundo valor: ";
	cin >> q;
	multi = booth(m, q);
	cout << "Resultado de la multiplicacion: " << multi << endl;
	/*div = division(m, q);
	coc = div.first; res = div.second;
	cout << "Resultado de la division: " << coc << endl;
	cout << "Residuo: " << res << endl;*/
	return 0;
}
