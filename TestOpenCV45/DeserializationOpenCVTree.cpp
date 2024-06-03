#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include"nlohmann/json.hpp"

#include"Tree.h"

using namespace std;
using json = nlohmann::json;


json read_json(const std::string &pathname){
	ifstream i(pathname);
	json j;
	i >> j;
	return j;
}

int parseNode(const json & node, WNode &wnode, WSplit &wsplit, bool &if_split_exist, int &split_index){
	try {
		wnode.depth = node.at("depth");
		wnode.value = node.at("value");

		if (node.size() == 3) {
			wnode.split = -1;
			if_split_exist = false;
		}

		// ����splits����
		else if (node.size() == 4) {
			wnode.split = split_index;
			if_split_exist = true;

			//����split���ݽṹ
			if (node.at("splits").size() != 1) {
				throw "splits var from json ; splits.size != 1";
			}
			json splits = node.at("splits")[0];
			wsplit.varIdx = splits.at("var");
			wsplit.quality = splits.at("quality");
			wsplit.c = splits.at("le");
			split_index++;
		}
	}
	catch (...)
	{
		std::cout << "caught an unknown exception." << std::endl;
		return 1;
	}
	return 0;
}


int parseJsonNodes(const json &DTreeNodes, std::vector<WNode> &vWnode, std::vector<WSplit> &vSplit){
	vWnode.clear();
	vSplit.clear();
	int split_index = 0;
	int if_ok = 0;

	// ����nodes���ԣ�
	for (int i = 0; i < DTreeNodes.size(); i++) {
		json node = DTreeNodes[i];
		WNode wnode;
		WSplit wsplit;
		bool if_split_exist = false;

		if_ok = parseNode(node, wnode, wsplit, if_split_exist, split_index);
		vWnode.push_back(wnode);

		if (wnode.split != -1) {
			vSplit.push_back(wsplit);
		}
	}
	return if_ok;
}


int parseDTreeJsonFile(const std::string JsonFileName, std::vector<WNode> &vWnode, std::vector<WSplit> &vSplit)
{
	int if_ok = 0;
	json DTreeJson;
	DTreeJson = read_json(JsonFileName);
	json DTreeMl = DTreeJson.at("opencv_ml_dtree");
	json DTreeNodes = DTreeMl.at("nodes");

	if_ok = parseJsonNodes(DTreeNodes, vWnode, vSplit);

	return if_ok;
}

/***************************************************************************************
	�洢������
		1. ������ȱ�����
		2. �ȴ���ߣ��ٴ��ұߣ�

***************************************************************************************/
void main4testDesDT()
{
	int if_ok = 0;
	
	std::string JsonFileName;
	JsonFileName = "C:/workplace/C++/TestOpenCV45/TestOpenCV45/iris_decision_tree_model.json";

	std::vector<WNode> vWnode;
	std::vector<WSplit> vSplit;

	// ��json�ļ�����ΪNode��Split��Ϣ��
	parseDTreeJsonFile(JsonFileName, vWnode, vSplit);

	// using vWnode, vSplit���´�����

	int i, num_nodes = vWnode.size();
	int root = -1, pidx = -1;

	/**/
	
	for (i = 0; i < num_nodes; i++){
		int nidx = i;
		WNode& node = vWnode[nidx];
		node.parent = pidx;

		if (pidx < 0) {
			root = nidx;
		}
		else {
			WNode & parent = vWnode[pidx];
			if (parent.left < 0){
				parent.left = nidx;
			}
			else{
				parent.right = nidx;
			}
		}
		// �����ǰ�ڵ��ܹ��������»��֣��򽫵�ǰ�ڵ����Ϊ���ڵ㣻
		if (node.split >= 0) {
			pidx = nidx;
		}
		// �����Ҷ�ӽڵ㣬�ͻ���Ѱ�Ҹ��ڵ㣻ֱ���ҵ�������û�и�ֵ�ĸ��ڵ㣻���˸��ڵ㸳ֵ��pidx��
		// �����ṹһ����һ����ȫ��������
		else {
			while (pidx >= 0 && vWnode[pidx].right >= 0) {
				pidx = vWnode[pidx].parent;
			}
		}

	}

	std::cout << "finish parse." << std::endl;
}