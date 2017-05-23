#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> MakeVector(){
	vector<int> v;
	for (int i = 0; i < 32; i++)
		 v.push_back(1);
}

class CicloSimple{
private:
	static int PC;
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
		}
		if (this->op < 32 && this-> op > 5){
			cout << "ALU inmediato\n";
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
		this->rd = regs.at(rd);
		//this->rt = regs.at(rt);
		this->rs = regs.at(rs);
		int res;
		interpretar();
		cout << "Reg file:\n";
		cout << "rs: " << this->rs << endl;
		cout << "rd: " << this->rd << endl;
		cout << "Operacion ALU suma\n";
		res = rs + rd;
		regs.at(rt) = res;
		cout << "Resultado guardado en " << rt << ": " << res << endl;
		cout << "Guardando resultados.\n";
	}
	void sub(int rd, int rs, int rt);
	void slt(int rd, int rs, int rt);
	void addi(int rd, int rs, int imm);
	void slti(int rd, int rs, int imm);
	void AND(int rd, int rs, int rt);
	void OR(int rd, int rs, int rt);
	void XOR(int rd, int rs, int rt);
	void NOR(int rd, int rs, int rt);
	void andi(int rd, int rs, int imm);
	void ori(int rd, int rs, int imm);
	void xori(int rd, int rs, int imm);
	void lw(int rt, int imm);
	void sw(int rt, int imm);
	void j(string L);
	void jr(int rs);
	void bltz(int rs, string L);
	void beq(int rs, int rt, string);
	void bne(int rs, int rt, string);
	void jal(string L);
};

int CicloSimple::PC = 0;
vector<int> CicloSimple::regs = MakeVector();

int main(int argc, char *argv[]) {
	CicloSimple MIPS;
	MIPS.add(3, 4, 5);
	return 0;
}
