#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "table.h"
using namespace std;

// 函数声明
void STRCON();
void program();
void const_des(bool is_local_defined);
void const_def(bool is_local_defined);
bool unsigned_int();
void INTCON();
void declare_head();
bool ICCON();
void variable_des(bool is_local_defined);
void variable_def(bool is_local_defined);
void variable_def_without_init(bool is_local_defined);
void variable_def_with_init(bool is_local_defined);
void func_with_return_def();
void func_without_return_def();
bool compound_statement(bool is_return_int, bool is_return_char);
void parameter_list(string func_name, bool is_return, bool is_return_int);
void main_func();
bool expression();
bool item();
bool factor();
string statement(bool is_return_int, bool is_return_char);
void assign_state();
bool condi_state(bool is_return_int, bool is_return_char);
void condition();
bool loop_state(bool is_return_int, bool is_return_char);
void step_size();
bool case_state(bool is_return_int, bool is_return_char);
bool case_table(bool is_return_int, bool is_return_char, bool is_const_int);
bool case_sub(bool is_return_int, bool is_return_char, bool is_const_int);
bool case_default(bool is_return_int, bool is_return_char);
bool func_with_return_call();
bool func_without_return_call();
void value_param_list(string func_name, bool is_duplicated);
bool state_list(bool is_return_int, bool is_return_char);
void read_state();
void write_state();
bool return_state(bool is_return_int, bool is_return_char);

vector<string> error_ans;
vector<string> tokens;
vector<string> names;
vector<int> rows;

int pos;  // token指针当前位置
int len = 0;    // tokens长度
string token = "";

map<string, bool> functions;		// 记录有无返回值
map<string, bool> return_functions; // 记录返回值类型  值int 1，  char 0
map<string, bool> identifiers; 			// 全局标识符
map<string, bool> identifiers_local; 	// 局部标识符

vector<string> consts;				// 全局常量
vector<string> consts_local;		// 局部常量


// 定义Function类	
class Function{
	public:
		string func_name;
		bool is_return_int;
		bool is_void;
		int num_of_params;
		vector<bool> params_type;

		// with params
		Function(string name, bool is_void_in, bool is_return_int_in, vector<bool> params_type_in){
			this->func_name = name;
			this->is_void = is_void_in;
			this->is_return_int = is_return_int_in;
			this->num_of_params = params_type_in.size();
			this->params_type = params_type_in;
		}

		// is params nums matched return true
		bool checkParamsNum(vector<bool> params){
			return this->num_of_params == params.size();
		}

		// is params matched return true
		bool checkIsMatch(vector<bool> params){
			for (int i = 0; i < this->num_of_params; i++){
				if (this->params_type[i] != params[i]){
					return false;
				}
			}
			return true;
		}
};

// 函数参数列表
map<string, Function> functions_params;

// 查找变量类型
bool findVariableType(string name){ // true:int, false:char
	bool flag = false;

	map<string, bool>::iterator iter;
	iter = identifiers_local.find(name);	// 先查局部变量
	if (iter != identifiers_local.end()){	
		flag = iter->second;
	}
	else{
		iter = identifiers.find(name);		// 再查全局变量
		if (iter != identifiers.end()){
			flag = iter->second;
		}
	}

	return flag;
}

// 添加错误信息到文件
ofstream errorfile;
void error(char c){
	errorfile << rows[pos] << " " << c << endl;
}// error

// 原代码
void error_out(string s) {
	error_ans.emplace_back(s + " error!——!");
	cout << rows[pos] << "\t" << s << ":   " << names[pos] << "   ------   " << tokens[pos] << endl;
}

void Forward() {
	if (pos + 1 < len) {
		token = tokens[++pos];
	}
}

void Retrack() {
	if (pos - 1 >= 0) {
		token = tokens[--pos];
	}
}

// 判断数字和字符合法
bool isDigit(char c){
	return (c >= '0') && (c <= '9');
}

bool isAlpha(char c){
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_'); 
}

// 非法符号或不符合词法
void check_error_a(){
	if (tokens[pos] == "STRCON"){
		if (names[pos].size() == 0){
			error('a');
			error_out("String不合词法");
			return;
		}
		for (char c:names[pos]){
			if (c != 32 && c != 33 && !(c >= 35 && c <= 126)){
				error('a');
				error_out("String");
				break;
			}
		}
	}
	else if (tokens[pos] == "CHARCON"){
		if (names[pos][0] != '+' && names[pos][0] != '-' && names[pos][0] != '*' && names[pos][0] != '/' &&
		 !isDigit(names[pos][0]) && !isAlpha(names[pos][0])){
			error('a');
			error_out("Char不合词法");
		}
	}
}

// 名字重定义
bool check_error_b(bool is_local){
	bool flag = false;

	string identifier_name = names[pos];

	map<string, bool>::iterator iter;  

	if (is_local == true){	// 判断局部
		iter = identifiers_local.find(identifier_name);
		if (iter != identifiers_local.end()){
			flag = true;
		}

		if (find(consts_local.begin(), consts_local.end(), identifier_name) != consts_local.end()){
			flag = true;
		}
	}
	else{				// 判断全局
		iter = functions.find(identifier_name);
		if (iter != functions.end()){
			flag = true;
		}
		iter = identifiers.find(identifier_name);
		if (iter != identifiers.end()){
			flag = true;
		}
		if (find(consts.begin(), consts.end(), identifier_name) != consts.end()){
			flag = true;
		}
	}


	if (flag){
		error('b');
		error_out(identifier_name + "名字重定义");
	}

	return flag;
}

// 未定义的名字
bool check_error_c(){

	bool flag = true;

	string identifier_name = names[pos];

	map<string, bool>::iterator iter;  
	iter = identifiers_local.find(identifier_name);
	// 先查找局部变量，常量
	if (iter != identifiers_local.end()){
		flag = false;
	}
	else if (find(consts_local.begin(), consts_local.end(), identifier_name) != consts_local.end()){
		flag = false;
	}
	// 再查找全局，以及函数名
	else{
		iter = functions.find(identifier_name);
		if (iter != functions.end()){
			flag = false;
		}
		else{
			iter = identifiers.find(identifier_name);
			if (iter != identifiers.end()){
				flag = false;
			}
			else if (find(consts.begin(), consts.end(), identifier_name) != consts.end()){
				flag = false;
			}			
		}
	}	
	// 没找到，报错
	if (flag){
		error('c');
		error_out("未定义的名字");
	}

	return flag;
}

// 函数参数个数不匹配
void check_error_d(){
	if (true){
		error('d');
		error_out("函数参数个数不匹配");
	}
}

// 函数参数类型不匹配
void check_error_e(){
	if (true){
		error('e');
		error_out("函数参数类型不匹配");
	}
}

// 条件判断中出现不合法的类型
void check_error_f(){
	if (true){
		error('f');
		error_out("条件判断中出现不合法的类型");
	}
}

// 无返回值的函数存在不匹配的return语句
void check_error_g(){
	if (true){
		error('g');
		error_out("无返回值的函数存在不匹配的return语句");
	}
}

// 有返回值的函数缺少 return 语句或存在不匹配的 return 语句
void check_error_h(){
	if (true){
		error('h');
		error_out("有返回值的函数缺少 return 语句或存在不匹配的 return 语句");
	}
}

// 数组元素的下标只能是整型表达式
void check_error_i(bool flag){
	if (flag == false){
		error('i');
		error_out("数组元素的下标只能是整型表达式");
	}
}

// 不能改变常量的值
void check_error_j(){
	bool flag = false;
	if (find(consts.begin(),consts.end(),names[pos]) != consts.end()){
		flag = true;
	}
	else if (find(consts_local.begin(),consts_local.end(),names[pos]) != consts_local.end()){
		flag = true;
	}

	if (flag == true){
		error('j');
		error_out("不能改变常量的值");
	}
}

// 应为分号
void check_error_k(){
	if (tokens[pos] != "SEMICN"){
		Retrack();
		error('k');
		error_out("应为分号 ;");
	}
}

// 应为右小括号 )
void check_error_l(){
	if (tokens[pos] != "RPARENT"){
		Retrack();
		error('l');
		error_out("应为右小括号 )");
	}
}

// 应为右中括号 ]
void check_error_m(){
	if (tokens[pos] != "RBRACK"){
		Retrack();
		error('m');
		error_out("应为右中括号 ]");
	}
}

// 数组初始化个数不匹配
void check_error_n(bool flag){
	if (flag){
		error('n');
		error_out("数组初始化个数不匹配");
	}
}

// <常量>类型不一致
void check_error_o(bool flag){
	if (flag){
		error('o');
		error_out("<常量>类型不一致");
	}
}

// 缺少缺省语句
void check_error_p(){
	if (true){
		error('p');
		error_out("缺少缺省语句");
	}
}
// 错误定义结束



// 开始ex2代码
// 添加了行数
void ADD() {
	error_ans.emplace_back(to_string(rows[pos])+ "\t: " + token + " " + names[pos]);
}

// 关系运算符
void OP_COM() {
	if (token != table["<"] && token != table["<="] && token != table[">"] && token != table[">="] && token != table["!="] && token != table["=="]) {
		error_out("OP_COM()");
	}
	else {
		ADD();
	}
}

void LBRACE() {
	if (token != table["{"]) {
		error_out("LBRACE()");
	}
	else {
		ADD();
	}
}

void RBRACE() {
	if (token != table["}"]) {
		error_out("RBRACE()");
	}
	else {
		ADD();
	}
}

void LBRACK() {
	if (token != table["["]) {
		error_out("LBRACK()");
	}
	else {
		ADD();
	}
}

// 右中括号需要错误处理
void RBRACK() {
	if (token != table["]"]) {
		check_error_m();
	}
	else {
		ADD();
	}
}

void LPARENT() {
	if (token != table["("]) {
		error_out("LPARENT()");
	}
	else {
		ADD();
	}
}

// 右小括号需要错误处理
void RPARENT() {
	if (token != table[")"]) {
		check_error_l();
	}
	else {
		ADD();
	}
}

void CHARCON() {
	if (token != table["字符常量"]) {
		error_out("CHARCON()");
	}
	else {
		ADD();
		check_error_a();
	}
}

void STRCON() {
	if (token != table["字符串"]) {
		error_out("STRCON()");
	}
	else {
		ADD();
		check_error_a();
		error_ans.emplace_back("<字符串>");
	}
}

// 分号也需要错误处理
void SEMICN() {
	if (token != table[";"]) {
		check_error_k();
	}
	else {
		ADD();
	}
}

void COLON() {
	if (token != table[":"]) {
		error_out("COLON()");
	}
	else {
		ADD();
	}
}

void ASSIGN() {
	if (token != table["="]) {
		error_out("ASSIGN()");
	}
	else {
		ADD();
	}
}

// 判断标识符
void IDENFR() {
	if (token != table["标识符"]) {
		error_out("IDENFR()");
	}
	else {
		ADD();
	}
}


// 无符号整数
bool unsigned_int() {
	if (token != table["整形常量"]) {
		error_out("unsigned_int()");
		return 0;
	}
	else {
		ADD();
		error_ans.emplace_back("<无符号整数>");
		return 1;
	}
}

// 整数
void INTCON() {
	if (token == table["+"] || token == table["-"]) {
		ADD();
		Forward();
		unsigned_int();
		error_ans.emplace_back("<整数>");
	}
	else if (token == table["整形常量"]) {
		unsigned_int();
		error_ans.emplace_back("<整数>");
	}
	else {
		error_out("INTCON()");
	}
}

bool ICCON() {   // 常量	int 1, char 0
	if (token == table["字符常量"]) {
		CHARCON();
		error_ans.emplace_back("<常量>");
		return 0;
	}
	else if (token == table["+"] || token == table["-"] || token == table["整形常量"]) {
		INTCON();
		error_ans.emplace_back("<常量>");
		return 1;
	}
	else {
		error_out("ICCON()");
		return 0;
	}
}

// 程序
void program() {
	if (token == table["const"]) {
		// 全局定义
		const_des(false);
		Forward();
	}
	if (tokens[pos + 2] != table["("] && (token == table["int"] || token == table["char"])) {	// 应该是0
		variable_des(false);
		Forward();
	}
	while (tokens[pos + 2] == table["("] && (token == table["int"] || token == table["char"] || token == table["void"])) {	// 应该是1
		if (token == table["int"] || token == table["char"]) {
			func_with_return_def();
		}
		if (token == table["void"] && tokens[pos + 1] != table["main"]) {   // 不能是主函数
			func_without_return_def();
		}
		Forward();
	}
	Retrack();
	main_func();
	error_ans.emplace_back("<程序>");
}

// 常量说明
void const_des(bool is_local_defined) {
	while (token == table["const"]) {
		ADD();

		Forward();
		const_def(is_local_defined);

		Forward();
		SEMICN();

		Forward();
	}
	Retrack();
	error_ans.emplace_back("<常量说明>");
}

// 常量定义
void const_def(bool is_local_defined) {
	if (token == table["int"]) {
		ADD();

		Forward();
		IDENFR();
		// 查看是否重定义
		if (!check_error_b(is_local_defined)){
			// 添加到对应vector
			if (is_local_defined == false){

				identifiers[names[pos]] = true;
				consts.push_back(names[pos]);
			}
			else{

				identifiers_local[names[pos]] = true;
				consts_local.push_back(names[pos]);
			}
		}

		Forward();
		ASSIGN();

		Forward();
		INTCON();

		Forward();
		while (token == table[","]) {
			ADD();

			Forward();
			IDENFR();
			// 查看是否重复定义
			if (!check_error_b(is_local_defined)){
				if (is_local_defined == false){
					identifiers[names[pos]] = true;
					consts.push_back(names[pos]);
				}
				else{
					identifiers_local[names[pos]] = true;
					consts_local.push_back(names[pos]);
				}
			}


			Forward();
			ASSIGN();

			Forward();
			INTCON();

			Forward(); // 查看之后一个是不是‘，’，判断循环
		}
		Retrack();
		error_ans.emplace_back("<常量定义>");
	}
	else if (token == table["char"]) {
		ADD();

		Forward();
		IDENFR();
		// 查看是否重复定义
		if (!check_error_b(is_local_defined)){
			if (is_local_defined == false){
				identifiers[names[pos]] = true;
				consts.push_back(names[pos]);
			}
			else{
				identifiers_local[names[pos]] = true;
				consts_local.push_back(names[pos]);
			}
		}

		Forward();
		ASSIGN();

		Forward();
		CHARCON();

		Forward();
		while (token == table[","]) {
			ADD();

			Forward();
			IDENFR();
			// 查看是否重复定义
			if (!check_error_b(is_local_defined)){
				if (is_local_defined == false){
					identifiers[names[pos]] = true;
					consts.push_back(names[pos]);
				}
				else{
					identifiers_local[names[pos]] = true;
					consts_local.push_back(names[pos]);
				}
			}

			Forward();
			ASSIGN();

			Forward();
			CHARCON();

			Forward();
		}
		Retrack();
		error_ans.emplace_back("<常量定义>");
	}
	else {
		error_out("const_def()");
	}
}

// 声明头部
void declare_head() {
	bool flag;
	if (token == table["int"]) {
		flag = true;
	}else if(token == table["char"]){
		flag = false;
	}else{
		error_out("declare_head()");
	}
	ADD();

	Forward();
	IDENFR();
	if (!check_error_b(false)){
		functions[names[pos]] = true;
		return_functions[names[pos]] = flag;
	}
	error_ans.emplace_back("<声明头部>");
}

// 变量说明
void variable_des(bool is_local_defined) {
	variable_def(is_local_defined);

	Forward();
	SEMICN();

	Forward();
	while ((token == table["int"] || token == table["char"]) && tokens[pos + 2] != table["("]) {
		variable_def(is_local_defined);

		Forward();
		SEMICN();

		Forward();
	}

	Retrack();
	error_ans.emplace_back("<变量说明>");
}

// 变量定义
void variable_def(bool is_local_defined) {
	if (pos + 2 < len && tokens[pos + 2] == table["="]) {
		variable_def_with_init(is_local_defined);
	}
	else if (pos + 5 < len && tokens[pos + 2] == table["["] && tokens[pos + 5] == table["="]) {
		variable_def_with_init(is_local_defined);
	}
	else if (pos + 8 < len && tokens[pos + 2] == table["["] && tokens[pos + 5] == table["["] && tokens[pos + 8] == table["="]) {
		variable_def_with_init(is_local_defined);
	}
	else {
		variable_def_without_init(is_local_defined);
	}

	error_ans.emplace_back("<变量定义>");
}

void variable_def_without_init(bool is_local_defined) {
	bool flag;	// 记录类型
	if (token == table["int"] || token == table["char"]) {
		ADD();

		if (tokens[pos] == "INTTK"){
			flag = true;
		}
		else{
			flag = false;
		}

		Forward();
		if (token == table["标识符"]) {
			IDENFR();
			// 查看是否重复定义
			if (!check_error_b(is_local_defined)){
				if (is_local_defined == false){
					identifiers[names[pos]] = flag;
				}
				else{
					identifiers_local[names[pos]] = flag;
				}
			}

			Forward();
			if (token == table["["]) {
				ADD();

				Forward();
				// 数组下标只能是无符号整数
				check_error_i(unsigned_int());

				Forward();
				RBRACK();

				Forward();
				if (token == table["["]) {
					ADD();

					Forward();
					check_error_i(unsigned_int());

					Forward();
					RBRACK();

				}
				else {
					Retrack();
				}
			}
			else {
				Retrack();
			}
		}
	}

	Forward();
	while (token == table[","]) {
		ADD();
		Forward();
		if (token == table["标识符"]) {
			IDENFR();
			// 查看是否重复定义
			if (!check_error_b(is_local_defined)){
				if (is_local_defined == false){
					identifiers[names[pos]] = flag;
				}
				else{
					identifiers_local[names[pos]] = flag;
				}
			}

			Forward();
			if (token == table["["]) {
				ADD();

				Forward();
				check_error_i(unsigned_int());

				Forward();
				RBRACK();

				Forward();
				if (token == table["["]) {
					ADD();

					Forward();
					check_error_i(unsigned_int());

					Forward();
					RBRACK();
				}
				else {
					Retrack();
				}
			}
			else {
				Retrack();
			}
		}
		Forward();
	}
	Retrack();
	error_ans.emplace_back("<变量定义无初始化>");
}

void variable_def_with_init(bool is_local_defined) {
	if (token == table["int"] || token == table["char"]) {
		ADD();

		// 计数匹配
		int n = 0, m = 0; // a[n][m]
		int count_n = 0, count_m = 0; // 实际值
		bool const_match = true;
		
		// 后续判断类型是否一致
		bool flag;
		if (tokens[pos] == "INTTK"){
			flag = true;
		}
		else{
			flag = false;
		}


		Forward();
		IDENFR();
		// 查看是否重复定义
		if (!check_error_b(is_local_defined)){
			if (is_local_defined == false){
				identifiers[names[pos]] = flag;
			}
			else{
				identifiers_local[names[pos]] = flag;
			}
		}

		Forward();
		if (token == table["="]) {
			ADD();

			Forward();
			bool const_flag = ICCON();
			check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));
		}
		else if (token == table["["]) {
			ADD();

			Forward();
			check_error_i(unsigned_int());
			n = atoi(names[pos].c_str());

			Forward();
			RBRACK();

			Forward();
			if (token == table["="]) {
				ADD();

				Forward();
				LBRACE();

				Forward();
				bool const_flag = ICCON();
				check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));
				count_n = 1;

				Forward();
				while (token == table[","]) {
					ADD();

					Forward();
					bool const_flag = ICCON();
					check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));

					Forward();
					count_n++;
				}// 遇到 } 才会退出

				// 检验个数匹配
				if (count_n != n){
					const_match = false;
				}

				RBRACE();
			}
			else if (token == table["["]) {
				ADD();          // [

				Forward();
				check_error_i(unsigned_int()); // 无符号整数
				m = atoi(names[pos].c_str());

				Forward();
				RBRACK();   // ]

				Forward();
				ASSIGN();   // =

				Forward();
				LBRACE();   // {
				count_n = 1;

				Forward();
				LBRACE();   // {
				count_m = 1;

				Forward();
				bool const_flag = ICCON();
				check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));


				Forward();
				while (token == table[","]) {
					ADD();

					Forward();
					bool const_flag = ICCON();
					check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));

					Forward();
					count_m++;
				}
				// 跳出说明遇到了 }

				if (count_m != m){
					const_match = false;
				}

				RBRACE();

				count_m = 0;

				Forward();
				while (token == table[","]) {
					ADD();

					Forward();
					LBRACE();

					Forward();
					bool const_flag = ICCON();
					check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));
					count_m++;

					Forward();
					while (token == table[","]) {
						ADD();

						Forward();
						bool const_flag = ICCON();
						check_error_o((const_flag == true && flag == false)||(const_flag == false && flag == true));
						
						Forward();
						count_m++;
					}
					// 跳出说明遇到了 }
					if (count_m != m){
						const_match = false;
					}
					RBRACE();

					Forward();
					count_m = 0;
					count_n++;
				}
				// 跳出说明遇到了 }
				if (count_n != n){
					const_match = false;
				}
				RBRACE();
			}
		}
		// 查看数量是否匹配
		if(const_match == false){
			check_error_n(true);
		}

		error_ans.emplace_back("<变量定义及初始化>");
	}
}

void func_with_return_def() {

	bool is_return_char = false;
	bool is_return_int = false;
	string func_name = names[pos+1];
	if(token==table["int"]){
		is_return_int = true;
	}else if(token==table["char"]){
		is_return_char = true;
	}else{
		is_return_int = false;
		is_return_char = false;
	}


	declare_head();

	Forward();
	LPARENT();

	Forward();
	parameter_list(func_name, true, is_return_int);

	Forward();
	RPARENT();

	Forward();
	LBRACE();

	Forward();
	bool has_return = compound_statement(is_return_int, is_return_char);

	Forward();
	RBRACE();

	error_ans.emplace_back("<有返回值函数定义>");
	//
	if(has_return==false){
		check_error_h();
	}
	identifiers_local.clear();
	consts_local.clear();
}

void func_without_return_def() {

	string func_name = names[pos+1];


	if (token == table["void"]) {
		ADD();

		Forward();
		IDENFR();
		if (!check_error_b(false)){
			functions[func_name] = false;
		}

		Forward();
		LPARENT();

		Forward();
		parameter_list(func_name, false, false);

		Forward();
		RPARENT();

		Forward();
		LBRACE();

		Forward();
		bool has_return = compound_statement(false, false);

		Forward();
		RBRACE();

		error_ans.emplace_back("<无返回值函数定义>");

		identifiers_local.clear();
		consts_local.clear();
	}
	else {
		error_out("无返回值函数定义");
	}
}

bool compound_statement(bool is_return_int, bool is_return_char) {
	bool has_return = false;
	if (token == table["const"]) {
		const_des(true);
		Forward();
	}
	if ((token == table["int"] || token == table["char"]) && (tokens[pos + 2] != table["("])) {
		variable_des(true);
		Forward();
	}
	has_return = state_list(is_return_int,is_return_char);
	error_ans.emplace_back("<复合语句>");
	return has_return;
}

// 参数表
void parameter_list(string func_name, bool is_return, bool is_return_int) { // 死循环
	vector<bool> params_type;
	if (token == table["int"] || token == table["char"]) {
		ADD();
		bool flag = false;
		if (tokens[pos] == "INTTK"){
			flag = true;
		}

		Forward();
		IDENFR();
		if (!check_error_b(true)){
			identifiers_local[names[pos]] = flag;
		}

		params_type.emplace_back(flag);

		Forward();
		while (token == table[","]) {
			ADD();
			Forward();
			if (token == table["int"] || token == table["char"]) {
				ADD();
				flag = false;
				if (tokens[pos] == "INTTK"){
					flag = true;
				}

				Forward();
				IDENFR();
				if (!check_error_b(true)){
					identifiers_local[names[pos]] = flag;
				}

				params_type.emplace_back(flag);
			}
			Forward();
		}
		Retrack();

		Function my_func = Function(func_name, is_return, is_return_int, params_type);

		// TODO 直接用等号会出问题
		// functions_params[func_name] = my_func;
		functions_params.insert(pair<string, Function>(func_name, my_func));
		

		error_ans.emplace_back("<参数表>");
	}
	else if (token == table[")"]) {    // 参数为 空， 直接读取 ) 。需要回退一位
		Retrack();
		error_ans.emplace_back("<参数表>");
	}
	else {
		error_out("参数表");
	}
}

void main_func() {
	if (token == table["void"]) {
		ADD();

		Forward();
		if (token == table["main"]) {
			ADD();

			Forward();
			LPARENT();

			Forward();
			RPARENT();

			Forward();
			LBRACE();

			Forward();
			compound_statement(false, false);

			Forward();
			RBRACE();
			error_ans.emplace_back("<主函数>");
		}
		else {
			error_out("main");
		}
	}
	else {
		error_out("main");
	}
}

// 改为bool
bool expression() {
	bool flag = false;
	if (token == table["+"] || token == table["-"]) {
		ADD();
		Forward();
	}
	flag |= item();

	Forward();
	while (token == table["+"] || token == table["-"]) {
		ADD();

		Forward();
		item();
		flag = true;

		Forward();
	}
	Retrack();
	error_ans.emplace_back("<表达式>");
	return flag;
}

//项
bool item() {
	bool flag = false;
	flag |= factor();

	Forward();
	while (token == table["*"] || token == table["/"]) {
		ADD();

		Forward();
		flag = factor();

		Forward();
	}
	Retrack();

	error_ans.emplace_back("<项>");
	return flag;
}

//  int为1，char为0
bool factor() {
	bool flag = false;
	if (token == table["标识符"]) {

		IDENFR();
		if (check_error_c() == false){
			flag = findVariableType(names[pos]);
		}

		Forward();
		if (token == table["["]) {
			ADD();

			Forward();
			check_error_i(expression());

			Forward();
			RBRACK();

			Forward();
			if (token == table["["]) {
				ADD();

				Forward();
				check_error_i(expression());

				Forward();
				RBRACK();
			}
			else {
				Retrack();
			}
		}
		else if (token == table["("]) {
			Retrack();
			error_ans.pop_back();
			flag = func_with_return_call();
		}
		else {
			Retrack();
		}
		error_ans.emplace_back("<因子>");
	}
	else if (token == table["("]) {
		ADD();

		Forward();
		flag = expression();

		Forward();
		RPARENT();
		error_ans.emplace_back("<因子>");
	}
	else if (token == table["整形常量"] || token == table["+"] || token == table["-"]) {
		INTCON();
		flag = 1;
		error_ans.emplace_back("<因子>");
	}
	else if (token == table["字符常量"]) {
		CHARCON();
		flag = 0;
		error_ans.emplace_back("<因子>");
	}
	else {
		error_out("因子");
	}
	return flag;
}

string statement(bool is_return_int, bool is_return_char) {   // 语句
	string str = "false";
	bool flag = false;
	bool is_statement = false;

	if (token == table["while"] || token == table["for"]) {
		flag = loop_state(is_return_int,is_return_char);
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["if"]) {
		flag = condi_state(is_return_int,is_return_char);
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["标识符"] && (tokens[pos + 1] == table["="] || tokens[pos + 1] == table["["])) {
		assign_state();
		Forward(); SEMICN();
		flag = false;
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if(token == table["标识符"]){
		// 判断有无返回值
		string func_name = names[pos];
		map<string, bool>::iterator iter;  
		//TODO 寻找有时会出问题
		iter = return_functions.find(func_name);
		if(iter->second == true){
			func_with_return_call();
		}else{
			func_without_return_call();
		}
		Forward(); SEMICN();
		flag = false;
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["scanf"]) {
		read_state();
		Forward(); SEMICN();
		flag = false;
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["printf"]) {
		write_state();
		Forward(); SEMICN();
		flag = false;
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["return"]) {
		flag = return_state(is_return_int,is_return_char);
		Forward(); SEMICN();
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["switch"]) {
		flag = case_state(is_return_int,is_return_char);
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table["{"]) {
		LBRACE();
		Forward(); 
		flag = state_list(is_return_int,is_return_char);
		Forward(); RBRACE();
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}
	else if (token == table[";"]) {
		SEMICN();
		flag = false;
		is_statement = true;
		error_ans.emplace_back("<语句>");
	}

	if (is_statement == false){
		return "not";
	}
	else if (flag){
		return "true";
	}
	else {
		return "false";
	}

}

void assign_state() {
	if (token == table["标识符"]) {
		ADD();
		check_error_j();
		check_error_c();

		Forward();
		if (token == table["="]) {
			ADD();
			Forward();
			expression();
			error_ans.emplace_back("<赋值语句>");
		}
		else if (token == table["["]) {
			ADD();
			Forward();
			check_error_i(expression());
			Forward();
			RBRACK();

			Forward();
			if (token == table["["]) {
				ADD();
				Forward();
				check_error_i(expression());
				Forward();
				RBRACK();
				Forward();
			}
			ASSIGN();
			Forward();
			expression();
			error_ans.emplace_back("<赋值语句>");
		}
		else {
			error_out("assign_state()");
		}
	}
}

bool condi_state(bool is_return_int, bool is_return_char) {
	bool flag = false;
	string str = "";

	if (token == table["if"]) {
		ADD();

		Forward();
		LPARENT();

		Forward();
		condition();

		Forward();
		RPARENT();

		Forward();
		str = statement(is_return_int, is_return_char);

		Forward();
		if (token == table["else"]) {
			ADD();

			Forward();
			str = statement(is_return_int, is_return_char);

			Forward();
		}
		Retrack();
		error_ans.emplace_back("<条件语句>");
	}
	return str == "true"? true:false;
}

void condition() {
	bool flag = true;
	flag &= expression();
	Forward();
	OP_COM();
	Forward();
	flag &= expression();
	error_ans.emplace_back("<条件>");
	if(!flag){
		check_error_f();
	}
}

bool loop_state(bool is_return_int, bool is_return_char) {
	bool flag = false;
	string str = "";
	if (token == table["while"]) {
		ADD();

		Forward();
		LPARENT();

		Forward();
		condition();

		Forward();
		RPARENT();

		Forward();
		str = statement(is_return_int, is_return_char);

		error_ans.emplace_back("<循环语句>");
	}
	else if (token == table["for"]) {
		ADD();

		Forward();
		LPARENT();

		Forward();
		IDENFR();
		check_error_c();

		Forward();
		ASSIGN();

		Forward();
		expression();

		Forward();
		SEMICN();

		Forward();
		condition();

		Forward();
		SEMICN();

		Forward();
		IDENFR();
		check_error_c();

		Forward();
		ASSIGN();

		Forward();
		IDENFR();
		check_error_c();

		Forward();
		if (token == table["+"] || token == table["-"]) {
			ADD();
		}
		Forward();
		step_size();

		Forward();
		RPARENT();

		Forward();
		str = statement(is_return_int, is_return_char);

		error_ans.emplace_back("<循环语句>");
	}
	else {
		error_out("loop_state()");
	}
	return str == "true"? true:false;
}

void step_size() {
	unsigned_int();
	error_ans.emplace_back("<步长>");
}

bool case_state(bool is_return_int, bool is_return_char) {
	bool flag = false;
	bool is_const_int = false;

	if (token == table["switch"]) {
		ADD();
		Forward(); LPARENT();
		Forward(); 
		is_const_int = expression();

		Forward(); RPARENT();
		Forward(); LBRACE();

		Forward(); 
		flag = case_table(is_return_int,is_return_char,is_const_int);
		
		Forward(); 
		if (tokens[pos] == "DEFAULTTK"){
			flag = case_default(is_return_int, is_return_char);
		}
		else{
			check_error_p();
			Retrack();
		}

		Forward(); RBRACE();
		error_ans.emplace_back("<情况语句>");
		return flag;
	}
	else {
		error_out("case_state()");
	}
	return flag;
}

bool case_table(bool is_return_int, bool is_return_char, bool is_const_int) {
	bool flag = false;
	flag |= case_sub(is_return_int, is_return_char, is_const_int);
	
	Forward();
	while (token == table["case"]) {
		flag |= case_sub(is_return_int, is_return_char, is_const_int);
		Forward();
	}
	Retrack();
	error_ans.emplace_back("<情况表>");
	return flag;
}

bool case_sub(bool is_return_int, bool is_return_char, bool is_const_int) {
	bool flag = false;
	string str = "";
	if (token == table["case"]) {
		ADD();

		Forward(); 
		bool const_flag = ICCON();
		check_error_o((const_flag == true && is_const_int == false)||(const_flag == false && is_const_int == true));
	
		Forward(); 
		COLON();

		Forward(); 
		str = statement(is_return_int, is_return_char);

		error_ans.emplace_back("<情况子语句>");
	}
	return str == "true"? true:false;
}

bool case_default(bool is_return_int, bool is_return_char) {
	bool flag = false;
	string str = "";
	if (token == table["default"]) {
		ADD();
		Forward(); COLON();

		Forward(); 
		str = statement(is_return_int,is_return_char);

		error_ans.emplace_back("<缺省>");
	}
	return str == "true"? true:false;
}

bool func_with_return_call() {
	IDENFR();

	string func_name = names[pos];
	// 是否未定义
	bool is_duplicated = check_error_c();

	Forward(); LPARENT();
	Forward(); value_param_list(func_name, is_duplicated);
	Forward(); RPARENT();
	error_ans.emplace_back("<有返回值函数调用语句>");

	// 判断返回值类型
	map<string, bool>::iterator iter_int;  
	iter_int = return_functions.find(func_name);
	return iter_int->second;
}

bool func_without_return_call() {
	IDENFR();
	Forward(); LPARENT();
	error_ans.emplace_back("<值参数表>");
	Forward(); RPARENT();
	error_ans.emplace_back("<无返回值函数调用语句>");
	return false;
}

// 值参数表
void value_param_list(string func_name, bool is_duplicated) {
	vector<bool> params;	// 记录参数类型

	if (token == table[")"] || token == table[";"])
	{
		// Retrack(); //会退一个，  )会有之后函数单独处理
		error_ans.emplace_back("<值参数表>");
	}else{
		params.emplace_back(expression());
		Forward();
		while (token == table[","]) {
			ADD();
			Forward(); 
			params.emplace_back(expression());

			Forward();
		}
		error_ans.emplace_back("<值参数表>");
	}
	Retrack();

	// 判断函数的参数和类型
	if (!is_duplicated){
		map<string, Function>::iterator iter;
		iter = functions_params.find(func_name);

		// check nums of params
		if (!(iter->second.checkParamsNum(params))){
			check_error_d();
		}
		else if (!(iter->second.checkIsMatch(params))){
			check_error_e();
		}
	}
}

// 语句列
bool state_list(bool is_return_int, bool is_return_char) {
	bool flag = false;

	// 替换
	while(true){
		string str = statement(is_return_int, is_return_char);
		if (str == "not"){
			break;
		}
		else if (str == "true"){
			flag |= true;
		}
		else if (str == "false"){
			flag |= false;
		}
		Forward();
	}

	Retrack();
	error_ans.emplace_back("<语句列>");
	return flag;
}

void read_state() {
	if (token == table["scanf"]) {
		ADD();
		Forward(); LPARENT();

		Forward(); IDENFR();
		check_error_j();
		check_error_c();

		Forward(); RPARENT();
		error_ans.emplace_back("<读语句>");
	}
}

void write_state() {
	if (token == table["printf"]) {
		ADD();
		Forward(); LPARENT();
		Forward();
		if (token == table["字符串"]) {
			STRCON();
			Forward();
			if (token == table[","]) {
				ADD();
				Forward(); expression();
				Forward(); RPARENT();
			}
			else if (token == table[")"]) {
				RPARENT();
			}
			else {
				Retrack();
			}
		}
		else if (token == table["+"] || token == table["-"] || token == table["标识符"] || token == table["("] || token == table["整形常量"] || token == table["字符常量"]) {
			expression();
			Forward(); RPARENT();
		}
		error_ans.emplace_back("<写语句>");
	}
}

bool return_state(bool is_return_int, bool is_return_char) {
	bool not_return_void = false;

	if (token == table["return"]) {
		not_return_void = true;
		ADD();

		Forward();
		if (token == table["("]) {
			LPARENT();
			
			Forward(); 
			if(token==table[")"]){
				if (is_return_char == true || is_return_int == true){
					check_error_h();
				}
				Forward();
			}else{
				bool exp_flag =  expression();
				if (is_return_char == false && is_return_int == false){
					check_error_g();
				}
				else if(exp_flag == false && is_return_int == true){
					check_error_h();
				}
				else if (exp_flag == true && is_return_char == true){
					check_error_h();
				}

				Forward(); RPARENT();
				Forward();
			}
		}
		// semicn
		else if (token == table[";"] && (is_return_char==true || is_return_int==true)){
			check_error_h();
		}
		Retrack();
		
		error_ans.emplace_back("<返回语句>");
	}
	else {
		error_out("return_state()");
	}
	return not_return_void;
}

void print_error_error_ans() {
	ofstream outfile;
	outfile.open("ouput_error.txt");
	for (int i = 0; i < error_ans.size(); i++) {
		outfile << error_ans[i] << endl;
	}
	outfile.close();
}

int error_analyse(vector<string>& t, vector<string>& w,vector <int> r) {
	tokens = t;
	names = w;
	rows = r;

	errorfile.open("error.txt");
	cout << "开始错误处理:" << endl;
	cout << tokens.size() << " " << names.size() << " " << rows.size() << endl;

	// 语法分析
	len = tokens.size();
	token = tokens[0];
	pos = 0;

	program();

	print_error_error_ans();
	return 0;
}
