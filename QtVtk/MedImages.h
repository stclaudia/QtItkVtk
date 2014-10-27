

#pragma once

#include <string>
using namespace std;

#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkMetaDataObject.h"
#include "gdcmGlobal.h"
#include "itkExtractImageFilter.h"


#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)
#include "vtkSmartPointer.h"
#include "vtkImageData.h"




enum ImageDirection
{
	ImageDirection_XY = 1,
	ImageDirection_XZ,
	ImageDirection_YZ
};


class CMedImages
{
public:
	CMedImages(void);
	~CMedImages(void);

	void SetDirectory(string directory);
	void Update();

	vtkImageData* GetImageData(ImageDirection direction, int imageIndex);
	int GetWindowCenter();
	int GetWindowWidth();
	int xSize;//Rows
	int ySize;//Columns
	int zSize;//Planes

private:
	void LoadImages();
	int GetValueFromTag(string tag);
	void ObtainImagesInfomation();

	typedef signed short PixelType;
	typedef itk::Image<PixelType, 3> ImagesType;
	typedef itk::ImageSeriesReader<ImagesType> ReaderType;
	typedef itk::GDCMImageIO ImageIOType;



	ReaderType::Pointer reader;
	ImageIOType::Pointer gdcmImageIO;
	ImagesType::Pointer imageVolume;

	vtkSmartPointer<vtkImageData> imageData2D;



	int windowCenter;
	int windowWidth;


	string directory;

};



