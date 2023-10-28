
class Graph;
class GraphFactory {
public:
  Graph* create();
} *_factory;


// 考虑一个抽象类Graph，它代表一切可绘制图形要素，并提供了抽象接口Draw()
class Graph {
public:
  virtual void draw() = 0;
};

// 可以继承该抽象类，并对抽象接口实现，以对图形要素进行扩展
class Text : public Graph {};
class Picture : public Graph {};
// ...

  // 客户可以从相应工厂中获得Graph的一个实例，然后调用Draw()接口绘图
void test()
{
  // ......
  Graph* graph = _factory->create();

  // ......

  graph->draw();

}

// 1. 现在新增了为所有图形要素绘制边框的功能，并要求支持多种边框风格
// 这个功能独立于原有的Draw()功能实现，可以用抽象接口drawBrace()来表示
// 假设test()面向客户，不允许修改，如何设计DrawBase结构，来完成该功能的扩展
class DrawBrace {
  virtual void drawBrace() = 0;
};
class DrawBraceWithStyle1 : public DrawBrace {};
class DrawBraceWithStyle2 : public DrawBrace {};
// ...

// 2. 在1的基础上，现在新增了为所有图形要素绘制滚动条的功能，同样要求支持多种滚动条风格
// 该功能同样独立于原有的Draw()功能以及drawBrace()实现，可以用抽象接口drawScrollBar()表示
// 允许客户使用参数来控制工厂，是否为图形要素绘制Brace或者ScrollBar
class DrawScrollBar {
  virtual void drawScrollBar() = 0;
};
class DrawScrollBarWithStyle1 : public DrawBrace {};
class DrawScrollBarWithStyle2 : public DrawBrace {};
// ...

// 3. 在2的基础上，现在要新支持一种新的图形要素Table
// 假设Graph的开发由A来负责，而新的扩展功能由B来负责，并且A不知道B的工作内容
// 如何调整前面的结构，来方便A开发新的图形要素Table，并使Table同样支持12中Brace和ScrollBar的功能
class Table : public Graph {};

#include <vector>
class Shape {};

// 考虑现在已经实现了这样一个功能Operation，它支持对两组Shape进行运算，并输出运算结果
// 它提供了公开接口operate()，用于客户调用，以及具体的步骤接口，在具体的操作中完成实现
// 目前已经完成了部分操作的实现
class Operation {
public:
  void operate(std::vector<Shape>& operandA, std::vector<Shape>& operandB, std::vector<Shape>& result) {
    step1();
    step2();
    step3();
  }
protected:
  virtual void step1() = 0;
  virtual void step2() = 0;
  virtual void step3() = 0;
};
class OperationOr : public Operation {};
class OperationAnd : public Operation {};

// 1. 为了方便Debug，可能要打印每一步产生的中间数据
// 为此在开发的过程中，需要新增一条Debug Flow以打印中间数据
class PrintIntermediates {
private:
  void printPoint();
  void printCorner();
  void printBox();
};

// 2. 为了直观对比计算的数据，可能在operate()的过程中，需要将box输出到文件中用于可视化
// 1和2的功能独立，可以由开发者利用两个宏在编译时单独开启和关闭
class TranslateToStream {
private:
  void translate(const std::vector<Shape>&);
};

// 3. 现在考虑补充新的操作OperationNot，如何保证OperationNot同样支持12中的Debug功能
class OperationNot : public Operation {};