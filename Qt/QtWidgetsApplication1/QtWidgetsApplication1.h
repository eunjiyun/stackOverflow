#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

class In3DTestWidget;

class QtWidgetsApplication1 : public QMainWindow//메인 윈도우
{
    //
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = nullptr);
    ~QtWidgetsApplication1();

public:
    void test();
    void colchan();

public:
    In3DTestWidget* widget;
    vtkUnsignedCharArray* cl;// = vtkUnsignedCharArray::New();
private:
    Ui::QtWidgetsApplication1Class ui;
    
};
