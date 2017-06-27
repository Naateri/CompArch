#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

int erres[3];

int busqui(string funci, string *punte){
	for(int i=0;i<23;i++){
		if(funci == *(punte+i)){
			return i;
		}
	}
	return -1;
}

vector<int> MakeVector(){
	vector<int> v;
	for (int i = 0; i < 32; i++)
		v.push_back(i+1);
	return v;
}

void makeArray(int *a){
	for (int i = 0; i < 32; i++)
		*(a+i) = 1;
}

string interpretaInstr(string lol){
	string instr, nums;
	int *ers = erres;
	for(int i = 0; i < lol.size(); i++){
		if(lol[i] != ' ' && lol[i] > '@'){
			instr += lol[i];
		} else if (lol[i] >= '0' && lol[i] <= '9'){
			nums += lol[i];
		}
		if (nums.size() >= 0 && lol[i] == ' '){
			stringstream ss(nums);
			ss >> *ers; 
			nums.clear();
			ers++;
		}
	}
	return instr;
}

class CicloSimple{
private:
	static int PC;
	//static int* regs;
	static vector<int> regs;
	bool ALUSrc;
	int ALUFunc;
	bool RegWrite;
	int RegDst;
	int RegInSrc;
	bool AddSub;
	int LogicFn;
	int FnClass;
	bool DataRead;
	bool DataWrite;
	int BrType;
	int PCSrc;
	bool jumpi; ///agregando porque si no tiene nada que ver con mips
	int op;
	int fn;
	int rd;
	int rs;
	int rt;
	string inst;
	void printALU(){
		cout<<endl;
		cout<<"  -------------------------------------------------------------------------------"  <<endl;
		cout<<" |                                _______                                        |" <<endl;
		cout<<" |                               |       \\                                       |"  <<endl;
		cout<<" |         _______               |        \\           Guardando en rd:"<<regs.at(this->rd)<<"          |"  <<endl;
		cout<<" |        |       |              |         \\             ____________            |"  <<endl;
		cout<<" |        |  Reg  |  ---->rs:"<<this->rs<<"   |          |           |            |           |"  <<endl;
		cout<<" | |      |       |              |   ALU    |   ----->  | Data Cache |----       |"  <<endl;
		cout<<" | |      |  File |  ---->rt:"<<this->rt<<"   |          |           |____________|    |      |"  <<endl;
		cout<<" | |  --> |_______|    |         |         /                              |      |"  <<endl;
		cout<<" | | |                 | imm     |        /                               |      |"  <<endl;
		cout<<" |  -+-----------------          |_______/                                |      |"  <<endl;
		cout<<" |   |                                                                    |      |"  <<endl;
		cout<<" |    --------------------------------------------------------------------       |"  <<endl;
		cout<<" |                                                                               |"  <<endl;
		cout<<" |                                                                               |"  <<endl;
		cout<<" |                 .........................................                     |"  <<endl;
		cout<<" |                 :                                       :                     |"  <<endl;
		cout<<" |                 :               CONTROL                 :                     |"  <<endl;
		cout<<" |                 :                                       :                     |"  <<endl;
		cout<<" |                 :.......................................:                     |"  <<endl;
		cout<<" |                                                                               |"  <<endl;
		cout<<" |                                                                               |"  <<endl;
		cout<<"  -------------------------------------------------------------------------------"  <<endl;
	}
	void interpretar(){
		cout<<"\n";
		cout << "Program counter: " << this->PC << endl;
		cout << "Instruccion: " << this->inst << endl;
		cout << "Leyendo la instruccion y guardandola en el registro de instrucciones,\nincrementando Program Counter + 4\n";
		cout << "Leyendo rs y rt en los registros x & y, calculando la direccion de la sucursal\ny guardando en EL registro z.\n";
		if (this->fn >= 32 && this->fn != 0){
			cout << "Tipo: ALU\n";
			cout << "Realizando operacion ALU y guardando el resultado en el registro z.\n";
			cout << "Escribir el registro z en rd (" << this->rd << ").\n";
			cout << "Ciclos de reloj: 4\n";
			printALU();
		}
		else if (this->op < 32 && this-> op > 5){
			cout << "ALU inmediato\n";
			cout << "Escribir el registro z en rd (" << this->rd << ").\n";
			cout << "Ciclos de reloj: 4\n";
		}
		else if(this->op == 35){
			cout << "Load operation.\n";
			cout << "Agregar valores base y offset, guardar en el registro z.\n";
			cout << "Leer memoria en los registros\n";
			cout << "Copiar el registro en rt(" << this->rt << ").\n";
			cout << "Ciclos de reloj: 5\n";
		} else if (this->op == 51){
			cout << "Load operation.\n";
			cout << "Agregar valores base y offset, guardar en el registro z.\n";
			cout << "Copiar el registro y en la memoria.\n";
			cout << "Ciclos de reloj: 4\n";
		} else if (this->jumpi){
			cout << "Jump operation.\n";
			cout << "Darle al PC la direccion destino\n";
			cout << "Ciclos de reloj: 3\n";
		}
		this->PC += 4;
		cout << "Program Counter (finished): " << this->PC << endl;
	}
	
	void aoxn(){
		this->op = 0;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->AddSub = 0;
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
	}
	
public:
	CicloSimple(){
		;
	}
	void li(int reg, int imm){
		this->inst = "li";
		this->rd = reg;
		int res;
		//interpretar();
		cout << "Reg file:\n";
		cout << "imm: " << imm << endl;
		cout << "Operacion load immediate\n";
		regs.at(rd) = res;
		cout << "Resultado guardado en " << this->rd << ": " << imm << endl;
		cout << "li operation\n";
		cout << "Cargando en " << this->rd << " el valor de " << imm << endl;
		cout << "Ciclos de reloj: 3\n";
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void add(int rd, int rs, int rt){
		this->fn = 32;
		this->op = 0;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->AddSub = 0;
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "add";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU suma\n";
		res = this->rs + this->rt;
		regs.at(this->rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void sub(int rd, int rs, int rt){
		this->op = 0;
		this->fn = 34;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->AddSub = 1;
		this->FnClass = 2;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "sub";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU resta\n";
		res = this->rs - this->rt;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void slt(int rd, int rs, int rt){
		this->op = 0;
		this->fn = 50;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->AddSub = 1;
		this->FnClass = 1;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "slt";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		bool res;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion Set Less Than\n";
		if(this->rs < this->rt) res = 1;
		else res = 0;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << (int)res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void addi(int rd, int rs, int imm){
		this->op = 16;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc =1 ;
		this->ALUSrc = 1;
		this->AddSub = 0;
		this->FnClass = 2;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "addi";
		//this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion ALU suma inmediata\n";
		res = this->rs + imm;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void slti(int rd, int rs, int imm){
		this->op = 18;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc = 1;
		this->ALUSrc = 1;
		this->AddSub = 1;
		this->FnClass = 1;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "slti";
		this->rt = regs.at(this->rt);
		//this->rd = rd;
		bool res;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion Set Less Than Immediate\n";
		if(this->rs < imm) res = 1;
		else res = 0;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << int(res) << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void AND(int rd, int rs, int rt){
		aoxn();
		this->fn = 36;
		this->LogicFn = 0;
		this->inst = "and";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU and\n";
		res = this->rs & this->rt;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void OR(int rd, int rs, int rt){
		aoxn();
		this->fn = 37;
		this->LogicFn = 1;
		this->inst = "or";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU or\n";
		res = this->rs | this->rt;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void XOR(int rd, int rs, int rt){
		aoxn();
		this->fn = 38;
		this->LogicFn = 2;
		this->inst = "xor";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU xor\n";
		res = this->rs ^ this->rt;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void NOR(int rd, int rs, int rt){
		aoxn();
		this->fn = 39;
		this->LogicFn = 3;
		this->PCSrc = 0;
		this->inst = "nor";
		this->rt = regs.at(this->rt);
		this->rs = regs.at(this->rs);
		//this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU nor\n";
		res = ~(this->rs | this->rt);
		regs.at(this->rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void andi(int rd, int rs, int imm){
		this->op = 24;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc = 1;
		this->ALUSrc = 1;
		this->LogicFn = 0; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->op = 0;
		this->fn = 36;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc =1 ;
		this->ALUSrc = 0;
		this->LogicFn = 0;
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "andi";
		this->rs = regs.at(rs);
		this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion ALU and inmediato\n";
		res = this->rs & imm;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void ori(int rd, int rs, int imm){
		this->op = 26;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc = 1;
		this->ALUSrc = 1;
		this->LogicFn = 1; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "ori";
		this->rs = regs.at(rs);
		this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion ALU or inmediato\n";
		res = this->rs | imm;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void xori(int rd, int rs, int imm){
		this->op = 28;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc = 1;
		this->ALUSrc = 1;
		this->LogicFn = 2; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "xori";
		this->rs = regs.at(rs);
		this->rd = rd;
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion ALU xor inmediato\n";
		res = this->rs ^ imm;
		regs.at(rd) = res;
		cout << "Resultado guardado en " << rd << ": " << res << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	
	void lw(int rt, int imm){
		this->op = 35;
		this->RegWrite = 1;
		this->RegDst = 0;
		this->RegInSrc = 0;
		this->ALUSrc = 1;
		this->AddSub = 0;
		this->FnClass = 2;
		this->DataRead = 1;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->fn = 0;
		this->inst = "lw";
		interpretar();
		cout << "Reg file:\n";
		cout << "rt: " << this->rt << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion Acceso a Memoria lw \n";
		regs.at(rt) = imm;
		cout << "Copiando en " << rt << ": " << imm << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void sw(int rt, int imm){
		this->op = 51;
		this->RegWrite = 0;
		this->ALUSrc = 1;
		this->AddSub = 0;
		this->FnClass = 2;
		this->DataRead = 0;
		this->DataWrite = 1;
		this->BrType = 0;
		this->PCSrc = 0;
		this->fn = 0;
		this->inst = "sw";
		interpretar();
		cout << "Reg file:\n";
		cout << "rt: " << this->rt << endl;
		cout << "imm: " << imm << endl;
		cout << "Operacion Acceso a Memoria sw \n";
		regs.at(rt) = imm;
		cout << "Copiando en " << rt << ": " << imm << endl;
		cout << "Guardando resultados.\n";
		cout << endl;
	}
	void j(string L){
		this->op = 2;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->PCSrc = 1;
		this->fn = 0;
		this->jumpi = 1;
		this->inst = "j";
		interpretar();
		cout << "Operacion Jump\n";
		cout << "Saltando a " << L << endl;
	}
	void jr(int rs){
		this->op = 0;
		this->fn = 16;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->PCSrc = 2;
		this->jumpi = 1;
		this->inst = "jr";
		interpretar();
	}
	void bltz(int rs, string L){
		this->op = 1;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 3;
		this->PCSrc = 0;
		this->jumpi = 1;
		this->inst = "bltz";
		interpretar();
		cout << "Operacion Less Than zero\n";
		if (rs < 0) cout << "Saltando a " << L << endl;
		else cout << "No pasa nada.\n";
	}
	void beq(int rs, int rt, string L){
		this->op = 4;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 1;
		this->PCSrc = 0;
		this->jumpi = 1;
		this->fn = 0;
		this->inst = "beq";
		interpretar();
		cout << "Operacion Equal than\n";
		if (this->rs == this->rt) cout << "Saltando a " << L << endl;
		else cout << "No pasa nada.\n";
	}
	void bne(int rs, int rt, string L){
		this->op = 6;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 2;
		this->PCSrc = 0;
		this->jumpi = 1;
		this->fn = 0;
		this->inst = "bne";
		interpretar();
		cout << "Operacion Not Equal than\n";
		if (this->rs != this->rt) cout << "Saltando a " << L << endl;
		else cout << "No pasa nada.\n";
	}
	void jal(string L){
		this->op = 6;
		this->RegWrite = 0;
		this->RegDst = 2;
		this->RegInSrc = 2;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 3;
		this->jumpi = 1;
		this->fn = 0;
		this->inst = "jal";
		interpretar();
	}
	void syscall(){;}
	
	void call(){
		string arreglito[] = {"add","sub","slt","and","or","nor","xor","li","addi","slti","andi","ori","xori","sw","lw","bltz","beq","bne","j","jr","jal","syscall","close"};
		string funcion;
		int funqui;
		getline(cin, funcion);
		funcion = interpretaInstr(funcion);
		funqui = busqui(funcion,arreglito);
		this->rd = erres[0];
		//cout << this->rd << endl;
		this->rs = erres[1];
		this->rt = erres[2];
		switch(funqui){
		case 0:
			this->add(1, 2, 3);
			break;
		case 1:
			this->sub(1, 2, 3);
			break;
		case 2:
			this->slt(1, 2, 3);
			break;
		case 3:
			this->AND(1, 2, 3);
			break;
		case 4:
			this->OR(1, 2, 3);
			break;
		case 5:
			this->NOR(1, 2, 3);
			break;
		case 6:
			this->XOR(1, 2, 3);
			break;
		case 7:
			this->li(1,2); 
			break;
		case 8:
			this->addi(1, 2, 3);
			break;
		case 9:
			this->slti(1, 2, 3);
			break;
		case 10:
			this->andi(1, 2, 3);	
			break;
		case 11:
			this->ori(1, 2, 3);
			break;
		case 12:
			this->xori(1, 2, 3);
			break;
		case 13:
			this->sw(1, 2);
			break;
		case 14:
			this->lw(1,2);
			break;
		case 15:
			this->bltz(1,"loop");
			break;
		case 16:
			this->beq(1, 2, "loop");
			break;
		case 17:
			this->bne(1, 2, "loop");
			break;
		case 18:
			this->j("loop");
			break;
		case 19:
			this->jr(73);
			break;
		case 20:
			this->jal("loop");
			break;
		case 21:
			this->syscall();
			break;
		case 22:
			cout << "Hasta luego!";
			exit(69);
			break;
		default:
			cout<<"No se encontro la funcion"<<endl;
			break;
		}
	}
};

int CicloSimple::PC = 0;
vector<int> CicloSimple::regs = MakeVector();
/*int* CicloSimple::regs = 0;
makeArray(regs);*/

int main(int argc, char *argv[]) {
	//while (true){
	CicloSimple *MIPS = new CicloSimple;
	while(1){
		MIPS->call();
	}
	/*MIPS->add(3, 4, 5);
	//MIPS.sub(10, 5, 5);
	//MIPS.addi(3, 3, 5);
	//MIPS.AND(6, 3, 3);
	//MIPS.OR(7, 3, 6);
	//MIPS.XOR(10, 7, 6);
	MIPS->andi(4, 3, 10);
	MIPS->ori(7, 3, 6);
	MIPS->xori(7, 3, 4);*/
	//}
	delete MIPS;
	return 0;
}
