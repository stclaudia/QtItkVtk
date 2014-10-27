#pragma once

#include <string>
#include <QtCore/QString>
using namespace std;

#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkRawImageIO.h"
#include "itkNumericSeriesFileNames.h"
#include "itkImageToVTKImageFilter.h"



#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)



#include "vtkSmartPointer.h"
#include "vtkImageData.h"


typedef unsigned short PixelType;
typedef itk::Image<PixelType, 3> ImagesType;
typedef ImagesType::Pointer RawImagesPointer;
typedef itk::ImageToVTKImageFilter< ImagesType> ConnectorType3D;
typedef itk::ImageSeriesReader<ImagesType> RawImagesReaderType;
typedef itk::RawImageIO<PixelType, 2> RawImageIOType;

typedef itk::NumericSeriesFileNames NameGeneratorType;




class RawImagesReader
{
public:
	RawImagesReader(void);
	~RawImagesReader(void);

	void ReadandConnect(QString imageDirectory, int xSize, int ySize, int zSize);

	vtkSmartPointer<vtkImageData> imageData;

 

private:



	RawImagesReaderType::Pointer rawImagesReader;
	RawImageIOType::Pointer rawImageIO;
	NameGeneratorType::Pointer nameGenerator;



	ConnectorType3D::Pointer connector3D;
	int xSize;
	int ySize;
	int zSize;
	
};

