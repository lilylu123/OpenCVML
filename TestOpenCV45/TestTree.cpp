#include <opencv2/ml.hpp>
#include <iostream>
#include<ctime>
#include "utils.h"

using namespace cv;
using namespace cv::ml;
using namespace std;


void GenDataArray(const int & number_of_items, float *wp, int if_print = 0)
{
	for (int i = 0; i < number_of_items ; i++)
	{
		if (i < number_of_items/2)
		{
			wp[i * 2] = 1.0;
			wp[i * 2 + 1] = i*1.0;
		}
		else
		{
			wp[i * 2] = float(i + 3 + 0.00001);
			wp[i * 2 + 1] = float(i + 3 + 0.00001);
		}
		
	}

	if (if_print == 1)
	{
		// 打印数据
		for (int i = 0; i < number_of_items * 2; i++)
		{
			if (i % 2 == 0)
			{
				std::cout << "x:" << wp[i] << ",   y:" << wp[i + 1] << std::endl;
			}
		}
	}
}


void GenLabelData(const int & number_of_items, float *LabelData, int if_print = 0)
{
	for (int i = 0; i < number_of_items ; i++)
	{
		LabelData[i] = int(i % 2 );
	}

}


void main4testDeserilizeTree()
{
	const std::string save_file{ "./iris_decision_tree_model.json" }; // .xml, .yaml, .jsons
}

void main()//4testDataFCSV2DT()
{

	// 第一部分读取数据
	std::string csvFileName = "./iris_data/data.csv";
	std::string csvLabelFileName = "./iris_data/label.csv";
	int col_num = 4;
	int row_num = 150;

	// 以指针的方式读取
	float*  dataFptr = new float[row_num * col_num];
	int* labelIptr = new int[row_num * 1];

	readCSV2Fptr(csvFileName, dataFptr);
	readCSV2IntPtr(csvLabelFileName, labelIptr);

	cv::Mat datasetMat = cv::Mat(row_num, col_num, CV_32FC1, dataFptr);
	cv::Mat LabelMat = cv::Mat(row_num, 1, CV_32SC1, labelIptr);

	// std::cout << "datasetMat:" << datasetMat << std::endl;
	// std::cout << "lableMat:" << LabelMat << std::endl;


	//// train 的data数据集 与 labelMat数据 每个数据占用的位数相同，否则会出错。
	//// train 的data用F类型， label用S类型
	cv::Ptr<cv::ml::TrainData> train_data = cv::ml::TrainData::create(datasetMat, cv::ml::ROW_SAMPLE, LabelMat);

	//// 第三步，构建DecisionTree训练模型并进行训练
	cv::Ptr<cv::ml::DTrees> dtree = cv::ml::DTrees::create();

	// set的参数不能设置错误
	dtree->setMaxCategories(4);
	dtree->setMaxDepth(3);
	dtree->setMinSampleCount(1);
	dtree->setCVFolds(0);
	dtree->setUseSurrogates(false);
	dtree->setUse1SERule(false);
	dtree->setTruncatePrunedTree(false);
	dtree->setRegressionAccuracy(0);

	// weights: 是否设置训练权重；通过setPriors获取；
	bool set_label_weight = true;

	if (set_label_weight)
	{
		cv::Mat LabelWeight = (Mat_<double>(3, 1) << 0.0, 1.0, 0.0);
		dtree->setPriors(LabelWeight);
	}
	else
	{
		dtree->setPriors(cv::Mat());
	}
	



	std::cout << "开始训练：" << std::endl;

	clock_t BeginTime, EndTime;
	BeginTime = clock();

	dtree->train(train_data);

	std::cout << "结束训练：" << std::endl;


	const std::string save_file{ "./iris_decision_tree_model_addWeight.json" }; // .xml, .yaml, .jsons
	dtree->save(save_file);


	EndTime = clock();

	std::cout << "Current Training data sample number is :" << row_num << ".Feature num is :" << col_num << std::endl;
	std::cout << "Train+Save model time:" << double(EndTime - BeginTime) << "ms" << std::endl;

	// Test the trained decision tree
	Mat testSample = datasetMat;
	Mat prediction;
	dtree->predict(testSample, prediction);

	// cout << "Prediction for test sample: " << prediction << endl;


	// 保存预测结果;
	std::string saveLabelFileName = "./iris_data/predLabel.csv";
	//saveMatAsText(prediction, saveLabelFileName);

	saveMatAsCSV(prediction, saveLabelFileName);

	delete[] dataFptr;
	delete[] labelIptr;
}


int main4testReadDTree()
{
	Ptr<DTrees> dtree = Algorithm::load<DTrees>("./iris_decision_tree_model.json");

	if (dtree.empty()) {
		std::cerr << "无法加载决策树模型。" << std::endl;
		return -1;
	}

	std::cout << "决策树模型已经加载。" << std::endl;

	// 第一部分读取数据
	std::string csvFileName = "./iris_data/data.csv";
	int col_num = 4;
	int row_num = 150;

	// 以指针的方式读取
	float*  dataFptr = new float[row_num * col_num];
	readCSV2Fptr(csvFileName, dataFptr);
	cv::Mat datasetMat = cv::Mat(row_num, col_num, CV_32FC1, dataFptr);
	std::cout << "datasetMat:" << datasetMat << std::endl;


	// Test the trained decision tree
	Mat testSample = datasetMat;
	Mat prediction;
	dtree->predict(testSample, prediction);

	cout << "Prediction for test sample: " << prediction << endl;

	// 保存预测结果;
	std::string saveLabelFileName = "./iris_data/predLabel_loadModel.csv";

	saveMatAsCSV(prediction, saveLabelFileName);

	delete[] dataFptr;

	
}

int main4testDecisionTreeTrain()
{
	/********************************************************************
		说明：
				1. CV 中 train data目前支持的格式为float格式；
	********************************************************************/
	//input : data: WaferPoints
	//output: data: WaferPoints

	//第1步，生成输入的WaferPoints数据
	int number_of_items = 100;
	int if_print = 0;

	/**********************************
	name : GenWaferPoints
	作用：生成waferPoints数据
	input : number_of_iterms,
			if_print
	output:
			WaferPoints wp
	**********************************/
	//GenWaferPoints(number_of_items, wp, if_print);

	// 使用了New之后，后面要使用delete
	float *array_wafer_point = new float[2 * number_of_items];
	int *label_point = new int[number_of_items];
	// int *if_repeated = new int[number_of_items];
	int return_index = 0;

	GenDataArray(number_of_items, array_wafer_point, if_print);

	//-------------------------------------------------------------------------------------
	//第2步，将waferPoints数据转化为CV::Mat
	// cv::Mat Data = cv::Mat::zeros(number_of_items, 2, CV_32FC1);
	cv::Mat DataFArray = cv::Mat(number_of_items, 2, CV_32FC1, array_wafer_point);

	std::cout << "DataFArray:" << DataFArray << std::endl;


	//// 创建label数据
	// cv::Mat LabelMat = cv::Mat::zeros(number_of_items, 1, CV_32SC1);
	cv::Mat LabelMat = cv::Mat(number_of_items, 1, CV_32SC1, label_point);


	for (int i = 0; i < LabelMat.rows; i++) //矩阵行数循环
	{
		for (int j = 0; j < LabelMat.cols; j++) //矩阵列数循环
		{  
			// LabelMat.at<int>(i, j) = (i+j)%2;
			if (i < LabelMat.rows / 2)
			{
				LabelMat.at<int>(i, j) = 0;
			}
			else
			{
				LabelMat.at<int>(i, j) = 1;
			}
		}
	}


	std::cout << "LabelMat:" << LabelMat << std::endl;

	//// train 的data数据集 与 labelMat数据 每个数据占用的位数相同，否则会出错。
	//// train 的data用F类型， label用S类型
	cv::Ptr<cv::ml::TrainData> train_data = cv::ml::TrainData::create(DataFArray, cv::ml::ROW_SAMPLE, LabelMat);

	//// 第三步，构建DecisionTree训练模型并进行训练
	cv::Ptr<cv::ml::DTrees> dtree = cv::ml::DTrees::create();

	// set的参数不能设置错误
	dtree->setMaxCategories(4);
	dtree->setMaxDepth(10);
	dtree->setMinSampleCount(1);
	dtree->setCVFolds(0);
	dtree->setUseSurrogates(false);
	dtree->setUse1SERule(false);
	dtree->setTruncatePrunedTree(false);
	dtree->setRegressionAccuracy(0);

	// weights
	// dtree->setPriors(cv::Mat());

	// mat的数量不要弄错。
	cv::Mat LabelWeight = (Mat_<double>(2, 1) << 1.0,1.0);
	dtree->setPriors(LabelWeight);

	std::cout << "开始训练：" << std::endl;
	dtree->train(train_data);

	const std::string save_file{ "./decision_tree_model.json" }; // .xml, .yaml, .jsons
	dtree->save(save_file);

	// Test the trained decision tree
	Mat testSample = (Mat_<float>(1, 2) << 2.0, 200.0);
	float prediction = dtree->predict(testSample);

	cout << "Prediction for test sample: " << prediction << endl;


	delete[] label_point;
	delete[] array_wafer_point;

	return 0;
}





int main4testDT()
{
	// Define training data
	float labels[3] = { 0, 0, 1 };
	Mat labelsMat(3, 1, CV_32SC1, labels);

	float trainingData[3][2] = { {1, 2}, {3, 4}, {5, 6} };
	Mat trainingDataMat(3, 2, CV_32FC1, trainingData);

	// Create a decision tree classifier
	Ptr<DTrees> dtree = DTrees::create();

	// Set parameters (optional)
	dtree->setMaxDepth(2);
	dtree->setMinSampleCount(2);
	dtree->setCVFolds(0);


	// Train the decision tree
	dtree->train(trainingDataMat, ROW_SAMPLE, labelsMat);

	// Test the trained decision tree
	Mat testSample = (Mat_<float>(1, 2) << 3.0, 3.0);
	float prediction = dtree->predict(testSample);

	cout << "Prediction for test sample: " << prediction << endl;



	return 0;
}

