#include "table.h"
#define MAX_LINE 1024

vector<string> name;
vector<string> category;

void print(){
	int len = name.size();
	for(int i=0; i<len; i++){
		cout << category[i] << " " << name[i] << endl;
	}
}

int main(){
    char c = '\0';
	string buffer;
	// 从键盘读取buffer
	while(c=getchar()){
		if(c=='?')
			break;
		else
			buffer+=c;
	}
	// cout << buffer << endl;
    

	string token="";	// 正在识别的单词
	int forward = 0; 	// 向前指针
	int buffer_size = buffer.size();	// 总长度

	cout << "analyse begin:" << endl;
	// 开始逐字符判断
	while(forward < buffer_size){
		token += buffer[forward];  //更新token

		// 特殊字符  +=*/:=;,()[]{}
		if(signal_char.find(token)!=signal_char.npos){
			name.emplace_back(token);
			category.emplace_back(table[token]);
		}

		// 比较运算符    先判断 <,>,=,! 再判断 <=,>=,==,!=
		if(signal_comparison.find(token)!=signal_comparison.npos){
			token += buffer[++forward];
			if(find(double_cocmparison.begin(),double_cocmparison.end(),token) != double_cocmparison.end()){
				name.emplace_back(token);
				category.emplace_back(table[token]);
			}else{
				token.erase(1,1);	// 删除第二个字符
				name.emplace_back(token);
				category.emplace_back(table[token]);
				--forward;
			}
		}

		// 判断整形常量
		if(isdigit(buffer[forward])){
			while(isdigit(buffer[++forward])){
				token += buffer[forward];
			}
			--forward;
			name.emplace_back(token);
			category.emplace_back(table["整形常量"]);
		}
		
		// 判断字符常量
		if(token=="\'"){
			// cout << "开始字符判断..." ;
			while(buffer[++forward] !='\''){
				token+=buffer[forward];
			} 
			token.erase(0,1);  // 去掉开头的  ' 
			// cout << "当前token: " << token << "类型: " << table["字符常量"] <<  endl;
			name.emplace_back(token);
			category.emplace_back(table["字符常量"]);
		}

		// 判断字符串
		if(token=="\""){
			// cout << "开始字符串判断...." ;
			while(buffer[++forward] !='\"'){
				token+=buffer[forward];
			} 
			token.erase(0,1);  // 去掉开头的  " 
			// cout << "当前token: " << token << ".... "<< table["字符串"];
			name.emplace_back(token);
			category.emplace_back(table["字符串"]);
			// cout << "已添加进容器" << endl;
		}
		
		// 判断关键字 或 标识符
		if(isalpha(buffer[forward]) || buffer[forward]=='_'){
			while(isalnum(buffer[++forward]) || buffer[forward]=='_'){
				token += buffer[forward];
			}
			--forward;
			string temp = token;	// 保留token原有格式，向name中填写
			transform(token.begin(),token.end(),token.begin(),::tolower);	// token变为小写,关键字识别用小写
			if(find(key_word.begin(),key_word.end(),token) != key_word.end()){
				name.emplace_back(temp);
				category.emplace_back(table[token]);
			}else{
				name.emplace_back(temp);
				category.emplace_back(table["标识符"]);
			}
		}
		// 重置token, 指针后移
		token = "";
		++forward;
	}
	
	print();
	// cout << "长度:" <<category.size() << " " << name.size() << endl;
	cout << "analyse complete..." << endl;
    return 0;
}