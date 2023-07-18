#include "test.h"
#include "TypeRich.h"
#include "UserDefineLiteral.h"
#include <iostream>

void TestTypeRich() {
	//// 使用预定义的msk类型去定义带单位的变量
	//Momentum m1{ 1.234 };
	//Force f1{ 1.234 };
	// // 相同msk类型的变量可以相互赋值
	//Momentum m2 = m1;
	//// 不同msk类型的变量赋值会在编译时报错
	//Force f2 = m1;
	//// 同理不能单纯的用double类型
	//auto ReceiveAMomentumVariable = [](const Momentum&) {};
	//ReceiveAMomentumVariable(1.1);

	//// 将构造函数声明为constexpr，就可以定义编译时物理常量
	//constexpr Acceleration g1{ 9.80665 };
	//constexpr Speed c2{ 299792458.0 };

	//// 利用自定义字面量类型，可以使用尾缀来更方便的定义常量
	//constexpr Acceleration g1= 9.80665_ms2;
	//constexpr Speed c2= 299792458.0_ms;

	//// 可以实现MSK之间的运算
	//Momentum m3 = m1 + m2;
	//Momentum m4 = 30.0_N * 0.1_s;
	//// 非法的量纲运算将会在编译时报出
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