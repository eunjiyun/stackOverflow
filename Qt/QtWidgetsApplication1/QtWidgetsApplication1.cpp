#include "QtWidgetsApplication1.h"
#include<iostream>
#include "In3DVTK_Def.h"
#include "In3DTestWidget.h"



//moc : 
// 소스 코드 -> .obj ->컴파일->링크(기계어로 번역)
//0bj파일로 exe파일 생성
//중간 단계에 moc_ ~~~ .obj ==>>중간 단계를 한번더 거친다.
//문제? 컴파일 속도가 느리다.
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	this->widget = new In3DTestWidget(this);
	this->widget->setGeometry(300, 100, 200, 200);
	this->widget->resize(900, 400);
	this->widget->LoadTest();

	

	//어떤 함수에서 어떻게 처리할지
	connect(ui.pushButton, &QPushButton::clicked, this, &QtWidgetsApplication1::test);
	cl = vtkUnsignedCharArray::New();
	connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication1::colchan);
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
void QtWidgetsApplication1::colchan()
{
	ui.pushButton_2->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "changed!", nullptr));

	
	cl->SetNumberOfComponents(3);
	for (int i{}; i < this->widget->polyData->GetNumberOfPoints(); ++i)
		cl->InsertNextTuple3(0, 0, 255);


	// 클리핑된 폴리데이터에 매핑된 색상 정보를 설정합니다.
	this->widget->polyData->GetPointData()->SetScalars(cl);


	this->widget->renderWindow->Render();
	//interactor->Start();
}
void QtWidgetsApplication1::test()
{
	ui.pushButton->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "pressed", nullptr));

	this->widget->renderWindow->AddRenderer(this->widget->renderer);
	this->widget->renderWindow->SetWindowId((void*)this->widget->winId());
	
	this->widget->interactor->SetRenderWindow(this->widget->renderWindow);

	this->widget->renderWindow->Render();
	this->widget->interactor->Start();
}