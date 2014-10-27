#ifndef QTVTK_H
#define QTVTK_H

#include <QMainWindow>
#include "ui_qtvtk.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkNumericSeriesFileNames.h"
#include "itkPNGImageIO.h"
#include "itkImageToVTKImageFilter.h"


#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)


#include "vtkSmartPointer.h"    // Required for smart pointer internal ivars.

#include "RawImagesReader.h"




typedef itk::Image< short, 2 >  ImageType;
typedef itk::Image< short, 3 >  ImageType3D;
typedef itk::ImageFileReader< ImageType >  ReaderType;//typedef itk::ImageSeriesReader< ImageType >  ReaderType;
typedef itk::ImageToVTKImageFilter< ImageType > ConnectorType;



class QtVtk : public QMainWindow
{
	Q_OBJECT

public:
	QtVtk(QWidget *parent = 0);
	~QtVtk();

private:
	Ui_QtVtkClass *ui;

private slots:
	void doTest();
	void doHessian();

private:




	ReaderType::Pointer reader; 
	ConnectorType::Pointer connector; 



	ImageType3D::Pointer imageVolume;
	RawImagesReader *rawImagesReader;
	RawImagesPointer rawImages;

};

#endif // QTVTK_H
