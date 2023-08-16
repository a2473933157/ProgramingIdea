#include "test.h"
#include "TypeRich.h"
#include "UserDefineLiteral.h"
#include <iostream>

void TestTypeRich() {
	//// ʹ��Ԥ�����msk����ȥ�������λ�ı���
	//Momentum m1{ 1.234 };
	//Force f1{ 1.234 };
	// // ��ͬmsk���͵ı��������໥��ֵ
	//Momentum m2 = m1;
	//// ��ͬmsk���͵ı�����ֵ���ڱ���ʱ����
	//Force f2 = m1;
	//// ͬ���ܵ�������double����
	//auto ReceiveAMomentumVariable = [](const Momentum&) {};
	//ReceiveAMomentumVariable(1.1);

	//// �����캯������Ϊconstexpr���Ϳ��Զ������ʱ������
	//constexpr Acceleration g1{ 9.80665 };
	//constexpr Speed c2{ 299792458.0 };

	//// �����Զ������������ͣ�����ʹ��β׺��������Ķ��峣��
	//constexpr Acceleration g1= 9.80665_ms2;
	//constexpr Speed c2= 299792458.0_ms;

	//// ����ʵ��MSK֮�������
	//Momentum m3 = m1 + m2;
	//Momentum m4 = 30.0_N * 0.1_s;
	//// �Ƿ����������㽫���ڱ���ʱ����
	//Force f3 = 30.0_N * 0.1_s;
	//Time t1 = 1.0_ms + 0.1_s;
}


void TestStringLiteral() {
	char a1[] =
		"<!DOCTYPE html>\r\n"
		"html lang = \"en\">\r\n"
		"  <head>\r\n"
		"  <meta charset = \"utf-8\">\r\n"
		"    <title>Hello World!</title>\r\n"
		"  </head>\r\n"
		"  <body>\r\n"
		"    Hello World!\r\n"
		"  </body>\r\n"
		"</html>\r\n";

	char a2[] = R"(<!DOCTYPE html>
		html lang = "en">
		  <head>
		  <meta charset = \"utf-8\">
		    <title>Hello World!</title>
		  </head>
		  <body>
		    Hello World!
		  </body>
		</html>
	)";

	auto a3 = UR"wzy(<!DOCTYPE html>
		html lang = "en">
		  <head>
		  <meta charset = \"utf-8\">
		    <title>Hello World!</title>
		  </head>
		  <body>
		    "(Hello World!)"
		  </body>
		</html>
	)wzy";

	const auto fozu = R"(
                            _ooOoo_
                           o8888888o
                           88" . "88
                           (| -_- |)
                            O\ = /O
                        ____/`---'\____
                      .   ' \\| |// `.
                       / \\||| : |||// \
                     / _||||| -:- |||||- \
                       | | \\\ - /// | |
                     | \_| ''\---/'' | |
                      \ .-\__ `-` ___/-. /
                   ___`. .' /--.--\ `. . __
                ."" '< `.___\_<|>_/___.' >'"".
               | | : `- \`.;`\ _ /`;.`/ - ` : | |
                 \ \ `-. \_ __\ /__ _/ .-` / /
         ======`-.____`-.___\_____/___.-`____.-'======
                            `=---='
		)";
	//std::cout << fozu;
}

void TestUserDefinedLiteral() {
	auto v1 = 123_w1;
	auto v2 = 123_w2;
	auto v3 = 12.3_w2;
	auto v4 = 12.3_w3;
	auto v5 = "hello world"_w4;
	auto v6 = 'a'_w5;
	auto v7 = 12.3_w6;
}