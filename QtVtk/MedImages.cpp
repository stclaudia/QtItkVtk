
//#include "stdafx.h"



#include "itkExtractImageFilter.h"
#include "itkImageToVTKImageFilter.h"

#include "MedImages.h"



CMedImages::CMedImages(void)
{
	reader = ReaderType::New();
	gdcmImageIO = ImageIOType::New();

}


CMedImages::~CMedImages(void)
{
}


void CMedImages::SetDirectory(string directory)
{
	this->directory = directory;
}

void CMedImages::LoadImages() 
{
	reader->SetFileName(directory);
	reader->SetImageIO(gdcmImageIO);

	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetInputDirectory(directory);
	typedef std::vector<std::string> FileNamesContainer;
	FileNamesContainer fileNames = nameGenerator->GetInputFileNames();

	zSize= fileNames.size();//»ñÈ¡zSize

	reader->SetImageIO(gdcmImageIO);
	reader->SetFileNames(fileNames);
	reader->Update();

	imageVolume = reader->GetOutput();
}

int CMedImages::GetValueFromTag(string tag)
{
	string strValue;
	gdcmImageIO->GetValueFromTag(tag, strValue);
	int intValue = atoi(strValue.c_str());
	return intValue;
}

void CMedImages::ObtainImagesInfomation()
{
	string tag;
	tag = "0028|1050";
	windowCenter = GetValueFromTag(tag);
	tag = "0028|1051";
	windowWidth = GetValueFromTag(tag);

	tag = "0028|0010";
	xSize = GetValueFromTag(tag);
	tag = "0028|0011";
	ySize = GetValueFromTag(tag);


}

void CMedImages::Update()
{
	LoadImages();

	ObtainImagesInfomation();
}



vtkImageData* CMedImages::GetImageData(ImageDirection direction, int imageIndex)
{
	reader->UpdateOutputInformation();
	ImagesType::RegionType inputRegion = imageVolume->GetLargestPossibleRegion();
	ImagesType::SizeType size = inputRegion.GetSize();
	ImagesType::IndexType start = inputRegion.GetIndex();

	switch (direction)
	{
	case ImageDirection_XY:
		start[2] = imageIndex;
		size[2] = 0;
		break;
	case ImageDirection_XZ:
		start[1] = imageIndex;
		size[1] = 0;
		break;
	case ImageDirection_YZ:
		start[0] =imageIndex;
		size[0] = 0;
		break;
	default:
		break;
	}

	ImagesType::RegionType desiredRegion;
	desiredRegion.SetSize(size);
	desiredRegion.SetIndex(start);

	typedef itk::Image<PixelType, 2> SliceImageType;
	typedef itk::ExtractImageFilter<ImagesType, SliceImageType> ExtractImageFilterType;
	ExtractImageFilterType::Pointer extractImageFilter = ExtractImageFilterType::New();
	extractImageFilter->InPlaceOn();
	extractImageFilter->SetDirectionCollapseToGuess();
	extractImageFilter->SetExtractionRegion(desiredRegion);
	extractImageFilter->SetInput(imageVolume);
	extractImageFilter->Update();

	typedef itk::ImageToVTKImageFilter<SliceImageType> ConnectorType;

	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(extractImageFilter->GetOutput());
	connector->Update();
	imageData2D = vtkSmartPointer<vtkImageData>::New();
	imageData2D->DeepCopy(connector->GetOutput()); 
	imageData2D->Update();


	return imageData2D;
};

int CMedImages::GetWindowCenter()
{
	return windowCenter;
}

int CMedImages::GetWindowWidth()
{
	return windowWidth;
}