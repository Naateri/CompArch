#include <iostream>

using namespace std;

int booth(int m, int q){ //m = multiplicand, q = multiplier
	short a = 0, q_1 = 0, q_0;
	int n = sizeof(int) * 8; //bits a multiplicar
	int count = n;
	while (count != 0){
		q_0 = (q & (1 << 0)); // = bit en la pos 0 de q
		if (q_0 == 0 && q_1 == 1){
			a += m;
		}else if (q_0 == 1 && q_1 == 0){
			a -= m;
		}
			//} else {
		a = a >> 1; //shifting a to the right by 1
		q = q >> 1; //shifting q to the right by 1
		q_1 = q_1 >> 1; //shifting q_1 to the right by 1
		count--;
		//}
	}
	return q;
	
}

int division(int m, int q){ //m = divisor, q = dividend
	short a = 0;
	int n = sizeof(int) * 8; //bits a multiplicar
	int count = n;
	while (count != 0){
		a = a << 1; //shifting a to the left by 1
		q = q << 1; //shifting q to the left by 1 
		a -= m; //a = a - m
		//q_0 = (q & (1 << 0)) >> 0; //bit en la pos 0 de q (maskeo)
		if (a < 0){
			q |= (0 << 0); //q_0 = 0
			//q ^= (0 ^ q) & (1 << 0);
			a += m;
		} else {
			q |= (1 << 0); //q_0 = 1;
			//q ^= (-1 ^ q) & (1 << 0);
		}
		count--;
	}
	return q;
	
}

int main(){
	/*int a = 7;
	int n = 0, bit;
	while (n < sizeof(int) * 8){
		bit = (a & (1 << n)) >> n; //bit en la pos n de a 
		cout << bit;
		n++;
	}*/
	int q, m;
	cout << "Ingrese el primer valor: ";
	cin >> m;
	cout << "Ingrese el segundo valor: ";
	cin >> q;
	cout << "Resultado de la multiplicacion: " << booth(m, q) << endl;
	cout << "Resultado de la division: " << division(m, q) << endl;
	return 0;
}
