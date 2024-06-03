#pragma once

struct WNode
{
	WNode()
	{
		depth = -1;
		parent = left = right = split = -1;
		value = -1;
	}

	int depth;
	int value;
	int split;

	int parent;
	int left;
	int right;
};


struct WSplit
{
	WSplit()
	{
		varIdx = 0;
		quality = c = 0.f;
	}
	int varIdx;
	float quality;
	float c;
};


//class SMEEClassifyTree
//{
//public:
//	std::vector<WNode> vWnode;
//	std::vector<WSplit> vSplit;
//}
