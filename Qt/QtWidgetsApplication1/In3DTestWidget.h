#pragma once

#include <QWidget>
#include "ui_In3DTestWidget.h"
#include "In3DVTK_Def.h"


QT_BEGIN_NAMESPACE
namespace Ui { class In3DTestWidgetClass; };
QT_END_NAMESPACE



class In3DTestWidget : public QVTKOpenGLNativeWidget// public QWidget
{
	Q_OBJECT

public:
	In3DTestWidget(QWidget *parent = nullptr);
	~In3DTestWidget();
   
public:
    void LoadTest();

public:

    vtkFloatArray* hsvValues;
    vtkUnsignedCharArray* clippedColors;// = vtkUnsignedCharArray::New();
    vtkPolyData* polyData;
    vtkSmartPointer<vtkPolyDataMapper> mapper;

    vtkSmartPointer<vtkActor> actor;

    vtkSmartPointer<vtkRenderer> renderer;

    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
   
private:
	Ui::In3DTestWidgetClass *ui;
};
