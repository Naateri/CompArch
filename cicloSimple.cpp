#include <iostream>
#include <vector>
#include <string>

using namespace std;
class CicloSimple{
private:
	static int PC;
	static vector<int> $; //registros
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
	
public:
	CicloSimple(){
		this->ALUSrc = 0;
		this->ALUFunc = 0;
		this->RegDst = 0;
		if ($.empty()){
			for (int i = 0; i < 31; i++)
				$.push_back(0);
		}
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

int main(int argc, char *argv[]) {

	return 0;
}

