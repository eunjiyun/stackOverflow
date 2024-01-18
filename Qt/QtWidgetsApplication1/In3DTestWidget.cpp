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

	reader->SetFileName(u8"C:\\Users\\dbzho\\OneDrive\\Desktop\\Field_Training\\vtk\\vtk_�ǽ���_������Ʈ\\upperJaw_1.ply");
	reader->Update();

	polyData = reader->GetOutput();

	// Ŭ���� �� RGB ���� ������ �����մϴ�.
	vtkUnsignedCharArray* originalColors{ vtkUnsignedCharArray::SafeDownCast(polyData->GetPointData()->GetScalars()) };


	// Ŭ���ε� ������������ �� ���� ���� ���ο� RGB ���� �迭�� �����մϴ�.
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

		// ��ȯ�� RGB ���� vtkFloatArray�� �߰��մϴ�.
		hsvValues->InsertNextTuple3(hue, saturation, value);
	}

	polyData->GetPointData()->SetScalars(hsvValues);

	// Ŭ������ �����մϴ�.
	vtkClipPolyData* clipper{ vtkClipPolyData::New() };
	clipper->SetInputData(polyData);

	clipper->SetValue(20);
	clipper->Update();

	// Ŭ���ε� ���������͸� �����ɴϴ�.
	polyData = clipper->GetOutput();




	// Ŭ���ε� ������������ �� ���� ���� ���� ����� ���� ���� ������ �����մϴ�.
	for (int i{}; i < polyData->GetNumberOfPoints(); ++i)
		clippedColors->InsertNextTuple3(255, 255, 255);

	


	// Ŭ���ε� ���������Ϳ� ���ε� ���� ������ �����մϴ�.
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
