//#include "stdafx.h"
#include "RawImagesReader.h"


RawImagesReader::RawImagesReader(void)
{
	nameGenerator = NameGeneratorType::New();
	rawImagesReader = RawImagesReaderType::New();
	rawImageIO = RawImageIOType::New();
	imageData = vtkImageData::New();
	connector3D = ConnectorType3D::New();
}


RawImagesReader::~RawImagesReader(void)
{

	nameGenerator ->Delete();
	rawImagesReader->Delete();
	rawImageIO->Delete();

}

void RawImagesReader::ReadandConnect(QString imageDirectory, int xSize, int ySize, int zSize)
{
	
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;


	imageDirectory.replace(QString("/"), QString("\\"));

    QString imageSeriesFormat = "\\I.pic.%d";
	imageSeriesFormat = imageDirectory + imageSeriesFormat;
	const QByteArray text = imageSeriesFormat.toLocal8Bit();
	const char *Dir = text.data();
//	nameGenerator->SetSeriesFormat("E:\\Medpic\\origin\\I.pic.%d");



	nameGenerator->SetSeriesFormat(Dir);
	nameGenerator->SetStartIndex(1);
	nameGenerator->SetEndIndex(zSize);
	nameGenerator->SetIncrementIndex(1);
	const RawImagesReaderType::FileNamesContainer & filenames = nameGenerator->GetFileNames();


	rawImageIO->SetDimensions(0, xSize); //图像宽
	rawImageIO->SetDimensions(1, ySize); //图像高
	rawImageIO->SetByteOrderToLittleEndian(); // 小端方式


	rawImagesReader->SetFileNames(nameGenerator->GetFileNames());
	rawImagesReader->SetImageIO(rawImageIO);
	rawImagesReader->Update();



	connector3D->SetInput(rawImagesReader->GetOutput());
	connector3D->Update();


	imageData->DeepCopy(connector3D->GetOutput());


//	return rawImagesPointer;
}
