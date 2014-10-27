#include <iostream>
#include <string>
#include "stdlib.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkCastImageFilter.h"
#include "MathFunc.h"


using namespace std;

const unsigned short dimension = 3;
typedef short PixelType;
typedef itk::Image<PixelType, dimension> ImageType;

typedef double HessianPixelType;//
typedef itk::Image<HessianPixelType, dimension> HessianInnerImageType;

typedef itk::CastImageFilter<ImageType, HessianInnerImageType> CastFilterType;

typedef itk::HessianRecursiveGaussianImageFilter<HessianInnerImageType> HFilterType;
typedef itk::Vector<HessianPixelType, dimension> VecType;
typedef itk::Matrix<HessianPixelType, dimension, dimension> MatType;

//
typedef itk::ImageRegionIterator<ImageType> OutputIterType;
typedef itk::SymmetricEigenAnalysis<MatType, VecType, MatType> EigValAnalysisType;


typedef ImageType::Pointer ImagePointerType;
typedef itk::ImageRegionIteratorWithIndex<HFilterType::OutputImageType> HIterType;

class EigValHessian {


private:
	  ImageType::RegionType region;
	  ImageType::SpacingType spacing;
	  ImageType::PointType origin;


    CastFilterType::Pointer CastFilter; //一般是用这个类把点像素值从整型转换成浮点型
    HFilterType::Pointer HFilter; //海森

    EigValAnalysisType EigValAnalysis;

	ImagePointerType  OutputImagePointer;

public:

		 int max;

		 EigValHessian(void)
		 {
			 max=0;  
			 
			 CastFilter = CastFilterType::New();
             HFilter = HFilterType::New();
			 OutputImagePointer=ImageType::New();
		 }


		 ~EigValHessian(void)
		 {}


  ImagePointerType  EigValHessians(const ImageType::Pointer& image) {
        VecType EigVal;
        MatType tmpMat;
   
        region=image->GetLargestPossibleRegion();
        spacing=image->GetSpacing();
        origin=image->GetOrigin();


        HFilter->SetSigma(3);//3 for sigma;
        EigValAnalysis.SetDimension(3);
        CastFilter->SetInput(image);
        HFilter->SetInput(CastFilter->GetOutput());

        HFilter->Update();

        HIterType HIter(HFilter->GetOutput(),region);


		OutputImagePointer->SetRegions(region);
		OutputImagePointer->SetOrigin(origin);
		OutputImagePointer->SetSpacing(spacing);
		OutputImagePointer->Allocate();

 OutputIterType OutputIter(OutputImagePointer,region);

        itk::SymmetricSecondRankTensor<double,3> Tensor;

		 fstream fout ("D:\\File2.txt");  
		 int i=0;

		 
        int num=0;
        for(HIter.GoToBegin(),OutputIter.GoToBegin();!HIter.IsAtEnd()&&!OutputIter.IsAtEnd();++HIter,++OutputIter){
            Tensor=HIter.Get();

            tmpMat[0][0]=Tensor[0];
            tmpMat[0][1]=Tensor[1];
            tmpMat[1][0]=Tensor[1];
            tmpMat[0][2]=Tensor[2];
            tmpMat[2][0]=Tensor[2];
            tmpMat[1][1]=Tensor[3];
            tmpMat[2][1]=Tensor[4];
            tmpMat[1][2]=Tensor[4];
            tmpMat[2][2]=Tensor[5];
            EigValAnalysis.ComputeEigenValues(tmpMat,EigVal);
            //	//
			fout<<i<<" EigVal "<<EigVal<<endl;
			double weight=sheet(EigVal[2],EigVal[1],EigVal[0])*1000;
		fout<<i<<" weight "<<weight<<endl;
		if(weight>max)
			max=weight;
	
			PixelType pixweight=weight;
			OutputIter.Set(pixweight);	

			i++;
        }
 
            OutputImagePointer->Update();
       
		return OutputImagePointer;
    }



};



