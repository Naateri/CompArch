//sin bitset (no compila)
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

string decToBin(int a){
	int sz = sizeof(char) * 8, tam, size;
	string binary;
	size = sz-1;
	binary[0] = '0';
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

string decToBinComplete(int a){
	if (a < 0){
		a = ~a + 1;
		return twosComplement(a);
	} else 
		return decToBin(a);
}

int booth(int m, int q){ //m = multiplicand, q = multiplier
	short a = 0, q_1 = 0, q_0, bit;
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	unsigned long result;
	string binaryA, binaryQ;
	while (count != 0){
		cout << "a: " << decToBinComplete(a) << endl;
		q_0 = (q & (1 << 0)); //= bit en la pos 0 de q
		cout << "q0: " << decToBinComplete(q_0) << endl;
		cout << "q-1: " << decToBinComplete(q_1) << endl;
		if (q_0 == 0 && q_1 == 1){
			a += m;
		} else if (q_0 == 1 && q_1 == 0){
			a -= m;
		}
		a = a >> 1; //shifting a to the right by 1
		bit = (q >> (n-1)) & 1; //bit en la posicion n-1 (7) en q
		if (bit == 0) //a = 0xx...xx
			a &= ~(1 << 0); //bit en la pos 0 de a = 0 (ultimo q)
		else //a = 1x...xx
			a |= (1 << 0); //bit en la pos 0 de a = 1 (ultimo q)
		q = q >> 1; //shifting q to the right by 1
		bit = (q_1 >> (n-1)) & 1; //bit en la posicion n-1 (7) en q
		if (bit == 0) //q_1 = 0xx...xx
			q &= ~(1 << 0); //bit en la pos 0 de q = 0 (q_1)
		else
			q |= (1 << 0); //bit en la pos 0 de q = 1 (q_1) 
		q_1 = q_1 >> 1; //shifting q_1 to the right by 1
		count--;
	}
	binaryA = bitset<8>(a).to_string();
	binaryQ = bitset<8>(q).to_string();
	binaryA += binaryQ; //concatenating a and q
	result = bitset<16>(binaryA).to_ulong();
	return result;
}

pair<int, int> division(int m, int q){ //m = divisor, q = dividend
	int a = 0;
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	short bit;
	//while (count != 0){
	for ( ; count != 0; count--){
		cout << "n: " << count << endl;
		cout << "q: " << decToBinComplete(q) << endl;
		cout << "a: " << decToBinComplete(a) << endl;
		a = a << 1; //shifting a to the left by 1
		bit = (q >> (n-1)) & 1; //bit en la posicion n-1 (7) en q
		if (bit == 0) //q = 0x...xx
			a &= ~(1 << 0); //bit en la pos 0 de a = 0
		else //q = 1x...xx
			a |= (1 << 0); //bit en la pos 0 de a = 1
		q = q << 1; //shifting q to the left by 1
		cout << "a shifted: " << decToBinComplete(a) << endl;
		cout << "q shifted: " << decToBinComplete(q) << endl; 
		a -= m; //a = a - m
		cout << "a: " << a << endl;
		//q_0 = (q & (1 << 0)) >> 0; //bit en la pos 0 de q (maskeo)
		if (a < 0){
			a += m;
			q &= ~(1 << 0); //q_0 = 0
		} else
			q |= (1 << 0); //q_0 = 1
			//a += m;
		cout << "new q: " << decToBinComplete(q) << endl;
		//count--;
	}
	pair<int, int> results;
	results.first = q;
	results.second = a;
	return results;
	
}

int main(){
	/*int a = 7;
	int n = 0, bit;
	while (n < sizeof(int) * 8){
	bit = (a & (1 << n)) >> n; //bit en la pos n de a 
	cout << bit;
	n++;
}*/
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
