#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> MakeVector(){
	vector<int> v;
	for (int i = 0; i < 32; i++)
		 v.push_back(1);
		 return v;
}

void makeArray(int *a){
	for (int i = 0; i < 32; i++)
		 *(a+i) = 1;
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
	int op;
	int fn;
	int rd;
	int rs;
	int rt;
	string inst;
	void interpretar(){
		cout << "Program counter: " << this->PC << endl;
		cout << "Instruccion: " << this->inst << endl;
		if (this->fn >= 32){
			cout << "Tipo: ALU\n";
			cout << "Ciclos de reloj: 4\n";
		}
		if (this->op < 32 && this-> op > 5){
			cout << "ALU inmediato\n";
			cout << "Ciclos de reloj: 4\n";
		}
		this->PC += 4;
		cout << "Program Counter (finished): " << this->PC << endl;
	}
public:
	CicloSimple(){
		;
	}
	void lui(int reg, int imm);
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
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU suma\n";
		res = this->rs + this->rt;
		regs.at(rd) = res;
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
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
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
		this->rs = regs.at(rs);
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
	}
	void AND(int rd, int rs, int rt){
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
		this->inst = "and";
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
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
		this->op = 0;
		this->fn = 37;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->LogicFn = 1; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "or";
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
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
		this->op = 0;
		this->fn = 38;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->LogicFn = 2; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "xor";
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
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
		this->op = 0;
		this->fn = 39;
		this->RegWrite = 1;
		this->RegDst = 1;
		this->RegInSrc = 1;
		this->ALUSrc = 0;
		this->LogicFn = 3; 
		this->FnClass = 3;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 0;
		this->PCSrc = 0;
		this->inst = "nor";
		this->rt = regs.at(rt);
		this->rs = regs.at(rs);
		int res = 0;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rt: " << this->rt << endl;
		cout << "Operacion ALU nor\n";
		res = ~(this->rs | this->rt);
		regs.at(rd) = res;
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
	///revisar esto
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
		this->inst = "j";
	}
	void jr(int rs){
		this->op = 0;
		this->fn = 16;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->PCSrc = 2;
		this->inst = "jr";
	}
	void bltz(int rs, string L){
		this->op = 1;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 3;
		this->PCSrc = 0;
		this->inst = "bltz";
	}
	void beq(int rs, int rt, string){
		this->op = 4;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 1;
		this->PCSrc = 0;
		this->inst = "beq";
	}
	void bne(int rs, int rt, string){
		this->op = 6;
		this->RegWrite = 0;
		this->DataRead = 0;
		this->DataWrite = 0;
		this->BrType = 2;
		this->PCSrc = 0;
		this->inst = "bne";
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
		this->inst = "jal";
	}
};

int CicloSimple::PC = 0;
vector<int> CicloSimple::regs = MakeVector();
/*int* CicloSimple::regs = 0;
makeArray(regs);*/

int main(int argc, char *argv[]) {
	//while (true){no quiero dejarlo comentado maricon 
	CicloSimple *MIPS = new CicloSimple;
	MIPS->add(3, 4, 5);
	//MIPS.sub(10, 5, 5);
	//MIPS.addi(3, 3, 5);
	//MIPS.AND(6, 3, 3);
	//MIPS.OR(7, 3, 6);
	//MIPS.XOR(10, 7, 6);
	MIPS->andi(4, 3, 10);
	MIPS->ori(7, 3, 6);
	MIPS->xori(7, 3, 4);
	//}
	delete MIPS;
	return 0;
}
