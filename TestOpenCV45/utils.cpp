#include"utils.h"
#include <opencv2/opencv.hpp>

using namespace cv;


int string_to_char(const std::string &s, char chh[1000]){
	strcpy(chh, s.c_str());
	return 0;
}

int string_to_int(const std::string &s, int &intStr){
	//此写法会报错
	//int intStr = atoi(s);
	//需先将string转成char*
	intStr = atoi(s.c_str());
	return 0;
}

int string_to_float(const std::string &s, float &fStr){
	//此写法会报错
	//int intStr = atoi(s);
	//需先将string转成char*
	fStr = atof(s.c_str());
	return 0;
}

//将数值类型转化为string， 
//string to_string (int val);
//string to_string(long val);
//string to_string(long long val);
//string to_string(unsigned val);
//string to_string(unsigned long val);
//string to_string(unsigned long long val);
//string to_string(float val);
//string to_string(double val);
//string to_string(long double val);

int read_csv(std::string &filepath, std::vector<std::vector<std::string> > &dataset, std::vector<std::string> &column, int &col_num)
{
	std::ifstream fp(filepath);
	if (!fp){
		std::cout << "open file failed!" << std::endl;
		return 1;
	}
	std::string line;

	//读取第一行表头,
	//如果第一行出现乱码，
	//采用无bom-utf8的格式编码
	getline(fp, line);
	std::cout << line << std::endl;

	std::string number;
	std::istringstream readstr(line);
	//string 数据流化
	for (int j = 0; j < col_num; j++){
		getline(readstr, number, ',');//循环读取数据集
		column.push_back(number);
	}

	int i = 0;
	while (getline(fp, line)) {
		std::vector<std::string> data_line;
		std::string number;
		std::istringstream readstr(line);
		//string 数据流化
		for (int j = 0; j < col_num; j++){
			getline(readstr, number, ',');//循环读取数据集
			data_line.push_back(number);
		}
		dataset.push_back(data_line);//插入到vector中
		i++;
	}
	return 0;
}

// 以vector的方式读取
int readCSV(std::string filename, std::vector<std::vector<float>> &data)
{
	std::ifstream file(filename);

	// 文件是否打开成功
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	
	//读取第一行表头,
	//如果第一行出现乱码，
	//采用无bom-utf8的格式编码
	std::string line;
	if (getline(file, line)){
		std::cout << line << std::endl;}

	// 读正文部分
	// 读取单行
	while (getline(file, line)){
		std::stringstream ss(line); // 构造ss
		std::string sstrLine;
		std::vector<float> row;
		// 单行数据用逗号分隔
		while (getline(ss, sstrLine, ',')){
			row.push_back(std::stof(sstrLine));}
		data.push_back(row);
	}
	return 0;
}

// 以指针的方式获取
int readCSV2Fptr(std::string filename, float* data)
{
	int ptr_index = 0;
	int col_num = 0;
	int row_num = 0;

	std::ifstream file(filename);
	// 文件是否打开成功
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	//读取第一行表头,如果第一行出现乱码，采用无bom-utf8的格式编码
	std::string line;
	if (getline(file, line))
	{std::cout << line << std::endl;}

	// 读正文部分读取单行
	while (getline(file, line)){
		std::stringstream ss(line); // 构造ss
		std::string sstrLine;
		// 单行数据用逗号分隔
		
		while (getline(ss, sstrLine, ',')){
			data[ptr_index] = std::stof(sstrLine);
			ptr_index++;}
	}

	return 0;
}

int readCSVInt(std::string filename, std::vector<std::vector<int>>&label)
{
	std::ifstream file(filename);

	// 文件是否打开成功
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	std::string FirstLine;
	//读取第一行表头, 如果第一行出现乱码，采用无bom-utf8的格式编码
	if (getline(file, FirstLine)){
		std::cout << FirstLine << std::endl;}

	// 读正文部分, 读取单行
	std::string line;
	while (getline(file, line)){
		std::stringstream ss(line); // 构造ss
		std::string sstrLine;
		std::vector<int> row;
		// 单行数据用逗号分隔
		while (getline(ss, sstrLine, ','))
		{
			row.push_back(std::stoi(sstrLine));
		}
		label.push_back(row);}

	return 0;
}

int readCSV2IntPtr(std::string filename, int* label)
{
	std::ifstream file(filename);
	int ptr_index = 0;

	// 文件是否打开成功
	if (!file) {
		std::cout << "open file failed!" << std::endl;
		return 1;}

	std::string FirstLine;
	//读取第一行表头, 如果第一行出现乱码，采用无bom-utf8的格式编码
	if (getline(file, FirstLine)) {
		std::cout << FirstLine << std::endl;}

	// 读正文部分, 读取单行
	std::string line;
	while (getline(file, line)) {
		std::stringstream ss(line); // 构造ss
		std::string sstrLine;

		// 单行数据用逗号分隔
		while (getline(ss, sstrLine, ',')){
			label[ptr_index] = std::stoi(sstrLine);
			ptr_index++;}
	}
	return 0;
}

void saveMatAsText(const cv::Mat& mat, const std::string &filename)
{
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cerr << "无法打开文件：" << filename << std::endl;
		return;
	}

	//写入矩阵的行数和列数
	file << mat.rows << " " << mat.cols << std::endl;

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			file << mat.at<float>(i, j) << ",";
		}
		file << std::endl;
	}
	file.close();
}


void saveMatAsCSV(const cv::Mat& mat, const std::string& filename) {
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filename << std::endl;
		return;
	}

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			if (j > 0) {
				file << ",";
			}

			// 根据矩阵的数据类型进行不同的处理
			if (mat.type() == CV_8U) {
				file << static_cast<int>(mat.at<uchar>(i, j));
			}
			else if (mat.type() == CV_32F) {
				file << mat.at<float>(i, j);
			}
			else if (mat.type() == CV_64F) {
				file << mat.at<double>(i, j);
			}
			// 根据需要可以添加更多类型
		}
		file << "\n";
	}
}

void main4TestCsvReadMethod()
{
	std::string csvFileName = "./iris_data/data.csv";
	int col_num = 4;
	int row_num = 151;

	// 以vector的方式读取
	// 第一种方式
	std::vector<std::vector<std::string> > dataset;
	std::vector<std::string> column;
	read_csv(csvFileName, dataset, column, col_num);

	// 第二种方式
	std::vector<std::vector<float>> dataFloat;
	readCSV(csvFileName, dataFloat);

	// 读取label
	std::string csvLabelFileName = "./iris_data/label.csv";
	std::vector<std::vector<int>> labelInt;
	readCSVInt(csvLabelFileName, labelInt);

	// 以指针的方式读取
	float*  dataFptr = new float[row_num * col_num];
	int* labelIptr = new int[row_num * 1];

	readCSV2Fptr(csvFileName, dataFptr);
	readCSV2IntPtr(csvLabelFileName, labelIptr);

	delete[] dataFptr;
	delete[] labelIptr;
}



