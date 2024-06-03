#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <opencv2/opencv.hpp>

int read_csv(std::string &filepath, std::vector<std::vector<std::string> > &dataset, std::vector<std::string> &column, int &col_num);

int readCSV(std::string filename, std::vector<std::vector<float>> &data);

// ��ָ��ķ�ʽ��ȡ���ݼ�
int readCSV2Fptr(std::string filename, float* data);

int readCSVInt(std::string filename, std::vector<std::vector<int>>&label);

// ��ָ��ķ�ʽ��ȡlabel
int readCSV2IntPtr(std::string filename, int* label);

void saveMatAsText(const cv::Mat& mat, const std::string &filename);

void saveMatAsCSV(const cv::Mat& mat, const std::string& filename);