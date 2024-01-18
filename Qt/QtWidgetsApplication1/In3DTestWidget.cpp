#include "In3DTestWidget.h"

#include <QDebug>

In3DTestWidget::In3DTestWidget(QWidget* parent)
	: QVTKOpenGLNativeWidget(parent)
	, ui(new Ui::In3DTestWidgetClass())
{
	ui->setupUi(this);
}

In3DTestWidget::~In3DTestWidget()
{
	delete ui;
}

void In3DTestWidget::LoadTest()
{
	qDebug() << "LoadTest Call";

	vtkSmartPointer<vtkPLYReader> reader{ vtkSmartPointer<vtkPLYReader>::New() };

	reader->SetFileName(u8"C:\\Users\\dbzho\\OneDrive\\Desktop\\Field_Training\\vtk\\vtk_실습용_프로젝트\\upperJaw_1.ply");
	reader->Update();

	polyData = reader->GetOutput();

	// 클리핑 전 RGB 색상 정보를 저장합니다.
	vtkUnsignedCharArray* originalColors{ vtkUnsignedCharArray::SafeDownCast(polyData->GetPointData()->GetScalars()) };


	// 클리핑된 폴리데이터의 각 점에 대한 새로운 RGB 색상 배열을 생성합니다.
	clippedColors = vtkUnsignedCharArray::New();
	clippedColors->SetNumberOfComponents(3); // R, G, B
	clippedColors->SetName("Colors");

	// Create a new array to store the HSV values
	hsvValues = vtkFloatArray::New();

	hsvValues->SetNumberOfComponents(3);
	hsvValues->SetName("HSVValues");

	for (int i{}; i < originalColors->GetNumberOfTuples(); ++i){
		float r{ static_cast<float>(originalColors->GetComponent(i, 0)) };
		float g{ static_cast<float>(originalColors->GetComponent(i, 1)) };
		float b{ static_cast<float>(originalColors->GetComponent(i, 2)) };

		// Convert RGB to HSV
		float maxVal{ std::max(std::max(r, g), b) };
		float minVal{ std::min(std::min(r, g), b) };
		float delta{ maxVal - minVal };

		float hue, saturation, value;
		if (0==delta ){
			hue = 0;
			saturation = 0;
			value = maxVal;
		}
		else{
			if (maxVal == r)
				hue = (g - b) / delta;
			else if (maxVal == g)
				hue = 2 + (b - r) / delta;
			else
				hue = 4 + (r - g) / delta;

			hue *= 60;
			if (0>hue )
				hue += 360;

			saturation = delta / maxVal;
			value = maxVal;
		}

		// 변환된 RGB 값을 vtkFloatArray에 추가합니다.
		hsvValues->InsertNextTuple3(hue, saturation, value);
	}

	polyData->GetPointData()->SetScalars(hsvValues);

	// 클리핑을 수행합니다.
	vtkClipPolyData* clipper{ vtkClipPolyData::New() };
	clipper->SetInputData(polyData);

	clipper->SetValue(20);
	clipper->Update();

	// 클리핑된 폴리데이터를 가져옵니다.
	polyData = clipper->GetOutput();




	// 클리핑된 폴리데이터의 각 점에 대해 가장 가까운 원본 점의 색상을 매핑합니다.
	for (int i{}; i < polyData->GetNumberOfPoints(); ++i)
		clippedColors->InsertNextTuple3(255, 255, 255);

	


	// 클리핑된 폴리데이터에 매핑된 색상 정보를 설정합니다.
	polyData->GetPointData()->SetScalars(clippedColors);

	

	// Visualize
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);

	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
	renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
	//QVTKOpenGLNativeWidget::interactor()->Render();

	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}
