
class Graph;
class GraphFactory {
public:
  Graph* create();
} *_factory;


// ����һ��������Graph��������һ�пɻ���ͼ��Ҫ�أ����ṩ�˳���ӿ�Draw()
class Graph {
public:
  virtual void draw() = 0;
};

// ���Լ̳иó����࣬���Գ���ӿ�ʵ�֣��Զ�ͼ��Ҫ�ؽ�����չ
class Text : public Graph {};
class Picture : public Graph {};
// ...

  // �ͻ����Դ���Ӧ�����л��Graph��һ��ʵ����Ȼ�����Draw()�ӿڻ�ͼ
void test()
{
  // ......
  Graph* graph = _factory->create();

  // ......

  graph->draw();

}

// 1. ����������Ϊ����ͼ��Ҫ�ػ��Ʊ߿�Ĺ��ܣ���Ҫ��֧�ֶ��ֱ߿���
// ������ܶ�����ԭ�е�Draw()����ʵ�֣������ó���ӿ�drawBrace()����ʾ
// ����test()����ͻ����������޸ģ�������DrawBase�ṹ������ɸù��ܵ���չ
class DrawBrace {
  virtual void drawBrace() = 0;
};
class DrawBraceWithStyle1 : public DrawBrace {};
class DrawBraceWithStyle2 : public DrawBrace {};
// ...

// 2. ��1�Ļ����ϣ�����������Ϊ����ͼ��Ҫ�ػ��ƹ������Ĺ��ܣ�ͬ��Ҫ��֧�ֶ��ֹ��������
// �ù���ͬ��������ԭ�е�Draw()�����Լ�drawBrace()ʵ�֣������ó���ӿ�drawScrollBar()��ʾ
// ����ͻ�ʹ�ò��������ƹ������Ƿ�Ϊͼ��Ҫ�ػ���Brace����ScrollBar
class DrawScrollBar {
  virtual void drawScrollBar() = 0;
};
class DrawScrollBarWithStyle1 : public DrawBrace {};
class DrawScrollBarWithStyle2 : public DrawBrace {};
// ...

// 3. ��2�Ļ����ϣ�����Ҫ��֧��һ���µ�ͼ��Ҫ��Table
// ����Graph�Ŀ�����A�����𣬶��µ���չ������B�����𣬲���A��֪��B�Ĺ�������
// ��ε���ǰ��Ľṹ��������A�����µ�ͼ��Ҫ��Table����ʹTableͬ��֧��12��Brace��ScrollBar�Ĺ���
class Table : public Graph {};

#include <vector>
class Shape {};

// ���������Ѿ�ʵ��������һ������Operation����֧�ֶ�����Shape�������㣬�����������
// ���ṩ�˹����ӿ�operate()�����ڿͻ����ã��Լ�����Ĳ���ӿڣ��ھ���Ĳ��������ʵ��
// Ŀǰ�Ѿ�����˲��ֲ�����ʵ��
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

// 1. Ϊ�˷���Debug������Ҫ��ӡÿһ���������м�����
// Ϊ���ڿ����Ĺ����У���Ҫ����һ��Debug Flow�Դ�ӡ�м�����
class PrintIntermediates {
private:
  void printPoint();
  void printCorner();
  void printBox();
};

// 2. Ϊ��ֱ�۶Աȼ�������ݣ�������operate()�Ĺ����У���Ҫ��box������ļ������ڿ��ӻ�
// 1��2�Ĺ��ܶ����������ɿ����������������ڱ���ʱ���������͹ر�
class TranslateToStream {
private:
  void translate(const std::vector<Shape>&);
};

// 3. ���ڿ��ǲ����µĲ���OperationNot����α�֤OperationNotͬ��֧��12�е�Debug����
class OperationNot : public Operation {};