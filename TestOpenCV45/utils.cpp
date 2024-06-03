#include"utils.h"
#include <opencv2/opencv.hpp>

using namespace cv;


int string_to_char(const std::string &s, char chh[1000]){
	strcpy(chh, s.c_str());
	return 0;
}

int string_to_int(const std::string &s, int &intStr){
	//��д���ᱨ��
	//int intStr = atoi(s);
	//���Ƚ�stringת��char*
	intStr = atoi(s.c_str());
	return 0;
}

int string_to_float(const std::string &s, float &fStr){
	//��д���ᱨ��
	//int intStr = atoi(s);
	//���Ƚ�stringת��char*
	fStr = atof(s.c_str());
	return 0;
}

//����ֵ����ת��Ϊstring�� 
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

	//��ȡ��һ�б�ͷ,
	//�����һ�г������룬
	//������bom-utf8�ĸ�ʽ����
	getline(fp, line);
	std::cout << line << std::endl;

	std::string number;
	std::istringstream readstr(line);
	//string ��������
	for (int j = 0; j < col_num; j++){
		getline(readstr, number, ',');//ѭ����ȡ���ݼ�
		column.push_back(number);
	}

	int i = 0;
	while (getline(fp, line)) {
		std::vector<std::string> data_line;
		std::string number;
		std::istringstream readstr(line);
		//string ��������
		for (int j = 0; j < col_num; j++){
			getline(readstr, number, ',');//ѭ����ȡ���ݼ�
			data_line.push_back(number);
		}
		dataset.push_back(data_line);//���뵽vector��
		i++;
	}
	return 0;
}

// ��vector�ķ�ʽ��ȡ
int readCSV(std::string filename, std::vector<std::vector<float>> &data)
{
	std::ifstream file(filename);

	// �ļ��Ƿ�򿪳ɹ�
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	
	//��ȡ��һ�б�ͷ,
	//�����һ�г������룬
	//������bom-utf8�ĸ�ʽ����
	std::string line;
	if (getline(file, line)){
		std::cout << line << std::endl;}

	// �����Ĳ���
	// ��ȡ����
	while (getline(file, line)){
		std::stringstream ss(line); // ����ss
		std::string sstrLine;
		std::vector<float> row;
		// ���������ö��ŷָ�
		while (getline(ss, sstrLine, ',')){
			row.push_back(std::stof(sstrLine));}
		data.push_back(row);
	}
	return 0;
}

// ��ָ��ķ�ʽ��ȡ
int readCSV2Fptr(std::string filename, float* data)
{
	int ptr_index = 0;
	int col_num = 0;
	int row_num = 0;

	std::ifstream file(filename);
	// �ļ��Ƿ�򿪳ɹ�
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	//��ȡ��һ�б�ͷ,�����һ�г������룬������bom-utf8�ĸ�ʽ����
	std::string line;
	if (getline(file, line))
	{std::cout << line << std::endl;}

	// �����Ĳ��ֶ�ȡ����
	while (getline(file, line)){
		std::stringstream ss(line); // ����ss
		std::string sstrLine;
		// ���������ö��ŷָ�
		
		while (getline(ss, sstrLine, ',')){
			data[ptr_index] = std::stof(sstrLine);
			ptr_index++;}
	}

	return 0;
}

int readCSVInt(std::string filename, std::vector<std::vector<int>>&label)
{
	std::ifstream file(filename);

	// �ļ��Ƿ�򿪳ɹ�
	if (!file){
		std::cout << "open file failed!" << std::endl;
		return 1;}

	std::string FirstLine;
	//��ȡ��һ�б�ͷ, �����һ�г������룬������bom-utf8�ĸ�ʽ����
	if (getline(file, FirstLine)){
		std::cout << FirstLine << std::endl;}

	// �����Ĳ���, ��ȡ����
	std::string line;
	while (getline(file, line)){
		std::stringstream ss(line); // ����ss
		std::string sstrLine;
		std::vector<int> row;
		// ���������ö��ŷָ�
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

	// �ļ��Ƿ�򿪳ɹ�
	if (!file) {
		std::cout << "open file failed!" << std::endl;
		return 1;}

	std::string FirstLine;
	//��ȡ��һ�б�ͷ, �����һ�г������룬������bom-utf8�ĸ�ʽ����
	if (getline(file, FirstLine)) {
		std::cout << FirstLine << std::endl;}

	// �����Ĳ���, ��ȡ����
	std::string line;
	while (getline(file, line)) {
		std::stringstream ss(line); // ����ss
		std::string sstrLine;

		// ���������ö��ŷָ�
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
		std::cerr << "�޷����ļ���" << filename << std::endl;
		return;
	}

	//д����������������
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
		std::cerr << "�޷����ļ�: " << filename << std::endl;
		return;
	}

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			if (j > 0) {
				file << ",";
			}

			// ���ݾ�����������ͽ��в�ͬ�Ĵ���
			if (mat.type() == CV_8U) {
				file << static_cast<int>(mat.at<uchar>(i, j));
			}
			else if (mat.type() == CV_32F) {
				file << mat.at<float>(i, j);
			}
			else if (mat.type() == CV_64F) {
				file << mat.at<double>(i, j);
			}
			// ������Ҫ������Ӹ�������
		}
		file << "\n";
	}
}

void main4TestCsvReadMethod()
{
	std::string csvFileName = "./iris_data/data.csv";
	int col_num = 4;
	int row_num = 151;

	// ��vector�ķ�ʽ��ȡ
	// ��һ�ַ�ʽ
	std::vector<std::vector<std::string> > dataset;
	std::vector<std::string> column;
	read_csv(csvFileName, dataset, column, col_num);

	// �ڶ��ַ�ʽ
	std::vector<std::vector<float>> dataFloat;
	readCSV(csvFileName, dataFloat);

	// ��ȡlabel
	std::string csvLabelFileName = "./iris_data/label.csv";
	std::vector<std::vector<int>> labelInt;
	readCSVInt(csvLabelFileName, labelInt);

	// ��ָ��ķ�ʽ��ȡ
	float*  dataFptr = new float[row_num * col_num];
	int* labelIptr = new int[row_num * 1];

	readCSV2Fptr(csvFileName, dataFptr);
	readCSV2IntPtr(csvLabelFileName, labelIptr);

	delete[] dataFptr;
	delete[] labelIptr;
}



