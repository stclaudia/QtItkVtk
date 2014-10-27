#include "qtvtk.h"

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "vtkBMPReader.h"

#include "vtkSmartPointer.h"
#include "vtkImageMapper.h"
#include "vtkActor2D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"

#include "vtkMarchingCubes.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"

#include <QFileDialog>
#include <QtCore/QString>
#include <QtGui>
#include <QMessageBox.h>


#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"

//�ж�qstring�Ƿ�Ϊ����
int isDigitStr(QString src)
{
	QByteArray ba = src.toLatin1();//QString ת��Ϊ char*  
	const char *s = ba.data();

	while (*s && *s >= '0' && *s <= '9') s++;

	if (*s)
	{ //���Ǵ�����  
		return 0;
	}
	else
	{ //������  
		return 1;
	}
}

QtVtk::QtVtk(QWidget *parent)
: QMainWindow(parent)

{
	this->ui = new Ui_QtVtkClass;
	this->ui->setupUi(this);

	 reader = ReaderType::New();
	 connector = ConnectorType::New();

}

QtVtk::~QtVtk()
{


}

void QtVtk::doTest()

{
	//���ļ�
	QString fileful;   //����ȡ���ļ���
	fileful = QFileDialog::getOpenFileName(this, "Open", QDir::currentPath(), "All files(*.*);;Image(*.bmp *.jpg *.png)");

	

	if (fileful.isNull())   // �û�ȡ��ѡ��
	{ 	
		QMessageBox::information(this, "Document", "No document", QMessageBox::Ok | QMessageBox::Cancel);		
	}
	
	    //�û�ѡ�����ļ�
		// �����ļ�
	else {

    QMessageBox::information(this, "Document", fileful + " is selected", QMessageBox::Ok | QMessageBox::Cancel);
    QString  filename,filepath,filesuffix;
	QFileInfo fileinfo;
	fileinfo = QFileInfo(fileful);
	
	filename = fileinfo.fileName();//�ļ���	
	filesuffix = fileinfo.suffix();//�ļ���׺	
    filepath = fileinfo.absolutePath();//����·��
//	QMessageBox::information(this, "Document","filename: "+ filename + ". filesuffix:  " + filesuffix + ". filepath:  " + filepath, QMessageBox::Ok | QMessageBox::Cancel);

	//QstringתΪchar *
	const QByteArray text = fileful.toLocal8Bit();
	const char *path = text.data();


	if ((filesuffix == "bmp") || (filesuffix == "Bmp") || (filesuffix == "BMP"))//�ļ���׺bmp

	{

		QMessageBox::information(this, "Document", "bmp.", QMessageBox::Ok | QMessageBox::Cancel);
	/*		*/
	}
	else if ((filesuffix == "png"))//�ļ���׺png
	{

		QMessageBox::information(this, "Document", "png done", QMessageBox::Ok | QMessageBox::Cancel);

	}


	else if (filesuffix.isNull())//�ļ��޺�׺������dicom��ʽ����
	{		
		QMessageBox::information(this, "Document", "Dicom not done.", QMessageBox::Ok | QMessageBox::Cancel);
	}

	else  if (isDigitStr( filesuffix))//�ļ���׺����,RAW���ݴ���
	{
		
		int xsize = 256;
		int ysize = 256;
		int zsize = 60;


		rawImagesReader = new RawImagesReader;

		QMessageBox::information(this, "Document", "Dicom 1.", QMessageBox::Ok | QMessageBox::Cancel);

		rawImagesReader->ReadandConnect(filepath, xsize, ysize, zsize);



		//����VTK��MC�㷨
		vtkMarchingCubes* march = vtkMarchingCubes::New();
		march->SetInputData(rawImagesReader->imageData);
		march->SetValue(0,45);
		march->Update();

		vtkPolyDataNormals* ployer = vtkPolyDataNormals::New();
		ployer->SetInputData(march->GetOutput());
		ployer->SetFeatureAngle(50.0);

		vtkPolyDataMapper *DoMapper = vtkPolyDataMapper::New();
		DoMapper->SetInputData(march->GetOutput());

		vtkActor *DoActor = vtkActor::New();
		DoActor->SetMapper(DoMapper);

		//��Ⱦ���ڿ��
		auto ren = vtkSmartPointer< vtkRenderer >::New();

		ren->AddActor(DoActor);
		ren->SetBackground(1, 1, 1);


		ui->qvtkwidget->GetRenderWindow()->AddRenderer(ren);
		ren->Render();



		QMessageBox::information(this, "Document", "Dicom not done.", QMessageBox::Ok | QMessageBox::Cancel);
	}

	}

}

void QtVtk::doHessian()

{








	QMessageBox::information(this, "Document", "Done.", QMessageBox::Ok | QMessageBox::Cancel);

}