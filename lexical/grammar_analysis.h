#pragma once
#include<iostream>
#include<string.h>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
class Grammar
{
private:
	vector<pair<string, string>> tokens;
	int idx;
	string token;
	FILE *fout;
	vector<string> func_with_return_value;
	vector<string> func_without_return_value;
public:
	Grammar(vector<pair<string, string>> lexical_results, FILE *fout);
	void program_entry();
	void constant_description();
	void constant_definition();
	void signed_integer();
	void declaration_header();
	void constant();
	void variable_description();
	void variable_definition();
	void variable_definition_not_init();
	void variable_definition_and_init();
	void func_definition_with_return_value();
	void func_definition_without_return_value();
	void compound_statement();
	void parameter_table();
	void main_func();
	void expression();
	void term();
	void factor();
	void statement();
	void assignment_statement();
	void conditional_statement();
	void condition();
	void circular_statement();
	void step();
	void case_statement();
	void case_table();
	void case_sub_statement();
	void default_fn();
	void func_call_statement_with_return_value();
	void func_call_statement_without_return_value();
	void value_parameter_table();
	void statement_column();
	void read_statement();
	void write_statement();
	void return_statement();
	string get_token(int i, bool flag);
	void forward_and_output();
	void analyse();
};

Grammar::Grammar(vector<pair<string, string>> lexical_results, FILE *fout)
{
	idx = -1;
	this->tokens = lexical_results;
	this->token = get_token(1, false);
	this->fout = fout;
}

string Grammar::get_token(int i, bool flag)
{
	string s = tokens[idx + i].first;
	if (flag == true)
		idx += i;
	return s;
}

void Grammar::forward_and_output()
{
	idx = idx + 1;
	string s1 = tokens[idx].first;
	string s2 = tokens[idx].second;
	printf("%s %s\n", s1.c_str(), s2.c_str());
	fprintf(fout, "%s %s\n", s1.c_str(), s2.c_str());
}

void Grammar::program_entry()
{
	if (token == "CONSTTK")
	{
		constant_description();
		token = get_token(1, false);
	}
	int flag = -1;
	if (token == "VOIDTK")
		flag = 1;
	else if (token == "INTTK" || token == "CHARTK")
	{
		token = get_token(3, false);
		if (token == "LPARENT")
			flag = 1;
		else
			flag = 0;
	}
	if (flag == 0)
	{
		variable_description();
	}
	token = get_token(1, false);
	while (1)
	{
		if (token == "INTTK" || token == "CHARTK")
		{
			func_definition_with_return_value();
			token = get_token(1, false);
		}
		else if (token == "VOIDTK")
		{
			token = get_token(2, false);
			if (token == "MAINTK")
			{
				main_func();
				break;
			}
			else if (token == "IDENFR")
			{
				func_definition_without_return_value();
				token = get_token(1, false);
			}
		}
	}
	printf("<程序>\n");
	fprintf(fout, "<程序>\n");
}

void Grammar::constant_description()
{
	while (1)
	{
		token = get_token(1, false);

			if (token == "CONSTTK")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "INTTK" || token == "CHARTK")
				{
					constant_definition();
					token = get_token(1, false);
					if (token == "SEMICN")
					{
						forward_and_output();
						token = get_token(1, false);
					}
				}
			}
			else
				break;
	}

	printf("<常量说明>\n");
	fprintf(fout, "<常量说明>\n");
}

void Grammar::constant_definition()
{
	int flag = -1;
	token = get_token(1, false);
	if (token == "INTTK")
		flag = 0;
	else if (token == "CHARTK")
		flag = 1;
	forward_and_output();
	token = get_token(1, false);
	while (1)
	{
		token = get_token(1, false);
		if (token == "IDENFR")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "ASSIGN")
			{
				forward_and_output();
				token = get_token(1, false);
				if (flag == 0) {
					if (token == "PLUS" || token == "MINU" || token == "INTCON")
					{
						signed_integer();
						token = get_token(1, false);
						if (token != "COMMA")
							break;
						else
							forward_and_output();
					}
				}
				else if (flag == 1)
				{
					if (token == "CHARCON")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token != "COMMA")
							break;
						else
							forward_and_output();
					}
				}
			}
		}
	}
	printf("<常量定义>\n");
	fprintf(fout, "<常量定义>\n");
}

void Grammar::signed_integer()
{
	token = get_token(1, false);
	if (token == "PLUS" || token == "MINU")
	{
		forward_and_output();
		token = get_token(1, false);
	}
	if (token == "INTCON")
	{
		forward_and_output();
		printf("<无符号整数>\n");
		fprintf(fout, "<无符号整数>\n");
		printf("<整数>\n");
		fprintf(fout, "<整数>\n");
	}
}

void Grammar::declaration_header()
{
	token = get_token(1, false);
	if (token == "INTTK" || token == "CHARTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "IDENFR")
		{
			forward_and_output();
			func_with_return_value.push_back(tokens[idx].second);
		}
	}
	printf("<声明头部>\n");
	fprintf(fout, "<声明头部>\n");
}

void Grammar::constant()
{
	token = get_token(1, false);
	if (token == "PLUS" || token == "MINU" || token == "INTCON")
	{
		signed_integer();
	}
	else if (token == "CHARCON")
	{
		forward_and_output();
	}
	printf("<常量>\n");
	fprintf(fout, "<常量>\n");
}

void Grammar::variable_description()
{
	variable_definition();
	token = get_token(1, false);
	if (token == "SEMICN")
	{
		forward_and_output();
		token = get_token(1, false);
		while (1)
		{
			if (token == "INTTK" || token == "CHARTK")
			{
				// 区别于函数定义，往前再看两步
				token = get_token(3, false);
				if (token != "LPARENT")
				{
					variable_definition();
					token = get_token(1, false);
					if (token == "SEMICN")
					{
						forward_and_output();
						token = get_token(1, false);
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;
		}
	}
	printf("<变量说明>\n");
	fprintf(fout, "<变量说明>\n");
}

void Grammar::variable_definition()
{
	token = get_token(3, false);
	if (token == "ASSIGN")
	{
		variable_definition_and_init();
	}
	else if (token == "LBRACK")
	{
		token = get_token(6, false);
		if (token == "ASSIGN")
		{
			variable_definition_and_init();
		}
		else if (token == "LBRACK")
		{
			token = get_token(9, false);
			if (token == "ASSIGN")
			{
				variable_definition_and_init();
			}
			else
				variable_definition_not_init();
		}
		else
			variable_definition_not_init();
	}
	else
		variable_definition_not_init();
	printf("<变量定义>\n");
	fprintf(fout, "<变量定义>\n");
}

void Grammar::variable_definition_and_init()
{
	token = get_token(1, false);
	if (token == "INTTK" || token == "CHARTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "IDENFR")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "ASSIGN")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "PLUS" || token == "MINU" || token == "INTCON" || token == "CHARCON")
				{
					constant();
				}
			}
			else if (token == "LBRACK")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "INTCON")
				{
					forward_and_output();
					printf("<无符号整数>\n");
					fprintf(fout, "<无符号整数>\n");
					token = get_token(1, false);
					if (token == "RBRACK")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "ASSIGN")
						{
							forward_and_output();
							token = get_token(1, false);
							if (token == "LBRACE")
							{
								forward_and_output();
								token = get_token(1, false);
								while (1)
								{
									if (token == "PLUS" || token == "MINU" || token == "INTCON" || token == "CHARCON")
									{
										constant();
										token = get_token(1, false);
										if (token == "COMMA")
										{
											forward_and_output();
											token = get_token(1, false);
										}
										else if (token == "RBRACE")
										{
											forward_and_output();
											break;
										}
									}
								}
							}
						}
						else if (token == "LBRACK")
						{
							forward_and_output();
							token = get_token(1, false);
							if (token == "INTCON")
							{
								forward_and_output();
								printf("<无符号整数>\n");
								fprintf(fout, "<无符号整数>\n");
								token = get_token(1, false);
								if(token == "RBRACK")
								{	
									forward_and_output();
									token = get_token(1, false);
									if (token == "ASSIGN")
									{
										forward_and_output();
										token = get_token(1, false);
										if (token == "LBRACE")
										{
											forward_and_output();
											token = get_token(1, false);
											if (token == "LBRACE")
											{
												forward_and_output();
												token = get_token(1, false);
												while (1)
												{
													if (token == "PLUS" || token == "MINU" || token == "INTCON" || token == "CHARCON")
													{
														constant();
														token = get_token(1, false);
														if (token == "COMMA")
														{
															forward_and_output();
															token = get_token(1, false);
														}
														else if (token == "RBRACE")
														{
															forward_and_output();
															break;
														}
													}
													else
														break;
												}
												token = get_token(1, false);
												if (token == "COMMA")
												{
													while (1)
													{
														if (token == "COMMA")
														{
															forward_and_output();
															token = get_token(1, false);
															if (token == "LBRACE")
															{
																forward_and_output();
																token = get_token(1, false);
																while (1)
																{
																	if (token == "PLUS" || token == "MINU" || token == "INTCON" || token == "CHARCON")
																	{
																		constant();
																		token = get_token(1, false);
																		if (token == "COMMA")
																		{
																			forward_and_output();
																			token = get_token(1, false);
																		}
																		else if (token == "RBRACE")
																		{
																			forward_and_output();
																			break;
																		}
																	}
																	else
																		break;
																}
															}
														}
														else
															break;
													}
													token = get_token(1, false);
													if (token == "RBRACE")
													{
														forward_and_output();
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("<变量定义及初始化>\n");
	fprintf(fout, "<变量定义及初始化>\n");
}

void Grammar::variable_definition_not_init()
{
	token = get_token(1, false);
	if (token == "INTTK" || token == "CHARTK")
	{
		forward_and_output();
		token = get_token(1, false);
		while (1)
		{
			if (token == "IDENFR")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "LBRACK")
				{
					if (token == "INTCON")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "RBRACK")
						{
							forward_and_output();
							token = get_token(1, false);
							if (token == "LBRACK")
							{
								forward_and_output();
								token = get_token(1, false);
								if (token == "INTCON")
								{
									forward_and_output();
									token = get_token(1, false);
									if (token == "RBRACK")
									{
										forward_and_output();
										token = get_token(1, false);
										if (token != "COMMA")
											break;
										else if (token == "COMMA")
										{
											forward_and_output();
											token = get_token(1, false);
										}
									}
								}
								else if (token != "COMMA")
									break;
								else if (token == "COMMA")
								{
									forward_and_output();
									token = get_token(1, false);
								}
							}
						}
					}
					else if (token != "COMMA")
						break;
					else if (token == "COMMA")
					{
						forward_and_output();
						token = get_token(1, false);
					}
				}
				else if (token != "COMMA")
					break;
				else if (token == "COMMA")
				{
					forward_and_output();
					token = get_token(1, false);
				}
			}
		}
	}
	printf("<变量定义无初始化>\n");
	fprintf(fout, "<变量定义无初始化>\n");
}

void Grammar::func_definition_with_return_value()
{
	token = get_token(1, false);
	if (token == "INTTK" || token == "CHARTK")
	{
		declaration_header();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "INTTK" || token == "CHARTK" || token == "RPARENT")
			{
				parameter_table();
				token = get_token(1, false);
				if (token == "RPARENT")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "LBRACE")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "CONSTTK" || token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
							|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
						{
							compound_statement();
							token = get_token(1, false);
							if (token == "RBRACE")
								forward_and_output();
						}
					}
				}
			}
		}
	}
	printf("<有返回值函数定义>\n");
	fprintf(fout, "<有返回值函数定义>\n");
}

void Grammar::func_definition_without_return_value()
{
	token = get_token(1, false);
	if (token == "VOIDTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "IDENFR")
		{
			forward_and_output();
			func_without_return_value.push_back(tokens[idx].second);
			token = get_token(1, false);
			if (token == "LPARENT")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "INTTK" || token == "CHARTK" || token == "RPARENT")
				{
					parameter_table();
					token = get_token(1, false);
					if (token == "RPARENT")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "LBRACE")
						{
							forward_and_output();
							token = get_token(1, false);
							if (token == "CONSTTK" || token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
								|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
							{
								compound_statement();
								token = get_token(1, false);
								if (token == "RBRACE")
									forward_and_output();
							}
						}
					}
				}
				
			}
		}
	}
	printf("<无返回值函数定义>\n");
	fprintf(fout, "<无返回值函数定义>\n");
}

void Grammar::compound_statement()
{
	token = get_token(1, false);
	if (token == "CONSTTK")
	{
		constant_description();
		token = get_token(1, false);
	}
	int flag = -1;
	if (token == "INTTK" || token == "CHARTK")
	{
		token = get_token(2, false);
		if (token == "LPARENT")
			flag = 1;
		else
			flag = 0;
	}
	if (flag == 0)
		variable_description();
	token = get_token(1, false);
	if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
		|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
		statement_column();
	printf("<复合语句>\n");
	fprintf(fout, "<复合语句>\n");
}

void Grammar::parameter_table()
{
	token = get_token(1, false);
	if (token == "INTTK" || token == "CHARTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "IDENFR")
		{
			forward_and_output();
			while (1)
			{
				token = get_token(1, false);
				if (token == "COMMA")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "INTTK" || token == "CHARTK")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "IDENFR")
							forward_and_output();
					}
				}
				else
					break;
			}
		}
	}
	printf("<参数表>\n");
	fprintf(fout, "<参数表>\n");
}

void Grammar::main_func()
{
	token = get_token(1, false);
	if (token == "VOIDTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "MAINTK")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "LPARENT")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "RPARENT")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "LBRACE")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "CONSTTK" || token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
							|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
						{
							compound_statement();
							token = get_token(1, false);
							if (token == "RBRACE")
								forward_and_output();
						}
					}
				}
			}
		}
	}
	printf("<主函数>\n");
	fprintf(fout, "<主函数>\n");
}

void Grammar::expression()
{
	token = get_token(1, false);
	if (token == "PLUS" || token == "MINU")
	{
		forward_and_output();
		token = get_token(1, false);
	}
	if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
		|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
	{
		term();
		while (1)
		{
			token = get_token(1, false);
			if (token == "PLUS" || token == "MINU")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
					|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
				{
					term();
				}
			}
			else
				break;
		}
	}
	printf("<表达式>\n");
	fprintf(fout, "<表达式>\n");
}

void Grammar::term()
{
	token = get_token(1, false);
	if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
		|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
	{
		factor();
		while (1)
		{
			token = get_token(1, false);
			if (token == "MULT" || token == "DIV")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
					|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
				{
					factor();
				}
			}
			else
				break;
		}
	}
	printf("<项>\n");
	fprintf(fout, "<项>\n");
}

void Grammar::factor()
{
	token = get_token(1, false);
	if (token == "IDENFR")
	{
		if (find(func_with_return_value.begin(), func_with_return_value.end(), tokens[idx + 1].second) != func_with_return_value.end())
			func_call_statement_with_return_value();
		else
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "LBRACK")
			{
				forward_and_output();
				expression();
				token = get_token(1, false);
				if (token == "RBRACK")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "LBRACK")
					{
						forward_and_output();
						expression();
						token = get_token(1, false);
						if (token == "RBRACK")
						{
							forward_and_output();
						}

					}
				}
			}
		}
	}
	else if (token == "LPARENT")
	{
		forward_and_output();
		expression();
		token = get_token(1, false);
		if (token == "RPARENT")
		{
			forward_and_output();
		}
	}
	else if (token == "PLUS" || token == "MINU" || token == "INTCON")
	{
		signed_integer();
	}
	else if (token == "CHARCON")
	{
		forward_and_output();
	}
	printf("<因子>\n");
	fprintf(fout, "<因子>\n");
}

void Grammar::statement()
{
	token = get_token(1, false);
	if (token == "WHILETK" || token == "FORTK")
		circular_statement();
	else if (token == "IFTK")
		conditional_statement();
	else if (token == "VOIDTK")
	{
		func_definition_without_return_value();
		token = get_token(1, false);
		if (token == "SEMICN")
			forward_and_output();
	}
	else if (token == "IDENFR")
	{
		token = get_token(2, false);
		if (token == "ASSIGN" || token == "LBRACK")
			assignment_statement();
		else if (find(func_with_return_value.begin(), func_with_return_value.end(), tokens[idx + 1].second) != func_with_return_value.end())
			func_call_statement_with_return_value();
		else if (find(func_without_return_value.begin(), func_without_return_value.end(), tokens[idx + 1].second) != func_without_return_value.end())
			func_call_statement_without_return_value();
		token = get_token(1, false);
		if (token == "SEMICN")
			forward_and_output();
	}
	else if (token == "SCANFTK")
	{
		read_statement();
		token = get_token(1, false);
		if (token == "SEMICN")
			forward_and_output();
	}
	else if (token == "PRINTFTK")
	{
		write_statement();
		token = get_token(1, false);
		if (token == "SEMICN")
			forward_and_output();
	}
	else if (token == "SWITCHTK")
		case_statement();
	else if (token == "SEMICN")
		forward_and_output();
	else if (token == "RETURNTK")
	{
		return_statement();
		token = get_token(1, false);
		if (token == "SEMICN")
			forward_and_output();
	}
	else if (token == "LBRACE")
	{
		forward_and_output();
		statement_column();
		token = get_token(1, false);
		if (token == "RBRACE")
			forward_and_output();

	}
	printf("<语句>\n");
	fprintf(fout, "<语句>\n");
}

void Grammar::assignment_statement()
{
	token = get_token(1, false);
	if (token == "IDENFR")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "ASSIGN")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
				expression();
		}
		else if (token == "LBRACK")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				expression();
				token = get_token(1, false);
				if (token == "RBRACK")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "ASSIGN")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
							|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
							expression();
					}
					else if (token == "LBRACK")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
							|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
						{
							expression();
							token = get_token(1, false);
							if (token == "RBRACK")
							{
								forward_and_output();
								token = get_token(1, false);
								if (token == "ASSIGN")
								{
									forward_and_output();
									token = get_token(1, false);
									if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
										|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
										expression();
								}
							}
						}
					}
				}
			}
		}
	}
	printf("<赋值语句>\n");
	fprintf(fout, "<赋值语句>\n");
}

void Grammar::conditional_statement()
{
	token = get_token(1, false);
	if (token == "IFTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				condition();
				token = get_token(1, false);
				if (token == "RPARENT")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
						|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
					{
						statement();
						while (1)
						{
							token = get_token(1, false);
							if (token == "ELSETK")
							{
								forward_and_output();
								token = get_token(1, false);
								if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
									|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
								{
									statement();
								}
							}
							else
								break;
						}
						
					}
				}
			}
		}
	}
	printf("<条件语句>\n");
	fprintf(fout, "<条件语句>\n");
}

void Grammar::condition()
{
	token = get_token(1, false);
	if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
		|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
	{
		expression();
		token = get_token(1, false);
		if (token == "LSS" || token == "LEQ" || token == "GRE" || token == "GEQ" || token == "EQL" || token == "NEQ")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				expression();
			}
		}
	}
	printf("<条件>\n");
	fprintf(fout, "<条件>\n");
}

void Grammar::circular_statement()
{
	token = get_token(1, false);
	if (token == "WHILETK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				condition();
				token = get_token(1, false);
				if (token == "RPARENT")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
						|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
						statement();
				}
			}
		}
	}
	else if (token == "FORTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "ASSIGN")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
						|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
					{
						expression();
						token = get_token(1, false);
						if (token == "SEMICN")
						{
							forward_and_output();
							token = get_token(1, false);
							if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
								|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
							{
								condition();
								token = get_token(1, false);
								if (token == "SEMICN")
								{
									forward_and_output();
									token = get_token(1, false);
									if (token == "IDENFR")
									{
										forward_and_output();
										token = get_token(1, false);
										if (token == "ASSIGN")
										{
											forward_and_output();
											token = get_token(1, false);
											if (token == "IDENFR")
											{
												forward_and_output();
												token = get_token(1, false);
												if (token == "PLUS" || token == "MINU")
												{
													forward_and_output();
													token = get_token(1, false);
													if (token == "INTCON")
													{
														step();
														token = get_token(1, false);
														if (token == "RPARENT")
														{
															forward_and_output();
															token = get_token(1, false);
															if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
																|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
																statement();
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("<循环语句>\n");
	fprintf(fout, "<循环语句>\n");
}

void Grammar::step()
{
	token = get_token(1, false);
	if (token == "INTCON")
	{
		forward_and_output();
		printf("<无符号整数>\n");
		fprintf(fout, "<无符号整数>\n");
	}
	printf("<步长>\n");
	fprintf(fout, "<步长>\n");
}

void Grammar::case_statement()
{
	token = get_token(1, false);
	if (token == "SWITCHTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				expression();
				token = get_token(1, false);
				if (token == "RPARENT")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "LBRACE")
					{
						forward_and_output();
						token = get_token(1, false);
						if (token == "CASETK")
						{
							case_table();
							token = get_token(1, false);
							if (token == "DEFAULTTK")
							{
								default_fn();
								token = get_token(1, false);
								if (token == "RBRACE")
									forward_and_output();
							}
						}
					}
				}
			}
		}
	}
	printf("<情况语句>\n");
	fprintf(fout, "<情况语句>\n");
}

void Grammar::case_table()
{
	token = get_token(1, false);
	if (token == "CASETK")
	{
		while (1)
		{
			token = get_token(1, false);
			if (token == "CASETK")
			{
				case_sub_statement();
			}
			else
				break;
		}
	}
	printf("<情况表>\n");
	fprintf(fout, "<情况表>\n");
}

void Grammar::case_sub_statement()
{
	token = get_token(1, false);
	if (token == "CASETK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "PLUS" || token == "MINU" || token == "INTCON" || token == "CHARTK")
		{
			constant();
			token = get_token(1, false);
			if (token == "COLON")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
					|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
					statement();
			}
		}
	}
	printf("<情况子语句>\n");
	fprintf(fout, "<情况子语句>\n");
}

void Grammar::default_fn()
{
	token = get_token(1, false);
	if (token == "DEFAULTTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "COLON")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
				|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
				statement();
		}
	}
	printf("<缺省>\n");
	fprintf(fout, "<缺省>\n");
}

void Grammar::func_call_statement_with_return_value()
{
	token = get_token(1, false);
	if (token == "IDENFR" && find(func_with_return_value.begin(), func_with_return_value.end(), tokens[idx + 1].second) != func_with_return_value.end())
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK" || token == "RPARENT")
			{
				value_parameter_table();
				token = get_token(1, false);
				if (token == "RPARENT")
					forward_and_output();
			}
		}
	}
	printf("<有返回值函数调用语句>\n");
	fprintf(fout, "<有返回值函数调用语句>\n");
}

void Grammar::func_call_statement_without_return_value()
{
	token = get_token(1, false);
	if (token == "IDENFR" && find(func_without_return_value.begin(), func_without_return_value.end(), tokens[idx + 1].second) != func_without_return_value.end())
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK" || token == "RPARENT")
			{
				value_parameter_table();
				token = get_token(1, false);
				if (token == "RPARENT")
					forward_and_output();
			}
		}
	}
	printf("<无返回值函数调用语句>\n");
	fprintf(fout, "<无返回值函数调用语句>\n");
}

void Grammar::value_parameter_table()
{
	token = get_token(1, false);
	if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
		|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
	{
		expression();
		while (1)
		{
			token = get_token(1, false);
			if (token == "COMMA")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
					|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
					expression();
			}
			else
				break;
		}
	}
	printf("<值参数表>\n");
	fprintf(fout, "<值参数表>\n");
}

void Grammar::statement_column()
{
	while (1)
	{
		token = get_token(1, false);
		if (token == "WHILETK" || token == "FORTK" || token == "IFTK" || token == "INTTK" || token == "CHARTK" || token == "VOIDTK" || token == "IDENFR"
			|| token == "SCANFTK" || token == "PRINTFTK" || token == "SWITCHTK" || token == "RETURNTK" || token == "LBRACE" || token == "SEMICN")
			statement();
		else
			break;
	}
	printf("<语句列>\n");
	fprintf(fout, "<语句列>\n");
}

void Grammar::read_statement()
{
	token = get_token(1, false);
	if (token == "SCANFTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR")
			{
				forward_and_output();
				token = get_token(1, false);
				if (token == "RPARENT")
					forward_and_output();
			}
		}
	}
	printf("<读语句>\n");
	fprintf(fout, "<读语句>\n");
}

void Grammar::write_statement()
{
	token = get_token(1, false);
	if (token == "PRINTFTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "STRCON")
			{
				forward_and_output();
				token = get_token(1, false);
				printf("<字符串>\n");
				fprintf(fout, "<字符串>\n");
				if (token == "COMMA")
				{
					forward_and_output();
					token = get_token(1, false);
					if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
						|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
					{
						expression();
						token = get_token(1, false);
						if (token == "RPARENT")
							forward_and_output();
					}
				}
				else if (token == "RPARENT")
					forward_and_output();
			}
			else if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				expression();
				token = get_token(1, false);
				if (token == "RPARENT")
					forward_and_output();
			}
		}
	}
	printf("<写语句>\n");
	fprintf(fout, "<写语句>\n");
}

void Grammar::return_statement()
{
	token = get_token(1, false);
	if (token == "RETURNTK")
	{
		forward_and_output();
		token = get_token(1, false);
		if (token == "LPARENT")
		{
			forward_and_output();
			token = get_token(1, false);
			if (token == "IDENFR" || token == "LPARENT" || token == "PLUS" || token == "MINU" || token == "INTCON"
				|| token == "CHARCON" || token == "INTTK" || token == "CHARTK")
			{
				expression();
				token = get_token(1, false);
				if (token == "RPARENT")
					forward_and_output();
			}
		}
	}
	printf("<返回语句>\n");
	fprintf(fout, "<返回语句>\n");
}
