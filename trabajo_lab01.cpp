#include <iostream>
#include <utility>
#include <string>

using namespace std;

int potenciacion(int b, int p){
	if (p == 0) return 1; else if (p == 1) return b;	
	int base = b;	
	for (int i = 1; i < p; i++)
		b *= base;
	return b;
}

string decToBin(int a){
	int sz = sizeof(char) * 8, tam, size;
	string binary;
	size = sz;
	for(int i = 0; i < sz; i++){
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
		
int booth(int m, int q){ //m = multiplicand, q = multiplier
	short a = 0, q_1 = 0, q_0;
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	while (count != 0){
		q_0 = (q & (1 << 0)); // = bit en la pos 0 de q
		if (q_0 == 0 && q_1 == 1){
			a += m;
		}else if (q_0 == 1 && q_1 == 0){
			a -= m;
		}
		a = a >> 1; //shifting a to the right by 1
		q = q >> 1; //shifting q to the right by 1
		q_1 = q_1 >> 1; //shifting q_1 to the right by 1
		count--;
	}
	return q;
	
}

pair<int, int> division(int m, int q){ //m = divisor, q = dividend
	int a = 0;
	int n = sizeof(char) * 8; //bits a multiplicar (8)
	int count = n;
	short bit;
	//while (count != 0){
	for (count; count != 0; count--){
		cout << "n: " << count << endl;
		cout << "q: " << decToBin(q) << endl;
		cout << "a: " << decToBin(a) << endl;
		a = a << 1; //shifting a to the left by 1
		q = q << 1; //shifting q to the left by 1
		bit = (q >> n) & 1;
		if (bit == 0) //q = 0x...xx
			a &= ~(1 << 0);
		else //q = 1x...xx
			a |= (1 << 0);
		cout << "a shifted: " << decToBin(a) << endl;
		cout << "q shifted: " << decToBin(q) << endl; 
		a -= m; //a = a - m
		cout << "a: " << a << endl;
		//q_0 = (q & (1 << 0)) >> 0; //bit en la pos 0 de q (maskeo)
		if (a < 0){
			q &= ~(1 << 0); //q_0 = 0
			a += m;
		} else {
			q |= (1 << 0); //q_0 = 1
			//a += m;
		}
		cout << "new q: " << decToBin(q) << endl;
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
	div = division(m, q);
	//cout << "Resultado de la multiplicacion: " << booth(m, q) << endl;
	coc = div.first; res = div.second;
	cout << "Resultado de la division: " << coc << endl;
	cout << "Residuo: " << res << endl;
	return 0;
}
